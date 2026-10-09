#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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

/* Задание: удаление узла с перераспределением */
struct Node* DeleteNode(struct Node* r, int data)
{
    if (r == NULL)
    {
        printf("Значение %d не найдено в дереве.\n", data);
        return NULL;
    }
    if (data > r->data)
    {
        r->left = DeleteNode(r->left, data);
        return r;
    }
    if (data < r->data)
    {
        r->right = DeleteNode(r->right, data);
        return r;
    }

    if (r->left == NULL && r->right == NULL)
    {
        /* Случай 1: лист — просто удаляем */
        free(r);
        return NULL;
    }
    if (r->left == NULL)
    {
        /* Случай 2: один потомок — поднимаем его на место удалённого */
        struct Node* temp = r->right;
        free(r);
        return temp;
    }
    if (r->right == NULL)
    {
        struct Node* temp = r->left;
        free(r);
        return temp;
    }

    /* Случай 3:перераспределение.*/
    struct Node* temp = r->left;
    while (temp->right != NULL)
        temp = temp->right;
    temp->right = r->right;
    temp = r->left;
    free(r);
    return temp;
}

void FreeTree(struct Node* r)
{
    if (r == NULL) return;
    FreeTree(r->left);
    FreeTree(r->right);
    free(r);
}

int main()
{
    setlocale(LC_ALL, "");

    int D, start = 1;
    root = NULL;

    printf("3 -Без дубликатов \n");
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

    printf("\nУдаление узлов (введите -1 для завершения)\n");
    start = 1;
    while (start)
    {
        printf("Введите число для удаления: ");
        scanf_s("%d", &D);
        if (D == -1)
        {
            printf("Удаление окончено\n");
            start = 0;
        }
        else
        {
            root = DeleteNode(root, D);
            printf("\nДерево после удаления:\n");
            if (root == NULL)
                printf("(дерево пусто)\n");
            else
                print_tree(root, 0);
            printf("\n");
        }
    }

    FreeTree(root);
    root = NULL;

    scanf_s("%d", &D);
    return 0;
}
