#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct node
{
	char inf[256];  
	struct node* next; 
	int priority; 
};

struct node* head = NULL, * last = NULL; 
void spstore(void), review(void), del(char* name);
struct node* get_struct(void); 



struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: \n");   
	scanf("%s", s);
	printf("Введите приоритет объекта: \n");
	scanf("%d", &p->priority);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);

	p->next = NULL;

	return p;		
}

void spstore(void)
{
	struct node* p = NULL;
	struct node* current = head;
	p = get_struct();
	if (head == NULL) 
	{
		head = p;
		last = p;
	}
	else if (p->priority > head->priority)
	{
		p->next = head;
		head = p;
	}
	else
	{
		while (current-> next != NULL && current->next->priority >= p->priority)
		{
			current = current->next;
		}
		p->next = current->next;
		current->next = p;
		if (p->next == NULL)
		{
			last = p;
		}
	}
	return;
}


/* Просмотр содержимого списка. */
void review(void)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("Имя - %s, приоритет - %d \n", struc->inf, struc->priority);
		struc = struc->next;
	}
	return;
}

void del(char* name)
{
	struct node* struc = head;
	struct node* prev = NULL;
	int flag = 0;

	if (head == NULL)
	{
		printf("Список пуст\n");
		return;
	}

	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			flag = 1;
			if (prev == NULL)
				head = struc->next;      // удаляем голову
			else
				prev->next = struc->next; // удаляем середину/хвост

			if (struc == last)
				last = prev;             // обновляем last

			struct node* tmp = struc;
			struc = struc->next;
			free(tmp);
			// prev НЕ двигаем — он остаётся указывать на предыдущий
		}
		else
		{
			prev = struc;
			struc = struc->next;
		}
	}

	if (flag == 0)
		printf("Элемент не найден\n");
}

void main() {
	char name[256];

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	spstore();
	spstore();
	spstore();

	review();

	printf("Введите имя для удаления: ");
	scanf("%s", name);
	del(name);
	review();
}