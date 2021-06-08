-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check crime scene reports
SELECT * FROM crime_scene_reports
WHERE year = 2020 AND day = 28 AND street LIKE 'Chamberlin Street';
-- id | year | month | day | street | description
-- 295 | 2020 | 7 | 28 | Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

SELECT name, transcript FROM interviews
WHERE year = 2020 AND day = 28 AND month = 7;
-- name | transcript
-- Jose | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
-- Eugene | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
-- Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
-- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Relevant Info
-- Ruth - Getting in car nearby courthouse within 10 min of theft
-- Eugene - Withdrawing money using ATM on Fifer Street
-- Raymond - Called someone while leaving courthouse < 1min - Mentioned first flight out of Fiftyville TOMORROW - Ask them to buy ticket

-- Check license plates matching description from witness - Ruth
SELECT hour, minute, activity, license_plate, name FROM
(SELECT * from courthouse_security_logs JOIN people ON courthouse_security_logs.license_plate = people.license_plate)
WHERE year = 2020 AND day = 28 AND month = 7 AND hour = 10;
hour | minute | activity | license_plate | name
-- 10 | 8  | entrance | R3G7486 | Brandon
-- 10 | 14 | entrance | 13FNH73 | Sophia
--
-- 10 | 16 | exit     | 5P2BI95 | Patrick
-- 10 | 18 | exit     | 94KL13X | Ernest *
-- 10 | 18 | exit     | 6P58WS2 | Amber
-- 10 | 19 | exit     | 4328GD8 | Danielle
-- 10 | 20 | exit     | G412CB7 | Roger
-- 10 | 21 | exit     | L93JTIZ | Elizabeth
-- 10 | 23 | exit     | 322W7JE | Russell
-- 10 | 23 | exit     | 0NTHK55 | Evelyn
--
-- 10 | 35 | exit     | 1106N58 | Madison
-- 10 | 42 | entrance | NRYN856 | Denise
-- 10 | 44 | entrance | WD5M8I6 | Thomas
-- 10 | 55 | entrance | V47T75I | Jeremy

-- Get ATM withdrawals from Fifer St. ATM as per witness - Eugene
SELECT name, amount FROM
(SELECT * FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number)
WHERE year = 2020 AND month = 7 AND day = 28
AND atm_location LIKE 'Fifer Street'
AND transaction_type LIKE 'withdraw';
-- name      | amount
-- Ernest    | 50 *
-- Russell   | 35
-- Roy       | 80
-- Bobby     | 20
-- Elizabeth | 20
-- Danielle  | 48
-- Madison   | 60
-- Victoria  | 30


-- Get call logs
SELECT name, caller, receiver, duration FROM
(SELECT * FROM phone_calls JOIN people ON phone_calls.caller = people.phone_number)
WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60;
-- name (caller) |  caller         | receiver       | duration
-- Roger    | (130) 555-0289 | (996) 555-8899 | 51
-- Evelyn   | (499) 555-9472 | (892) 555-8872 | 36
-- Ernest   | (367) 555-5533 | (375) 555-8161 | 45 *
-- Kathryn  | (609) 555-5876 | (389) 555-5198 | 60
-- Evelyn   | (499) 555-9472 | (717) 555-1342 | 50
-- Madison  | (286) 555-6063 | (676) 555-6554 | 43
-- Russell  | (770) 555-1861 | (725) 555-3243 | 49
-- Kimberly | (031) 555-6622 | (910) 555-3251 | 38
-- Bobby    | (826) 555-1652 | (066) 555-9701 | 55
-- Victoria | (338) 555-6650 | (704) 555-2131 | 54
SELECT name, caller, receiver, duration FROM
(SELECT * FROM phone_calls JOIN people ON phone_calls.receiver = people.phone_number)
WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60;
-- name (receiver) | caller         | receiver       | duration
-- Jack       | (130) 555-0289 | (996) 555-8899 | 51
-- Larry      | (499) 555-9472 | (892) 555-8872 | 36
-- Berthold   | (367) 555-5533 | (375) 555-8161 | 45 *
-- Danielle   | (609) 555-5876 | (389) 555-5198 | 60
-- Melissa    | (499) 555-9472 | (717) 555-1342 | 50
-- James      | (286) 555-6063 | (676) 555-6554 | 43
-- Philip     | (770) 555-1861 | (725) 555-3243 | 49
-- Jacqueline | (031) 555-6622 | (910) 555-3251 | 38
-- Doris      | (826) 555-1652 | (066) 555-9701 | 55
-- Anna       | (338) 555-6650 | (704) 555-2131 | 54



-- Get flight information as per witness - Raymond - Earliest flight next day from crime
SELECT hour, minute, abbreviation, full_name, city FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE year = 2020 AND day = 29 AND month = 7
ORDER BY hour, minute DESC
LIMIT 1;
-- hour | minute | abbreviation | full_name                   | city
-- 8    | 20     | CSF          | Fiftyville Regional Airport | Fiftyville

-- Shows arrival airport for respective flight
SELECT hour, minute, abbreviation, full_name, city FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE year = 2020 AND day = 29 AND month = 7
ORDER BY hour, minute DESC
LIMIT 1;
-- hour | minute | abbreviation | full_name        | city
-- 8    | 20     | LHR          | Heathrow Airport | London

-- This shows a list of people with booked flights + departure time
SELECT name, hour, minute FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE year = 2020 AND day = 29 AND month = 7
ORDER BY hour, minute DESC;
-- name     | hour | minute
-- Doris    | 8    | 20
-- Roger    | 8    | 20
-- Ernest   | 8    | 20 *
-- Edward   | 8    | 20
-- Evelyn   | 8    | 20
-- Madison  | 8    | 20
-- Bobby    | 8    | 20
-- Danielle | 8    | 20
-- ... More entries but the above is all for the first flight as per witness - Raymond
