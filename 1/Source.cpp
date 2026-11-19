#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int** generateGraph(int n, int p) {
    int** G = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++) {
        G[i] = (int*)calloc(n, sizeof(int));
    }

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
    return G;
}

void printMatrix(int** G, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}

void bfs(int** G, int n, int start) {
    int* visited = (int*)calloc(n, sizeof(int));
    int* queue = (int*)malloc(n * sizeof(int));
    int head = 0, tail = 0;

    visited[start] = 1;
    queue[tail++] = start;

    printf("Обход в ширину: ");
    while (head < tail) {
        int v = queue[head++];
        printf("%d ", v);
        for (int u = 0; u < n; u++) {
            if (G[v][u] && !visited[u]) {
                visited[u] = 1;
                queue[tail++] = u;
            }
        }
    }
    printf("\n");

    free(visited);
    free(queue);
}

void freeGraph(int** G, int n) {
    for (int i = 0; i < n; i++) {
        free(G[i]);
    }
    free(G);
}

int main(void) {
    setlocale(LC_ALL, "");

    int n, percent;

    printf("Введите количество вершин: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Ошибка: введите положительное целое число.\n");
        return 1;
    }

    printf("Введите вероятность ребра в процентах (0-100): ");
    if (scanf("%d", &percent) != 1 || percent < 0 || percent > 100) {
        fprintf(stderr, "Ошибка: введите целое число от 0 до 100.\n");
        return 1;
    }

    srand((unsigned)time(NULL));

    int** graph = generateGraph(n, percent);
    printMatrix(graph, n);
    bfs(graph, n, 0);
    freeGraph(graph, n);

    return 0;
}