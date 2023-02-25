from cs50 import get_int


def set_height():
    height = get_int("Height: ")

    if height < 1 or height > 8:
        height = set_height()

    return height


height = set_height()

for i in range(height):
    for j in range(height - i - 1):
        print(" ", end="")
    for k in range(i + 1):
        print("#", end="")
    print()
