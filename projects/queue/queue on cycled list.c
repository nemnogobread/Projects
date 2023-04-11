// в ходе работы программы предпологается, что работа идёт только с неотрицательными числами
// в противном случае, нужно подправить main и функцию dequeue 

#include "stdio.h"
#include "stdlib.h"
#include "inttypes.h"

typedef struct Queue
{
    int *data;  // массив, который мы замкнём в процессе реализации
    int head;   // номер первого элемента в очереди
    int tail;   // номер последнего элемента в очереди
    int count;  // кол-во элементов в очереди
    int max;    // максимальный размер очереди
}Queue;

Queue *init(size_t size);                               // инициализация очереди размера size
void enqueue(Queue *q, int a);                          // добавление в конец очереди
int dequeue(Queue *q);                                  // удаление из начала очереди
void print_queue(Queue *q);                             // печать очереди
void print_data(Queue *q);                              // вспомогательная функция, печать всего массива data        

int main()
{
    int test[] = {1, 2, 3, 4, 5, 6};  
    uint8_t size;
    printf("Please, enter max size of queue: ");
    scanf("%d", &size);                                 // чтобы убедиться в зацикленности массива, набери size = 9
    Queue *q = init(size);

    for (int i = 0; i < 12; i++)                        // советую просто поставить в цикле точку останова и пройтись дебагером, чтобы всё понять
    {
        enqueue(q, test[i%6]);                         
        if (i%2)                                        
            dequeue(q);
        printf("queue has next structure: ");
        print_queue(q);
        printf("data has next structure:  ");
        print_data(q);
        printf("\n");
    }
    printf("\n");

    int local_size = q->count;
    for (int i = 0; i < local_size + 1; i++)
    {
        int temp = dequeue(q);
        if (temp != -1)
        {
            printf("poped element: %d\n", temp);
            printf("queue has next structure: ");
            print_queue(q);
            printf("data has next structure:  ");
            print_data(q);
            printf("\n");
        }
    }
}

Queue *init(size_t size)                                // инициализируем очередь
{
    Queue *q = (Queue*)malloc(sizeof(Queue));           // выделение памяти под очередь
    q->data = (int*)calloc(size, sizeof(int));          // выделение памяти под массив data. изначально он заполнится нулями
    q->head = q->tail = q->count = 0;
    q->max = size;
    return q;
}

void print_queue(Queue *q)
{
    if (q->count == 0)
        printf("No elements in queue");

    for (int i = 0; i < q->count; i++)
    {
        printf("%d ", q->data[(q->head + i) % (q->max)]);
    }
    printf("\n");
}

void enqueue(Queue *q, int a)                           // вставка в очередь
{
    if (q->count == q->max)                             // проверка если очередь переполнена
    {
        fprintf(stderr, "Not enough space in queue\n");
        return;
    }

    if (q->count == 0)                                  // проверка, если очередь пуста
    {
        q->data[q->tail] = a;
        q->count++;
        return;
    }

    q->tail = (q->tail + 1) % q->max;   
    q->data[q->tail] = a;
    q->count++;
}

int dequeue(Queue *q)                                   // удаление элемента из очереди
{
    if (q->count == 0)                                  // проверка, если очередь пуста
    {
        printf("Can't remove element, the queue is empty\n");
        return -1;
    }

    int res = q->data[q->head];
    q->head = (q->head + 1) % q->max;
    q->count--;
    return res;
}

void print_data(Queue *q)                               // печать всего массива data
{
    for (int i = 0; i < q->max; i++)
        printf("%d ", q->data[i]);
    printf("\n");
}
