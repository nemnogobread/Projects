// в ходе работы программы предпологается, что работа идёт только с неотрицательными числами
// в противном случае, нужно подправить main и функцию dequeue 

#include "stdio.h"
#include "stdlib.h"
#include "inttypes.h"

typedef struct Queue
{
    int *data;  // вектор с данными
    int head;   // номер первого элемента в очереди
    int tail;   // номер последнего элемента в очереди
    int count;  // размер очереди
    int size;   // текущий размер вектора
}Queue;

Queue *init(size_t size);               // инициализация очереди
void enqueue(Queue *q, int a);          // добавление в конец очереди
void reallocate_memory(Queue *q);       // перевыделение памяти, в случае переполнения *data
int dequeue(Queue *q);                  // удаление из начала очереди         
void print_queue(Queue *q);             // печать очереди                
void print_data(Queue *q);              // вспомогательная функция, печать всего массива data                    

int main()
{
    int test[] = {1, 2, 3, 4, 5, 6, 7};  
    uint8_t size = 2;                                 
    Queue *q = init(size);
    print_queue(q);
    for (int i = 0; i < sizeof(test)/sizeof(test[0]); i++)                        
    {
        enqueue(q, test[i]);                         
        printf("queue has next structure: ");
        print_queue(q);
        printf("data has next structure:  ");
        print_data(q);
        printf("\n");
    }
    
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

Queue *init(size_t size)                                
{
    Queue *q = (Queue*)malloc(sizeof(Queue));        // выделение памяти под очередь   
    q->data = (int*)calloc(size, sizeof(int));       // выделение памяти под массив data. изначально он заполнится нулями
    q->head = q->tail = q->count = 0;
    q->size = size;
    return q;
}

void print_queue(Queue *q)
{
    if (q->count == 0)
        printf("No elements in queue");

    for (int i = 0; i < q->count; i++)
    {
        printf("%d ", q->data[i + q->head]);
    }
    printf("\n");
}

void reallocate_memory(Queue *q)
{
    int *temp = (int*)calloc((q->size)*2, sizeof(int));     // создание нового массива, в 2 раза больше старого
    for (int i = 0; i < q->count; i++)                      // копия данных из очереди в новый массив
    {
        temp[i] = q->data[i + q->head];
    }
    free(q->data);                                          // освобождение памяти из-под старого массива
    q->data = temp;                                         // перенос указателя на data на новый массив 
    q->head = 0;
    q->tail = q->count - 1;
    q->size *= 2;                                           
}

void enqueue(Queue *q, int a)                         
{
    if (q->count == 0)
    {
        q->data[q->tail] =  a;
        q->count++;
        return;
    }

    if (q->tail == q->size - 1)                             // перевыделение памяти, если последний элемент очереди является последний в data
        reallocate_memory(q);

    q->data[q->tail + 1] = a;
    q->count++;
    q->tail++;
}

int dequeue(Queue *q)                                 
{
    if (q->count == 0)
    {
        printf("Can't remove element, the queue is empty\n");
        return -1;
    }
    int res = q->data[q->head];
    if (q->head == q->tail)                                 // в случае, если удаляется последний элемент, то tail вместе с head перейдут вместе, а не только head
        q->tail++;
    q->head++;
    q->count--;
    return res;
}

void print_data(Queue *q)                              
{
    for (int i = 0; i < q->size; i++)
    {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}
