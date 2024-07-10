from cs50 import get_string
from math import trunc

def main():
    number = get_string("Number: ")
    if is_valid(number):
        print(get_provider(number))
    else:
        print("INVALID")

def is_valid(number):
    if len(number) < 13:
        return False

    tmp = []
    total = 0
    for n in number[-2::-2]:
        tmp.append(int(n) * 2)
        element = tmp[(len(tmp) - 1)]
        if element / 10 >= 1:
            total += trunc(element % 10)
            total += trunc(element / 10)
        else:
            total += element

    for n in number[-1::-2]:
        total += int(n)

    if total % 10 == 0:
        return True
    else:
        return False

def get_provider(number):
    firstDigit = int(number[0])
    secondDigit = int(number[1])


    if firstDigit == 4:
        return "VISA"

    if firstDigit == 5:
        if secondDigit in {1, 2, 3, 4, 5}:
            return "MASTERCARD"

    if firstDigit == 3:
        if secondDigit in {4, 7}:
            return "AMEX"

    return "INVALID"

if __name__ == "__main__":
    main()