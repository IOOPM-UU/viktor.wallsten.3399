#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main( int argc, char *argv[])
{
    char *numb = argv[1]; // en string med vårt arg
    int num = atoi(numb); // gör om vår sträng till en int
    
    for (int i = 1; i <= num; i++)
    {
       if(i % 3 == 0)
       {
        printf("fizz, ");
       }
       else
       {
        if(i % 5 == 0)
        {
        printf("buzz, ");
        }
        else
        {
            printf("%d, ", i);
        }
       }
    }
    
    return 0;
}