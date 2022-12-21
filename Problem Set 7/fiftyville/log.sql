-- Keep a log of any SQL queries you execute as you solve the mystery.
--The CS50 Duck has been stolen! The town of Fiftyville has called upon you to solve the mystery of the stolen duck.
--Authorities believe that the thief stole the duck and then, shortly afterwards, took a flight out of town
--with the help of an accomplice. Your goal is to identify:

-- 1. Looking through the crime_scene_reports on the day of the crime
SELECT * FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND year = 2021 AND street = "Humphry Street";
-- Query showed 5 incidents with the id 295 appearing to be what we are looking for. Humphrey Street bakery
-- robbed at 10:15am

--2. Looking through three interviews that mentioned bakery and occurred at the same time.
SELECT * FROM interviews
WHERE day = 28 AND month = 7 AND year = 2021 AND transcript LIKE '%bakery%';
-- Query showed Ruth, Eugene, and Jose (id: 161,162,163).
-- Ruth: Car left within ten minutes of theft.
-- Eugene: Theif on Leggett Street withdrawing money from ATM in early morning.
-- Jose: Call for less than a minute after theft. Taking earliest flight out of fiftyville on July 29 2021. Ticket purchase July 28, 2021

--3. Checking atm transactions on day of theft and fit the street.
SELECT * FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
--4.Checking bank_accounts for matching account number from theft above.
SELECT * FROM bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");
-- We now have 8 person_ids that could be the theif.

--5. Checking calls that lasted a minute.
SELECT * FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60;
-- Maybe try to find the area code of area.
--6. Checking ticket purchases slightly after call.

--7. Checking license plates of cars that left within ten minutes of theft.
SELECT * FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND activity = "exit" AND hour = 10 AND minute < 25;

--8. Looking at airports that match origin of fiftyville
SELECT * FROM airports
WHERE city = "Fiftyville";

--9. Checking first flight on July 29 2021 out of fiftyville.
SELECT * FROM flights
WHERE day = 29 AND month = 7 AND year = 2021 AND origin_airport_id = (SELECT id FROM airports
WHERE city = "Fiftyville") ORDER BY hour LIMIT 1;

--10. Checking passengers on flight from (9).
SELECT * FROM passengers
WHERE flight_id = (SELECT id FROM flights
WHERE day = 29 AND month = 7 AND year = 2021 AND origin_airport_id = (SELECT id FROM airports
WHERE city = "Fiftyville") ORDER BY hour LIMIT 1);

-- Checking for theif using phone number, bank account number, license plate, flight number, Maybe determine if accomplice was on flight for either person and look at them calling
SELECT * FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60)
AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND activity = "exit" AND hour = 10 AND minute < 25)
AND passport_number IN (SELECT passport_number FROM passengers
WHERE flight_id = (SELECT id FROM flights
WHERE day = 29 AND month = 7 AND year = 2021 AND origin_airport_id = (SELECT id FROM airports
WHERE city = "Fiftyville") ORDER BY hour LIMIT 1));

-- Checking for accomplice Received phone call from theif, was on flight with theif
SELECT * FROM people
WHERE phone_number = (SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60
AND caller = (SELECT phone_number FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60)
AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND activity = "exit" AND hour = 10 AND minute < 25)
AND passport_number IN (SELECT passport_number FROM passengers
WHERE flight_id = (SELECT id FROM flights
WHERE day = 29 AND month = 7 AND year = 2021 AND origin_airport_id = (SELECT id FROM airports
WHERE city = "Fiftyville") ORDER BY hour LIMIT 1))));

-- Checking for city they went to
SELECT * FROM airports
WHERE id = (SELECT destination_airport_id FROM flights
WHERE day = 29 AND month = 7 AND year = 2021 AND origin_airport_id = (SELECT id FROM airports
WHERE city = "Fiftyville") ORDER BY hour LIMIT 1);


