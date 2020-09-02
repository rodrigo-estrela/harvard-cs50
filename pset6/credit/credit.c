#include <stdio.h>
#include <cs50.h>

long get_card_number(void);
int digitsCount(long number);
int digitsSum(int number);
bool isValid(long number);
int getStartingDigits(long number);

int main(void)
{
    long cardNumber = get_card_number();
    if (isValid(cardNumber))
    {
        int startingDigits = getStartingDigits(cardNumber);
        switch (startingDigits)
        {
            case 34:
            case 37:
                printf("AMEX\n");
                return 0;
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                printf("MASTERCARD\n");
                return 0;
            default:
                if ((startingDigits / 10) == 4)
                {
                    printf("VISA\n");
                    return 0;
                }
        }
    }

    printf("INVALID\n");
}

long get_card_number(void)
{
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);
    return number;
}

int digitsCount(long number)
{
    int counter = 0;
    while (number > 0)
    {
        number /= 10;
        counter++;
    }
    return counter;
}

bool isValid(long number)
{
    // Check quantity of digits, should be 13 <= digitsCount >= 16
    int digits = digitsCount(number);
    if (digits < 13 || digits > 16)
    {
        return false;
    }

    // Checksum algorithm
    int position = 1; // used to capture every other digit;
    int everyOtherSum = 0;
    int remainingDigitsSum = 0;

    while (number > 0)
    {
        if ((position % 2) == 0)
        {
            everyOtherSum += digitsSum((number % 10) * 2);
        }
        else
        {
            remainingDigitsSum += number % 10;
        }
        number /= 10;
        position++;
    }

    // Final check
    if (((everyOtherSum + remainingDigitsSum) % 10) == 0)
    {
        return true;
    }

    return false;
}

int digitsSum(int number)
{
    //This function return the sum of digits from a given number
    int sum = 0;
    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }

    return sum;
}

int getStartingDigits(long number)
{
    // This function returns the frist two digits of the card number
    int remainder;
    while (number > 10)
    {
        remainder = number % 100;
        number /= 10;
    }

    return remainder;
}