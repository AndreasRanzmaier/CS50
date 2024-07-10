#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool is_valid(long testNumber);
string get_provider(long testNumber);
int get_first_x_digits(long testNumber, int x);
long get_number_lenght(long value);

int main(void)
{
    long testNumber;
    do
    {
        testNumber = get_long("Number: ");
    } while (testNumber < 1);

    if (is_valid(testNumber))
    {
        printf("%s\n", get_provider(testNumber));
    }
    else
    {
        printf("INVALID\n");
    }
}

bool is_valid(long testNumber)
{
    // invalid if not at least 13 digits long
    if (get_number_lenght(testNumber) < 13)
    {
        return false;
    }

    long fullNumber = testNumber;
    int total = 0;
    while (fullNumber > 0)
    {
        long lastNumber = fullNumber / 10;
        int everyOther = lastNumber % 10;
        fullNumber = fullNumber / 100;

        everyOther *= 2;

        // if number is greater then 9 we need to add the 2 digits seperatly
        if ((everyOther / 10) >= 1)
        {
            total += everyOther % 10;
            total += everyOther / 10;
        }
        else
        {
            total += everyOther;
        }
    }
    printf("%i\n", total);

    fullNumber = testNumber;
    while (fullNumber > 0)
    {
        int everyOther = fullNumber % 10;
        fullNumber = fullNumber / 100;

        total += everyOther;
    }

    printf("%i\n", total);

    if (total % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string get_provider(long testNumber)
{
    int firstDigit = get_first_x_digits(testNumber, 1);
    int firstTwoDigits = get_first_x_digits(testNumber, 2);

    switch (firstDigit)
    {
    case 4:
        // VISA 4
        return "VISA";
        break;
    case 5:
        // MASTERCARD  51, 52, 53, 54, 55:
        // also check 2. digit
        if ((firstTwoDigits == 51) || (firstTwoDigits == 52) || (firstTwoDigits == 53) || (firstTwoDigits == 54) || (firstTwoDigits == 55))
        {
            return "MASTERCARD";
        }
        return "INVALID";
        break;
    case 3:
        // AMEX 34, 37
        // also check 2. digit
        if ((firstTwoDigits == 34) || (firstTwoDigits == 37))
        {
            return "AMEX";
        }
        return "INVALID";
        break;
    }
    return "INVALID";
}

int get_first_x_digits(long testNumber, int x)
{
    int position = pow(10, x); // 10 = first digit, 100 = first 2, 1000 = first 3, ...

    // Remove last digit from number till only one digit is left
    while (testNumber >= position)
    {
        testNumber = testNumber / 10;
    }
    return testNumber;
}

long get_number_lenght(long value)
{
    long l = !value;
    while (value)
    {
        l++;
        value = value / 10;
    }
    return l;
}