import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    #Show portfolio of stocks of a user with shares > 1.
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    shares = db.execute("SELECT symbol, SUM(shares) as shares, operation FROM transactions WHERE user_id = ? GROUP BY symbol HAVING (SUM(shares)) > 0"
    ,session["user_id"])

    total_cash_shares = 0

    for share in shares:
        quote = lookup(share["symbol"])
        share["name"] = quote["name"]
        share["price"] = quote["price"]
        share["total"] = share["price"] * share["shares"]
        total_cash_shares += share["total"]
    round(user_cash[0]["cash"], 2)
    total_cash = total_cash_shares + user_cash[0]["cash"]

    return render_template("index.html", shares=shares, user_cash=user_cash[0], total_cash=total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        price = lookup(symbol)
        shares = request.form.get("shares")
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        name = lookup(symbol)

        if not symbol:
            return apology("missing valid symbol")

        elif price is None:
            return apology("missing valid symbol")

        try:
            shares = int(shares)

            if shares < 1:
                return apology("missing valid input number")

        except ValueError:
            return apology("share must be a positive integer")

        shares_price = shares * price["price"]

        if shares_price > user_cash:
            return apology("user does not have enough cash")

        else:
            #Update the users cash
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", shares_price, session["user_id"])
            #Insert the stock purchase into a new database
            db.execute("INSERT INTO transactions (user_id, symbol, name, shares, price, operation, time) VALUES (?, ?, ?, ?, ?, ?, datetime())",
            session["user_id"], symbol, name["name"], shares, price["price"], "buy")

            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    shares = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])

    return render_template("history.html", shares=shares)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        quote = lookup(request.form.get("symbol"))

        if not quote:
            return apology("missing valid symbol")

        else:
            return render_template("quoted.html", name=quote["name"], symbol=quote["symbol"], price=quote["price"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirm_password = request.form.get("confirmation")

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(rows) != 0:
            #Apology for existing username
            return apology("username already exists")
        elif not username:
            #Apology for missing username
            return apology("missing username")
        elif not password:
            #Apology for missing password
            return apology("missing password")
        elif password != confirm_password:
            return apology("passwords do not match")
        elif not confirm_password:
            return apology("missing confirmation password")
        else:
            hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
            db.execute("INSERT INTO users (username, hash) VALUEs (?, ?)", username, hash)
            return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":



        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        quote = lookup(request.form.get("symbol"))
        name = quote["name"]
        price = lookup(symbol)["price"]

        shares = int(shares)

        new_shares = db.execute("SELECT SUM(shares) as shares FROM transactions WHERE user_id = ? AND symbol = ?",session["user_id"], symbol)[0]
        user_shares = int(new_shares["shares"])

        user_shares_left = user_shares - shares

        # User has not selected a share to sell
        if not symbol:
            return apology("missing share to sell")

        # User has not input the number of shares to sell
        elif not shares or shares < 0:
            return apology("missing number of shares to sell")

        elif user_shares < 0:
            return apology("no shares to sell")

        elif user_shares_left < 0:
            return apology("Not enough shares to sell. Please enter a lower number.")

        else:
            #Increase user cash from sale
            user_cash += shares * price
            #Perform the transaction in the transactions table
            db.execute("INSERT INTO transactions (user_id, symbol, name, shares, price, operation, time) VALUES (?, ?, ?, ?, ?, ?, datetime())",
            session["user_id"], symbol, name, -shares, price, "sell")
            #Update the users cash after the sale
            db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash, session["user_id"])
            return redirect("/")

    else:
        shares = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
        return render_template("sell.html", shares=shares)

@app.route("/cash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == "POST":


        cash = request.form.get("cash")
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        user_cash = float(user_cash)

        if not cash:
            return apology("missing added funds")

        else:
            cash = float(cash)
            user_cash += cash

            db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash, session["user_id"])

            return redirect("/")

    else:
        user_cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        return render_template("cash.html", user_cash=user_cash)