from cs50 import get_int
# Luhn's Algorithm
#
# Multiply every other digit by 2, starting with the number’s second-to-last digit,
# and then add those products’ digits together.
# Add the sum to the sum of the digits that weren’t multiplied by 2.
# If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0),
# the number is valid!


def main():
    # Get card number from user
    card_num = get_int("Number: ")
    total_sum = 0
    card_length = 0

    # loop until we process all card numbers
    while True:
        # Add to count the total number of digits
        card_length += 1

        # Get current number to process - truncating
        curr_num = int(card_num % 10)

        # Process as per Luhns Algorithm
        tmp = 0
        if card_length % 2 == 0:
            curr_num = curr_num * 2
            if curr_num >= 10:
                # Truncate to utilize only the digits individually
                tmp = int(curr_num % 10)
                curr_num = int(curr_num / 10)

        total_sum += (curr_num + tmp)

        # Shift card number over one decimal place
        card_num = card_num / 10

        # When the number is less than one all digits have been processed
        if card_num < 1:
            break

    first_num = int(card_num * 10)
    second_num = int((card_num * 100) % 10)

    print(f"total: {total_sum} % 10 = {total_sum % 10}")

    card_type = "INVALID"

    if round(total_sum % 10) == 0:
        if first_num == 3:
            if card_length == 15 and (second_num == 4 or second_num == 7):
                card_type = "AMEX"
        elif first_num == 4:
            if card_length == 13 or card_length == 16:
                card_type = "VISA"
        elif first_num == 5:
            for i in range(6):
                if card_length == 16 and second_num == i:
                    card_type = "MASTERCARD"

    print(card_type)


main()