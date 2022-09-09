#include <stdio.h>
#include "utils.h"
#include <stdlib.h>
#include <time.h>

int main()
{
    const int max = 1000; // högsta det kan vara
    int guess;
    int guesses = 0; // antalet gissningar
    int awnser; // svaret
    char *name;
    

    srand(time(0)); // uses the current time as seed

    awnser = (rand() % max); // ger ett random nummer mellan max och min

    name = ask_question_string("enter your name: "); //använder för att ta namn
    printf("hello '%s'\n", name); // printa namn

    do{
        guess = ask_questions_int("enter a guess\n"); // används för att ta en gissning som input

        if(guess > awnser) // kollar om guess är större eller minder än awnser
        {
            printf("guess is too high, guess again\n");
        }
        else if(guess < awnser)
        {
            printf("guess is too low, guess again\n");
        }                    
        else // om den inte är större eller mindrre än svare måste det vara korrekt och du har vunnit
        {  
            printf("You guessed correct '%s', you won\n", name);
            printf("It took you '%d' guesses\n", (guesses +1));
        }
        guesses++;
        
        if(guesses == 15)
        {
            printf("you have no guesses left :( \n");
            printf("the correct awnser was '%d'\n", awnser);
        }
   
    }while (guess != awnser && guesses != 15);

    return 0;
}