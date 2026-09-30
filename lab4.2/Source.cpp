#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
    if (r == NULL)
    {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL)
        {
            printf("Ошибка выделения памяти");
            exit(0);
        }
        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;
        if (data > root->data) root->left = r;
        else root->right = r;
        return r;
    }
    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);
    return root;
}

void print_tree(struct Node* r, int l)
{
    if (r == NULL) return;
    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++)
        printf(" ");
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

/* Задание 2: сколько раз встречается элемент */
int CountOccurrences(struct Node* r, int data)
{
    if (r == NULL)
        return 0;
    int count = 0;
    if (r->data == data)
        count = 1;
    count += CountOccurrences(r->left, data);
    count += CountOccurrences(r->right, data);
    return count;
}

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int D, start = 1;
    root = NULL;

    printf("2 - Посчитать, сколько раз заданное число встречается в дереве\n");
    while (start)
    {
        printf("Введите число: ");
        scanf_s("%d", &D);
        if (D == -1)
        {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else
            root = CreateTree(root, root, D);
    }

    print_tree(root, 0);

    printf("\nВведите значение для подсчёта вхождений: ");
    scanf_s("%d", &D);
    printf("Значение %d встречается в дереве %d раз(а).\n", D, CountOccurrences(root, D));

    scanf_s("%d", &D);
    return 0;
}