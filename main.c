#include "dishesOrders.h"
#include "queue.h"


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct Order orders[10]; // defined number of orders = 10
struct Queue *queue;


int nr_order = 1;
int pending_orders[3];

const struct Food bookOfDishes[8]; // declare as a constant that we have 8 dishes in our list of orders

int receive_max_time_wait(struct Order order) // calculates time to wait for an order
{
    int j;
    int time = 0;

    for (j = 0; j < order.items_size; j++)
    {
        if (time < order.items[j].preparation_time)
        {
            time = order.items[j].preparation_time;
        }
    }

    return time * 1.3;
}

int receive_preparation_time(int id, struct Food *bookOfDishes)
{
    int j, time;
    for (j = 0; j < 8; j++)
    {
        if (id == bookOfDishes[j].id) // In order with the id of the ordered dishes gets the preparation_time value from dishesOrders.h
        {
            time = bookOfDishes[j].preparation_time;
        }
    }

    return time;
}

void *cook(void *cook_id) 
{
    int id = (int)cook_id;

    int i;
    struct Order *order_temp;
    struct QueueNode *food_id;

    while (1)
    {
        pthread_mutex_lock(&mutex);

        food_id = deQueue(queue);

        pthread_mutex_unlock(&mutex);
        if (food_id == NULL)
        {
            pthread_mutex_lock(&mutex);

            order_temp = pop(h);
            if (order_temp != -1)
            {
                for (i = 0; i < (*order_temp).items_size; i++)
                {
                    enQueue(queue, (int)(*order_temp).items[i].id, nr_order);
                }
                nr_order += 1;
            }

            pthread_mutex_unlock(&mutex);
        }
        else
        {
            printf("\nCook : %d id working %d : time on an order : %d", id, bookOfDishes[food_id->key].preparation_time, food_id->order);
            pending_orders[id] = (int)food_id->order;

            sleep(((int)bookOfDishes[food_id->key].preparation_time)/3);

            pending_orders[id] = -1;
        }
    }

    pthread_exit(NULL);
}

void *waitress(void *waitress_id) 
{
    int id = (int)waitress_id;

    int i, y, random_time, random_items, random_id, random_priority;

    for (i = 0; i < 10; i++)
    {
        random_items    = rand() % 4 + 1;
        orders[i].items = (struct Food*) malloc(random_items * sizeof(struct Food));
        for (y = 0; y < random_items; y++)
        {
            random_id = rand() % 8 + 1;

            orders[i].items[y].id               = bookOfDishes[random_id].id;
            orders[i].items[y].preparation_time = bookOfDishes[random_id].preparation_time;
            orders[i].items[y].complexity       = bookOfDishes[random_id].complexity;
            orders[i].items[y].cooking_apparatus= bookOfDishes[random_id].cooking_apparatus;
        }

        orders[i].items_size = random_items;
        random_priority      = rand() % 5 + 1;
        orders[i].priority   = random_priority;
        orders[i].max_time_wait   = receive_max_time_wait(orders[i]);

        pthread_mutex_lock(&mutex);
        push(h, orders[i].priority, &orders[i]);
        pthread_mutex_unlock(&mutex);
        printf("\nAnother Order is here ");
        sleep((rand() % (4 + 1 - 2)) + 2);
    }

    pthread_exit(NULL);
}

void *checker(void *checker_id)
{
    int id = (int)checker_id;
    int food_id = 1;
    int last_order = 0;

    while(1)
    {
        while(pending_orders[0] != 0 || pending_orders[1] != 0 || pending_orders[2] != 0)
        {
            if (pending_orders[0] == -1 && pending_orders[1] == -1 && pending_orders[2] == -1 && last_order)
            {
                // is waiting for other orders
            }
            else if (pending_orders[0] == -1 && pending_orders[1] == -1 && pending_orders[2] == -1 && !last_order)
            {
                printf("\nOrder %d is ready\n", food_id);
                last_order = 1;
            }
            else if (pending_orders[0] != food_id && pending_orders[1] != food_id && pending_orders[2] != food_id)
            {
                printf("\nOrder %d is ready\n", food_id);
                food_id += 1;
                last_order = 0;
            }
        }
    }
}

int main()
{
    pthread_t cook_threads[3], waitress_thread, checker_thread; // declare 3 threads for cook, 1 for waitress and 1 for checker
    int i, thread_error;
    srand((unsigned)time(NULL));

    set_dishes(&bookOfDishes); // calls the function from queue header , which creates the list with pending_orders

    h     = (heap_t *)calloc(1, sizeof (heap_t)); // allocate memory 
    queue = createQueue();  // calls the function which creates queue

    pending_orders[0] = 0;
    pending_orders[1] = 0;
    pending_orders[2] = 0;

    for (i = 0; i < 3; i++)
    {
        thread_error = pthread_create(&cook_threads[i], NULL, cook, (void *)i);
        if (thread_error)
        {
            printf("ERROR; return code from pthread_create() is %d\n", thread_error);
            exit(-1);
        }
    }

    thread_error = pthread_create(&waitress_thread, NULL, waitress, (void *)0);
    if (thread_error)
    {
        printf("ERROR; return code from pthread_create() is %d\n", thread_error);
        exit(-1);
    }

    thread_error = pthread_create(&checker_thread, NULL, checker, (void *)0);
    if (thread_error)
    {
        printf("ERROR; return code from pthread_create() is %d\n", thread_error);
        exit(-1);
    }

    pthread_join(cook_threads[0], NULL);
    pthread_join(cook_threads[1], NULL);
    pthread_join(cook_threads[2], NULL);
    pthread_join(waitress_thread, NULL);
    pthread_join(checker_thread, NULL);
    return 0;
}