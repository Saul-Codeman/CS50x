#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Luhn's Algorithm
int total(long cardnumber)
{
    long numbercalc = cardnumber;
    int sum1 = 0;
    int sum2 = 0;
    int total = 0;
    int mod1;
    int mod2;
    int d1;
    int d2;
        // Double every digit starting from the second to last digit.
    do{
        //Last and every other digit is added
        mod1 = numbercalc % 10;
        numbercalc = numbercalc / 10;
        sum1 = sum1 + mod1;
        // Second to last and every other digit is multiplied by two and added
        mod2 = numbercalc % 10;
        numbercalc = numbercalc / 10;
        mod2 = mod2 * 2;
        d1 = mod2 % 10;
        d2 = mod2 / 10;
        sum2 = sum2 + d1 + d2;
    } while (numbercalc > 0);
    total = sum1 +sum2;
    if (total % 10 != 0){
            return 1;
    }
    return 0;
}


int main(void)
{
    // Get cc number
    long cardnumber = get_long("Number: ");

    // Count length of cc number
    int length = 0;
    long numbercount = cardnumber;
    do{
    numbercount /= 10;
    length++;
} while (numbercount != 0);

    // Get Starting 2 Numbers
    long start = cardnumber;
    do{
        start = start / 10;
    } while (start > 100);

    // Determine if card in invalid
    if (length != 13 && length != 15 && length != 16){
        printf("INVALID\n");
        return 0;
    }
    // Check if cardnumber is invalid
    if (total(cardnumber)){
        printf("INVALID\n");
        return 0;
    };
    // Determine if card is VISA
    if ((length == 13 || length == 16) && (start / 10 == 4)){
        printf("VISA\n");
        return 0;
    }
    // Determine if card is MASTERCARD
    if ((length == 16) && (start == 51 || start == 52 || start == 53 || start == 54 || start == 55)){
        printf("MASTERCARD\n");
        return 0;
    }
    // Determine if card is AMEX
    if ((length == 15) && (start == 34 || start == 37)){
        printf("AMEX\n");
        return 0;
    }
    else{
        printf("INVALID\n");
        return 0;
    }
}

