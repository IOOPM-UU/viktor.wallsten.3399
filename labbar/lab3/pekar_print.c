#include <stdio.h>

void print(char *str)
{
    char *end = str; // här pekar end på början av str
    while (*end != '\0') // derefrence det som finns på platsen in end
    {
        putchar(*end); // derefrence end och printar det som finns där
        end++; // öka index på end
    }
    
}

int main(int argc, char *argv[])
{
    char *argument = argv[1]; // gör en pekare till vårt argument
    print(argument);
    puts("\n");

    return 0;
}