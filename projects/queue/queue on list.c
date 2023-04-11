// в ходе работы программы предпологается, что работа идёт только с неотрицательными числами
// в противном случае, нужно подправить main и функцию dequeue 

#include "stdio.h"
#include "stdlib.h"

typedef struct Node                 // инициализация узла списка. typedef использован для удобства, не нужно каждый раз писать struct
{
    int data;
    struct Node *next;
}Node;

typedef struct Queue                // инициализация очереди. typedef использован для удобства, не нужно каждый раз писать struct
{
    struct Node *head;              // указатель на начало очереди
    struct Node *tail;              // указатель на конец очереди
}Queue;

void print_queue(Queue *q);         // печать очереди, начиная с головы (head)
void enqueue(Queue *q, int data);   // добавление в конец очереди нового узла со значением data
int dequeue(Queue *q);              // извлечение элемента из начала очереди, возвращает значение этого элемента

int main()
{
    int test[] = {3, 17, 21, 10};
    Queue queue = {NULL, NULL};     // объявление и инициализания очереди, пока head и tail узазывают на NULL 
    
    for (int i = 0; i < sizeof(test)/sizeof(test[0]); i++)
    {
        enqueue(&queue, test[i]);   // добавление в очередь элементов из тестового списка test
        print_queue(&queue);
        printf("date from head: %d \n", *queue.head);           // печать элемента начала очереди
        printf("date from tail: %d \n\n", *queue.tail);         // печать элемента конца очереди
    }

    while (queue.head != NULL)
    {
        int temp = dequeue(&queue);
        if (temp != -1)
        {
            printf("poped element: %d\n", temp);   // добавление в очередь элементов из тестового списка test
            print_queue(&queue);
            if (queue.head != NULL)
            {
                printf("date from head: %d \n", *queue.head);           // печать элемента начала очереди
                printf("date from tail: %d \n\n", *queue.tail);         // печать элемента конца очереди
            }
        } 
    }
    dequeue(&queue);

    printf("\n");
    return 0;
}

void print_queue(Queue *q)
{
    if (q->head == NULL)                                        // проверка пуста ли очередь
        printf("No elements in queue");

    for (Node *p = q->head; p != NULL; p = p->next)             // печать всех элементов. если очередь пуста, то программа вообще на зайдёт в цикл из-за проверки p != NULL 
    {
        printf("%d ", p->data);
    }
    printf("\n");
}

void enqueue(Queue *q, int data)
{
    Node *p = (Node*)malloc(sizeof(Node));                      // выделение памяти под новый узел
    p->data = data;
    p->next = NULL;
    if (q->tail == NULL)                                        // проверка пуста ли очередь
    {
        q->head = p;                                            
        q->tail = p;
    }
    else
    {
        q->tail->next = p;
        q->tail = p;
    }
}

int dequeue(Queue *q)
{
    if (q->head == NULL)                                        // проверка пуста ли очередь
    {
        printf("Can't remove element, the queue is empty");
        return -1;
    }
    Node *temp = q->head;
    int res = q->head->data;
    q->head = q->head->next;
    free(temp);                                                 // освобождение памяти из-под удалённого узла
    return res;
}
