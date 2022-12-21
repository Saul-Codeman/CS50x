from cs50 import get_string
import math
# Determine if input is valid
while True:
    cardnumber = get_string("Number: ")
    if int(cardnumber) > 0:
        break
# Determine second to last digit
count = 0
if len(cardnumber) % 2 != 0:
    count = 1
sum = 0
# Iterate through each number of the card number
# Determine if number is valid
for num in cardnumber:
    if count % 2 == 0:
        if int(num) * 2 >= 10:
            other_num = math.floor(int(num) * 2 / 10) + int(num) * 2 % 10
            sum += other_num
        else:
            sum += int(num) * 2
    else:
        sum += int(num)
    count += 1
if sum % 10 != 0:
    print("INVALID")
    quit()
# Determine what card it is
# Determine if card is AMEX
if cardnumber[0] == "3" and len(cardnumber) == 15:
    if cardnumber[1] == "4" or cardnumber[1] == "7":
        print("AMEX")
        quit()
# Determine if card is Mastercard
elif cardnumber[0] == "5" and len(cardnumber) == 16:
    if cardnumber[1] == "1" or cardnumber[1] == "2" or cardnumber[1] == "3" or cardnumber[1] == "4" or cardnumber[1] == "5":
        print("MASTERCARD")
        quit()
# Determine if card is VISA
elif cardnumber[0] == "4":
    if len(cardnumber) == 16 or len(cardnumber) == 13:
        print("VISA")
        quit()
else:
    print("INVALID")

