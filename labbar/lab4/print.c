#include <stdio.h>

void print( char *input)
{
    int i = 0;

    while(input[i] != '\0')
    {
        putchar(input[i]);
        i++;
    }

}

void println(char *input)
{
    print(input);
    print("\n");
}

int main(int argc, char *argv[])
{
    char *output;

    //print(argv[1]);
    println(argv[1]);

    return 0;
}