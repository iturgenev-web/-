#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

// --- ЗАДАНИЕ 1: Рекурсивный DFS ---
void DFS_recursive(int v, int n, int** G, bool* NUM) {
    NUM[v] = true;
    printf("%d ", v + 1);

    for (int i = 0; i < n; i++) {
        if (G[v][i] == 1 && !NUM[i]) {
            DFS_recursive(i, n, G, NUM);
        }
    }
}

void POG_recursive(int n, int** G) {
    bool* NUM = (bool*)malloc(n * sizeof(bool));
    for (int i = 0; i < n; i++) {
        NUM[i] = false;
    }

    for (int i = 0; i < n; i++) {
        if (!NUM[i]) {
            DFS_recursive(i, n, G, NUM);
        }
    }
    printf("\n");
    free(NUM);
}

// --- ЗАДАНИЕ 2*: Нерекурсивный DFS ---
void DFS_iterative(int start, int n, int** G, bool* NUM) {
    int* stack = (int*)malloc(n * sizeof(int));
    int top = -1;

    stack[++top] = start;
    NUM[start] = true;
    printf("%d ", start + 1);

    while (top >= 0) {
        int v = stack[top];
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (G[v][i] == 1 && !NUM[i]) {
                NUM[i] = true;
                printf("%d ", i + 1);
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

void POG_iterative(int n, int** G) {
    bool* NUM = (bool*)malloc(n * sizeof(bool));
    for (int i = 0; i < n; i++) {
        NUM[i] = false;
    }

    for (int i = 0; i < n; i++) {
        if (!NUM[i]) {
            DFS_iterative(i, n, G, NUM);
        }
    }
    printf("\n");
    free(NUM);
}

int main() {
    setlocale(LC_ALL, "russian");
    int n, p;
    printf("Введите количество вершин: ");
    scanf("%d", &n);
    printf("Введите количество вероятность появления ребра в процентах: ");
    scanf("%d", &p);
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

    printf("\nМатрица смежности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }

    printf("\nРекурсивный DFS (Задание 1):\n");
    POG_recursive(n, G);

    printf("\nНерекурсивный DFS (Задание 2*):\n");
    POG_iterative(n, G);

    return 0;
}