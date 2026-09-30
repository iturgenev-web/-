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

/* Задание 3*: добавление без дубликатов */
struct Node* CreateTreeNoDup(struct Node* root, struct Node* r, int data)
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
    if (data == r->data)
    {
        printf("Значение %d уже существует в дереве. Добавление отменено.\n", data);
        return root;
    }
    if (data > r->data)
        CreateTreeNoDup(r, r->left, data);
    else
        CreateTreeNoDup(r, r->right, data);
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

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int D, start = 1;
    root = NULL;

    printf("3 - Изменить добавление, чтобы не добавлялись одинаковые значения\n");
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
            root = CreateTreeNoDup(root, root, D);
    }

    print_tree(root, 0);

    scanf_s("%d", &D);
    return 0;
}