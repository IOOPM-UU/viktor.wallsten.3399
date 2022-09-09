#include <stdio.h>
#include <stdbool.h>

typedef struct point point_t; //ett allias för struct point så alla av typen point_t är oxå av typen struct point

typedef struct rectangle rectangle_t; // ett allias för struct rectangle 

struct point
{
    int x;
    int y;
};

struct rectangle
{
    point_t x;
    point_t y;
};

void print_point(point_t *p)
{
    printf("(%d, %d)\n", (*p).x, (*p).y);
}

point_t make_point(int x, int y)
{
    point_t p1 = { };
    p1.x = x;
    p1.y = y;
    return p1;
}

void print_rect(rectangle_t *r)
{
    rectangle_t rekt = *r;
    point_t upper_right = rekt.x;
    point_t lower_left = rekt.y;
    printf("\n");
    printf("upper right: ");
    print_point(&rekt.x);
    printf("lower left: ");
    print_point(&rekt.y);
    printf("\n");
}

rectangle_t make_rect(int a, int b, int c, int d)
{
    rectangle_t r1 = {};
    point_t p1 = make_point(a, b);
    point_t p2 = make_point(c, d);
    r1.x = p1;
    r1.y = p2;
    return r1;
}

int area_rect(rectangle_t *r)
{
    rectangle_t r_area = *r;
    point_t upper_right = r_area.x;
    point_t lower_left = r_area.y;

    int höjd = (upper_right.x - lower_left.x);
    int bas = (upper_right.y - lower_left.y);

    return (höjd * bas);
}


void main(){

point_t p = { .x = 10, .y = 7 };
point_t p2 = {.x = 30, .y = 10};
point_t p3 = {.x = 40, .y = 15};
rectangle_t r = {.x = p3, .y = p2};
//translate(&p, &p);
print_point(&p);
point_t p1 = make_point(2,6);
print_point(&p1);
print_rect(&r);
rectangle_t r1 = make_rect(1, 2, 3, 4);
print_rect(&r1);
int area = area_rect(&r);
printf("area: %d\n", area);

}