#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    string key = argv[1];
    if (argc != 2){
        printf("./substitution key\n");
        return 1;
    }
    // VALIDATE KEY
    int count = 0;
    for (int i = 0; i < strlen(key); i++){
        // Check if count has any non alphabetical characters
        if (isupper(key[i])){
            count++;
        }
        if (islower(key[i])){
            count++;
        }
        else if (!isalpha(key[i])){
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }
    // Use nested loop to determine if a character was repeated. Maybe lowercase all chars to make it easier.
    for (int j = 0; j < strlen(key); j++){
        for (int k = j + 1; k < strlen(key); k++){
            if (tolower(key[j]) == tolower(key[k])){
                printf("Key must contain 26 unique characters.\n");
                return 1;
            }
        }
    }
    if (count != 26){
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    string plaintext = get_string("Plaintext: ");
    // Make two separate conditionals for lowercase and uppercase to use with the key in order to preserve case
    printf("ciphertext: ");
    string upper_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lower_alphabet = "abcdefghijklmnopqrstuvwxyz";

    // if l == m then add key[m] to the ciphertext
    for (int l = 0; l < strlen(plaintext); l++){
        if (isupper(plaintext[l])){
            for (int m = 0; m < strlen(upper_alphabet); m++){
                if (plaintext[l] == upper_alphabet[m]){
                    int index = m;
                    printf("%c", toupper(key[index]));
                }
            }
        }
        if (islower(plaintext[l])){
            for (int m = 0; m < strlen(lower_alphabet); m++){
                if (plaintext[l] == lower_alphabet[m]){
                    int index = m;
                    printf("%c",tolower(key[index]));
                }
            }
        }
        else if (!isalpha(plaintext[l])){
            printf("%c", plaintext[l]);
        }
    }
    printf("\n");
    return 0;
}