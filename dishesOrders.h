#ifndef ORDERS_H
#define ORDERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

// defined variables of Struct type for two important classes Food and Order. 

struct Order
{
    struct Food *items;
    int items_size;
    int priority;
    int max_time_wait;
} Order;

struct Food
{
    int id;
    int preparation_time;
    int complexity;
    char cooking_apparatus[10];
} Food;

// created a list of orders with the given information to us (preparation time, complexity, cooking apparatus).

void set_dishes(struct Food *bookOfDishes)
{
    bookOfDishes[0].preparation_time = 20;
    bookOfDishes[0].complexity = 2;
    bookOfDishes[0].cooking_apparatus = "oven";
    bookOfDishes[0].id = 0;

    bookOfDishes[1].preparation_time = 10;
    bookOfDishes[1].complexity = 1;
    bookOfDishes[1].cooking_apparatus = " ";
    bookOfDishes[1].id = 1;

    bookOfDishes[2].preparation_time = 7;
    bookOfDishes[2].complexity = 1;
    bookOfDishes[2].cooking_apparatus = "stove";
    bookOfDishes[2].preparation_time = 2;

    bookOfDishes[3].preparation_time = 32;
    bookOfDishes[3].complexity = 3;
    bookOfDishes[3].cooking_apparatus = " ";
    bookOfDishes[3].id = 3;

    bookOfDishes[4].preparation_time = 35;
    bookOfDishes[4].complexity = 3;
    bookOfDishes[4].cooking_apparatus = "oven";
    bookOfDishes[4].id = 4;

    bookOfDishes[5].preparation_time = 10;
    bookOfDishes[5].complexity = 1;
    bookOfDishes[5].cooking_apparatus = "stove";
    bookOfDishes[5].id = 5;

    bookOfDishes[6].preparation_time = 20;
    bookOfDishes[6].complexity = 2;
    bookOfDishes[6].cooking_apparatus = " ";
    bookOfDishes[6].id = 6;

    bookOfDishes[7].preparation_time = 30;
    bookOfDishes[7].complexity = 2;
    bookOfDishes[7].cooking_apparatus = "oven";
    bookOfDishes[7].id = 7;
}

#endif


