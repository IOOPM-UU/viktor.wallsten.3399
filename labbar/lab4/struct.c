#include <stdio.h>
#include <stdlib.h>

typedef struct point point_t; //ett allias för struct point så alla av typen point_t är oxå av typen struct point

struct point
{
    int x;
    int y;
};

struct point translate(point_t p1, point_t p2) // används för att flytta en punkt i planet, detta ker med vädesemantik så det är en kopia av p1 som skickas
{
  p1.x += p2.x; // adderar p2.x till p1.x
  p1.y += p2.y; // adderar p2.y till p1.y
  return p1; // returnerar den nya punkten
}

void translate(point_t *p1, point_t *p2) // detta gör samma som ovan men med pekarsemantik dvs att den faktiska p1 manipuleras och INTE en kopia
{
  p1->x += p2->x; // pilen är en kortform av p->x dvs samma sak som att skriva (*p).x alltså ge mig värdet som p pekar på och hämta ur fältet x
  p1->y += p2->y;
}

void main()
{
point_t p = {.x = 10, .y = -42};
printf("point(x=%d,y=%d)\n", p.x, p.y);

// om vi har definerat en struct som tar 2 int och bara sätter väde på en av dem så kommer den andra att automatiskt sättas till 0
point_t p1 = { .x = 10 };
point_t p2 = { .y = -42 };
point_t p3 = { };

printf("point(x=%d,y=%d)\n", p1.x, p1.y);
printf("point(x=%d,y=%d)\n", p2.x, p2.y);
printf("point(x=%d,y=%d)\n", p3.x, p3.y);
}
