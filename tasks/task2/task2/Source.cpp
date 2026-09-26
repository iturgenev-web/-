#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct node
{
    char inf[256];          
    struct node* next;         
};

struct node* head = NULL;       
struct node* last = NULL;                      

struct node* get_struct()
{
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите значение элемента: \n");
    scanf("%255s", s);

    strcpy(p->inf, s);
    p->next = NULL;

    return p;
}


void enqueue()
{
    struct node* p = get_struct();

    if (head == NULL)          
    {
        head = p;
        last = p;
    }
    else                        
    {
        last->next = p;
        last = p;
    }
}

void dequeue()
{
    struct node* p;

    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    p = head;
    printf("Извлечён элемент: %s\n", p->inf);

    head = head->next;
    if (head == NULL)           
        last = NULL;

    free(p);
}

void review()
{
    struct node* struc = head;

    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    printf("Очередь (начало -> конец):\n");
    while (struc != NULL)
    {
        printf("  %s\n", struc->inf);
        struc = struc->next;
    }
}

void clear()
{
    struct node* p = head;
    struct node* tmp;

    while (p != NULL)
    {
        tmp = p->next;
        free(p);
        p = tmp;
    }

    head = NULL;
    last = NULL;
}


void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    enqueue();
    enqueue();
    enqueue();
    review();
    dequeue();
    dequeue();
    review();
    clear();

}