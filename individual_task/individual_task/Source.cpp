#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

double get_time() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

// Структура для списка смежности
typedef struct Node {
    int v;
    struct Node* next;
} Node;

// МАТРИЦА СМЕЖНОСТИ: Рекурсивный DFS
void DFS_recursive(int v, int n, int** G, bool* NUM, int* order, int* idx) {
    NUM[v] = true;
    order[(*idx)++] = v;

    for (int i = 0; i < n; i++) {
        if (G[v][i] == 1 && !NUM[i]) {
            DFS_recursive(i, n, G, NUM, order, idx);
        }
    }
}

void POG_recursive(int start_v, int n, int** G, int* order) {
    bool* NUM = (bool*)calloc(n, sizeof(bool));
    int idx = 0;

    DFS_recursive(start_v, n, G, NUM, order, &idx);
    for (int i = 0; i < n; i++) {
        if (!NUM[i]) {
            DFS_recursive(i, n, G, NUM, order, &idx);
        }
    }
    free(NUM);
}

// --- МАТРИЦА СМЕЖНОСТИ: Нерекурсивный DFS ---
void DFS_iterative(int start, int n, int** G, bool* NUM, int* order, int* idx) {
    int* stack = (int*)malloc(n * sizeof(int));
    int top = -1;

    stack[++top] = start;
    NUM[start] = true;
    order[(*idx)++] = start;

    while (top >= 0) {
        int v = stack[top];
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (G[v][i] == 1 && !NUM[i]) {
                NUM[i] = true;
                order[(*idx)++] = i;
                stack[++top] = i;
                found = true;
                break;
            }
        }

        if (!found) {
            top--;
        }
    }
    free(stack);
}

void POG_iterative(int start_v, int n, int** G, int* order) {
    bool* NUM = (bool*)calloc(n, sizeof(bool));
    int idx = 0;

    DFS_iterative(start_v, n, G, NUM, order, &idx);
    for (int i = 0; i < n; i++) {
        if (!NUM[i]) {
            DFS_iterative(i, n, G, NUM, order, &idx);
        }
    }
    free(NUM);
}

// --- СПИСКИ СМЕЖНОСТИ: Рекурсивный DFS ---
void DFS_list_recursive(int v, Node** adj, bool* NUM, int* order, int* idx) {
    NUM[v] = true;
    order[(*idx)++] = v;

    for (Node* cur = adj[v]; cur != NULL; cur = cur->next) {
        if (!NUM[cur->v]) {
            DFS_list_recursive(cur->v, adj, NUM, order, idx);
        }
    }
}

void POG_list_recursive(int start_v, int n, Node** adj, int* order) {
    bool* NUM = (bool*)calloc(n, sizeof(bool));
    int idx = 0;

    DFS_list_recursive(start_v, adj, NUM, order, &idx);
    for (int i = 0; i < n; i++) {
        if (!NUM[i]) {
            DFS_list_recursive(i, adj, NUM, order, &idx);
        }
    }
    free(NUM);
}

// --- СПИСКИ СМЕЖНОСТИ: Нерекурсивный DFS ---
void DFS_list_iterative(int start, int n, Node** adj, bool* NUM, int* order, int* idx) {
    int* stack = (int*)malloc(n * sizeof(int));
    int top = -1;

    stack[++top] = start;
    NUM[start] = true;
    order[(*idx)++] = start;

    while (top >= 0) {
        int v = stack[top];
        bool found = false;

        for (Node* cur = adj[v]; cur != NULL; cur = cur->next) {
            if (!NUM[cur->v]) {
                NUM[cur->v] = true;
                order[(*idx)++] = cur->v;
                stack[++top] = cur->v;
                found = true;
                break;
            }
        }

        if (!found) {
            top--;
        }
    }
    free(stack);
}

void POG_list_iterative(int start_v, int n, Node** adj, int* order) {
    bool* NUM = (bool*)calloc(n, sizeof(bool));
    int idx = 0;

    DFS_list_iterative(start_v, n, adj, NUM, order, &idx);
    for (int i = 0; i < n; i++) {
        if (!NUM[i]) {
            DFS_list_iterative(i, n, adj, NUM, order, &idx);
        }
    }
    free(NUM);
}

void print_order(int* order, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", order[i] + 1);
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "russian");
    int n, p, start_v;

    printf("Введите количество вершин: ");
    scanf("%d", &n);
    printf("Введите вероятность появления ребра в процентах: ");
    scanf("%d", &p);
    printf("Введите начальную вершину (от 1 до %d): ", n);
    scanf("%d", &start_v);
    start_v--; // переход к индексации с 0

    int** G = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        G[i] = (int*)malloc(n * sizeof(int));
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        G[i][i] = 0;
        for (int j = i + 1; j < n; j++) {
            if (rand() % 100 < p) {
                G[i][j] = G[j][i] = 1;
            }
            else {
                G[i][j] = G[j][i] = 0;
            }
        }
    }

    // Построение списков смежности из матрицы G
    Node** adj = (Node**)malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        adj[i] = NULL;
        for (int j = n - 1; j >= 0; j--) {
            if (G[i][j] == 1) {
                Node* node = (Node*)malloc(sizeof(Node));
                node->v = j;
                node->next = adj[i];
                adj[i] = node;
            }
        }
    }

    printf("\nМатрица смежности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }

    printf("\nСписки смежности:\n");
    for (int i = 0; i < n; i++) {
        printf("%d: ", i + 1);
        for (Node* cur = adj[i]; cur != NULL; cur = cur->next) {
            printf("%d -> ", cur->v + 1);
        }
        printf("NULL\n");
    }

    int* order = (int*)malloc(n * sizeof(int));
    double t1, t2;

    printf("\nРекурсивный DFS (матрица смежности):\n");
    t1 = get_time();
    POG_recursive(start_v, n, G, order);
    t2 = get_time();
    print_order(order, n);
    printf("Время: %.6f сек.\n", t2 - t1);

    printf("\nНерекурсивный DFS (матрица смежности):\n");
    t1 = get_time();
    POG_iterative(start_v, n, G, order);
    t2 = get_time();
    print_order(order, n);
    printf("Время: %.6f сек.\n", t2 - t1);

    printf("\nРекурсивный DFS (списки смежности):\n");
    t1 = get_time();
    POG_list_recursive(start_v, n, adj, order);
    t2 = get_time();
    print_order(order, n);
    printf("Время: %.6f сек.\n", t2 - t1);

    printf("\nНерекурсивный DFS (списки смежности):\n");
    t1 = get_time();
    POG_list_iterative(start_v, n, adj, order);
    t2 = get_time();
    print_order(order, n);
    printf("Время: %.6f сек.\n", t2 - t1);

    return 0;
}