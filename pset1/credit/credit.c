#include <stdio.h>
#include <cs50.h>

/*
* Luhn's Algorithm
*
* Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
* Add the sum to the sum of the digits that weren’t multiplied by 2.
* If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
*/


int main(void)
{
    long cardNumber = get_long("Number: ");
    double tmpCardNum = (double) cardNumber;
    long totalSum = 0;

    // Counts number of digits.
    int count = 0;
    do
    {
        count++;

        // Set the current number to the last digit available..
        long currentNum = (long) tmpCardNum % 10;

        // On every second digit, multiply them by 2 and separate any digits if needed.
        if (count % 2 == 0)
        {
            currentNum = currentNum * 2;
            int tmpNum = 0;

            // If contains 2 digits, you have to split them to add individually.
            if (currentNum >= 10)
            {
                tmpNum = currentNum % 10;
                currentNum = currentNum / 10;
            }
            totalSum += (currentNum + tmpNum);
        
        else
        {
            // Add the current number to the total sum.
            totalSum += currentNum;
        }

        // Shifting the decimal place over by one,
        // adding one to the count to determine card length.
        tmpCardNum = tmpCardNum / 10;
    }
    while ((int)tmpCardNum != 0);
    // Breaks once all numbers processed : casting to int drops decimal places.


    // Gets the first and second numbers of the card to validate
    // in conjunction with the card length and Luhn's Algorithm.
    int firstNum = (int)(tmpCardNum * 10);
    int secondNum = (int)(tmpCardNum * 100) % 10;
    string cardType = "INVALID";

    if (totalSum % 10 == 0)
    {
        switch (firstNum)
        {
            case 3 :
                // American Express starts with 34 or 37 - 15 digits long
                if (count == 15 && (secondNum == 4 || secondNum == 7))
                {
                    cardType = "AMEX";
                }
                break;
            case 4 :
                // Visa is 13 or 16 digits long.
                if (count == 13 || count == 16)
                {
                    cardType = "VISA";
                }
                break;
            case 5 :
                // MasterCard starts with 51-55 - 16 digits long.
                for (int i = 1; i < 6; i++)
                {
                    if (count == 16 && secondNum == i)
                    {
                        cardType = "MASTERCARD";
                    }
                }
                break;
            default :
                cardType = "INVALID";
        }
    }

    printf("%s\n", cardType);
}



