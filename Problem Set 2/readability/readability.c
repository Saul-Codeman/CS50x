#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
    // Get the text from the user
    string text = get_string("Text: ");
    // Get number of letters in text
    int characters = strlen(text);
    float letters = 0;
    float words = 1;
    float sentences = 0;
    for (int i = 0; i < characters; i++){
        if (isupper(text[i])){
            letters++;
        }
        if (islower(text[i])){
            letters++;
        }
        //Get number of words in text
        if (text[i] == ' '){
            words++;
        }
        //Get number of sentences in text
        if (text[i] == '.' || text[i] == '!' || text[i] == '?'){
            sentences++;
        }
    }
    // Coleman-Liau index
    int index = round((0.0588 * letters / words * 100) - (0.296 * sentences / words * 100) - 15.8);
    if (index >= 1 && index <= 16){
        printf("Grade %i\n", index);
    }
    if (index < 1){
        printf("Before Grade 1\n");
    }
    if (index > 16){
        printf("Grade 16+\n");
    }
}