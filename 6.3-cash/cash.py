from cs50 import get_float


def main():
    cash = set_cash()
    coins = 0

    while cash > 0:

        if cash >= 0.25:
            cash -= 0.25
            cash = round(cash, 2)
            coins += 1

        elif cash >= 0.10:
            cash -= 0.10
            cash = round(cash, 2)
            coins += 1

        elif cash >= 0.05:
            cash -= 0.05
            cash = round(cash, 2)
            coins += 1

        else:
            cash -= 0.01
            cash = round(cash, 2)
            coins += 1

    print(coins)

def set_cash():
    cash = get_float("Change owed: ")

    if cash < 0:
        cash = set_cash()

    return cash

main()