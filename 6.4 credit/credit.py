from cs50 import get_string


def main():
    credit_card = set_card()
    valid = checksum(credit_card[::-1])

    if valid is True:
        card = banner(credit_card)
        print(card)
    else:
        print("INVALID")

def set_card():
    credit_card = get_string("Number: ")

    if credit_card == "":
        credit_card = set_card()

    return credit_card

def checksum(credit_card):
    even_sum = 0
    odd_sum = 0
    count = 0

    for digit in credit_card:
        digit = int(digit)

        if count % 2 != 0:
            dig_value = int(credit_card[count]) * 2

            if dig_value > 9:
                dig_value = str(dig_value)

                for sub_dig in dig_value:
                    sub_dig = int(sub_dig)
                    even_sum += sub_dig
            else:
                even_sum += dig_value
            count += 1
        else:
            odd_sum += digit
            count += 1

    total_sum = str(even_sum + odd_sum)
    lenght = len(total_sum)

    if total_sum[lenght - 1] == '0':
        return True
    else:
        return False

def banner(credit_card):
    if len(credit_card) == 15 and credit_card[0] == '3':
        return "AMEX"
    if len(credit_card) == 16 and credit_card[0] == '5':
        return "MASTERCARD"
    else:
        return "VISA"

main()
