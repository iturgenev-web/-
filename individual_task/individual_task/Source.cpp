#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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
	int flag;

	p = (node*)malloc(sizeof(struct node));

	printf("Введите название объекта: \n");
	scanf("%s", s);
	printf("Введите приоритет объекта: \n");
	scanf("%d", &flag);
	while (flag < 1) 
	{
		printf("Максимальный приоритет - 1, введи другой приоритет: \n");
		scanf("%d", &flag);
	}
	p->priority = flag;
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
	else if (p->priority < head->priority)
	{
		p->next = head;
		head = p;
	}
	else
	{
		while (current->next != NULL && current->next->priority <= p->priority)
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
				head = struc->next;      
			else
				prev->next = struc->next; 

			if (struc == last)
				last = prev;             

			struct node* tmp = struc;
			struc = struc->next;
			free(tmp);
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
void change(char* name, int new_priority)
{
	struct node* struc = head;
	int flag = 0;

	if (head == NULL) { printf("Список пуст\n"); return; }

	/* ПРОХОД 1: меняем приоритеты на месте */
	while (struc)
	{
		if (strstr(struc->inf, name) != NULL)
		{
			struc->priority = new_priority;
			flag = 1;
		}
		struc = struc->next;
	}

	if (!flag) { printf("Элемент не найден\n"); return; }

	/* ПРОХОД 2: пересортировка — вынимаем из head и вставляем в sorted */
	struct node* sorted = NULL;
	struct node* sorted_last = NULL;

	while (head)
	{
		struc = head;
		head = head->next;

		if (sorted == NULL || struc->priority < sorted->priority)
		{
			struc->next = sorted;
			sorted = struc;
			if (sorted_last == NULL) sorted_last = struc;
		}
		else
		{
			struct node* current = sorted;
			while (current->next != NULL &&
				current->next->priority <= struc->priority)
				current = current->next;
			struc->next = current->next;
			current->next = struc;
			if (struc->next == NULL) sorted_last = struc;
		}
	}

	head = sorted;
	last = sorted_last;

	printf("Приоритет всех \"%s\" изменён на %d\n", name, new_priority);
}

void main() {
	setlocale(LC_ALL, "Russian");
	char name[256];
	int choice, new_priority;
	do
	{
		printf("Меню программы\n");
		printf("1 - Добавить элемент\n");
		printf("2 - Извлечь элемент\n");
		printf("3 - Просмотреть очередь\n");
		printf("4 - Изменить приоритет\n");
		printf("5 - Выход\n");
		printf("Выбор:\n");
		scanf("%d", &choice);
		switch (choice) {
			case 1: spstore(); 
					break;
			case 2:
				printf("Введите имя для удаления: ");
				scanf("%s", name);
				del(name);
				break;
			case 3: 
				review();
				break;
			case 4:
				printf("Введите название элемента, которому хотите поменять приоритет\n");
				scanf("%s", name);
				printf("Введите новый приоритет\n");
				scanf("%d", &new_priority);
				change(name, new_priority);
			case 5: break;
			default: printf("Неверный выбор меню\n");
		}
	} while (choice != 5);
}