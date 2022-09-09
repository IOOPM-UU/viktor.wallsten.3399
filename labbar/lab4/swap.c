#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = 0; // sätter temp till 0 
    temp = *a; // sätter temp till värdet av det som pointern a pekar på dvs 42
    *a = *b; // sätter värdet på a till värdet på b
    *b = temp; // sätter värdet på b till temp

}

int main()
{
    int a = 42;
    int b = 7;

    swap(&a, &b); //skickar med adresserna för a och b

    printf("a: %d \nb: %d\n", a, b);
}