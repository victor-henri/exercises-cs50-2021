from cs50 import get_string


def main():
    text = get_string("Text: ")
    letters = 0
    words = 0
    sentences = 0

    for character in text:
        if character.isalpha():
            letters += 1

        if character.isspace():
            words += 1

        if character == '.' or character == '!' or character == '?':
            sentences += 1

    words += 1
    average_letters = letters / words * 100
    average_sentences = sentences / words * 100
    formula = 0.0588 * average_letters - 0.296 * average_sentences - 15.8

    grade = round(formula)

    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

main()