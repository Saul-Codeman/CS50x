#include <cs50.h>
#include <stdio.h>

int main(void)
{int choice;
do
{
    choice = get_int("How tall would you like the pyramid? ");
}
while(choice < 1 || choice > 8);

for (int i = 1; i <= choice; i++){
    for (int k = choice; k > i; k--){
        printf(" ");
    }
    for (int j = 1; j <= i; j++){
    printf("#");
    }
    printf("\n");
}
}