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

struct node* get_struct()
{
    struct node* p = NULL;
    char s[256];

    p = (struct node*)malloc(sizeof(struct node));
    printf("Введите значение элемента: \n");
    scanf("%255s", s);

    strcpy(p->inf, s);
    p->next = NULL;

    return p;
}



void push()
{
    struct node* p = get_struct();

    p->next = head;             
    head = p;                  
}


void pop()
{
    struct node* p;

    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    p = head;
    printf("Извлечён элемент: %s\n", p->inf);

    head = head->next;         
    free(p);
}


void review()
{
    struct node* struc = head;

    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    printf("Стек (вершина -> основание):\n");
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
}


void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    push();
    push();
    push();
    review();
    pop();
    pop();
    review();
    clear();

}