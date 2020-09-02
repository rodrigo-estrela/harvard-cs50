from cs50 import get_string


def main():
    text = get_string("Text: ")
    index = colemanLiauIndex(text)

    if index <= 1:
        print("Before Grade 1")
        return 0
    elif index >= 16:
        print("Grade 16+")
        return 0

    print(f"Grade {index}")


def count_letters(s):
    counter = 0
    for c in range(len(s)):
        if s[c].isalnum():
            counter += 1

    return counter


def count_words(s):
    counter = 0
    i = 0
    while (i < len(s)):
        if s[i].isalnum():
            counter += 1
            while (True):
                i += 1
                if s[i].isspace() or i == (len(s) - 1):
                    break
        i += 1
    
    return counter


def count_sentences(s):
    counter = 0
    i = 0
    while (i < len(s)):
        if s[i].isalnum():
            counter += 1
            while (True):
                i += 1
                if isEndOfSentence(s[i]) or i == (len(s) - 1):
                    break
        i += 1

    return counter


def isEndOfSentence(s):
    if s == '.' or s == '?' or s == '!':
        return True

    return False


def colemanLiauIndex(s):
    letters = count_letters(s)
    words = count_words(s)
    sentences = count_sentences(s)

    L = (letters * 100) / words
    S = (sentences * 100) / words

    return round(0.0588 * L - 0.296 * S - 15.8)


main()