#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[1])
{
    // Determine if key is valid
    if (argc != 2){
        printf("Usage: ./caesar key\n");
        return 1;
    }
    string tmp = argv[1];
    int key = atoi(argv[1]);
    for (int i = 0; i < strlen(tmp); i++){
        if (tmp[i] > 57 || tmp[i] < 48){
            printf("Usage: ./caesar key\n");
            return 1;
    }
    }
    printf("%i\n", key);
    // Get the plaintext
    string plaintext = get_string("plaintext: ");
    int characters = strlen(plaintext);
    // Shift plaintext to be ciphertext
    string ciphertext = NULL;
    char cipherletter;
    for (int j = 0; j < characters; j++){
        if (isupper(plaintext[j])){
            //shift by key
            cipherletter = plaintext[j + key];
            // if the cipherletter goes past Z
            if (cipherletter > 90){
                cipherletter = plaintext[j - 26 + key];
            }
            ciphertext += cipherletter;
        }
        else if (islower(plaintext[j])){
            cipherletter = plaintext[j+key];
            if (cipherletter > 122){
                cipherletter = plaintext[j - 26 + key];
            }
            ciphertext += cipherletter;
            printf("%s\n", ciphertext);
        }
        else{
            ciphertext += plaintext[j];
        }
    }
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}