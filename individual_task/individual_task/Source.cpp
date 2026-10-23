#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, "Russian");

    int** a;
    int n, m = 0;
    int degree, in_degree, out_degree, found, pr, choice;

    srand((unsigned int)time(NULL));

    printf("Введите количество вершин: ");
    scanf("%d", &n);
    printf("Введите вероятность появления ребра в процентах: ");
    scanf("%d", &pr);
    printf("Выберите тип графа. Неориентированный - 0. Ориентированный - 1\n");
    scanf("%d", &choice);

    a = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        a[i] = (int*)calloc(n, sizeof(int));
    }

    if (choice == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (rand() % 101 < pr) {
                    a[i][j] = a[j][i] = 1;
                }
            }
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && rand() % 101 < pr) {
                    a[i][j] = 1;
                }
            }
        }
    }

    printf("\nМатрица смежности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    if (choice == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (a[i][j] == 1)
                    m++;
            }
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] == 1)
                    m++;
            }
        }
    }

    printf("\nПорядок графа: %d\n", n);
    printf("Размер графа: %d\n", m);

    // 3. Поиск изолированных вершин
    printf("\nИзолированные вершины: ");
    found = 0;

    for (int i = 0; i < n; i++) {
        degree = 0;
        in_degree = 0;
        out_degree = 0;

        for (int j = 0; j < n; j++) {
            out_degree += a[i][j];
            in_degree += a[j][i];
        }

        if (choice == 0)
            degree = out_degree;
        else
            degree = in_degree + out_degree;

        if (degree == 0) {
            printf("%d ", i + 1);
            found = 1;
        }
    }

    if (!found)
        printf("нет");

    // Поиск концевых вершин
    printf("\nКонцевые вершины: ");
    found = 0;

    for (int i = 0; i < n; i++) {
        degree = 0;
        in_degree = 0;
        out_degree = 0;

        for (int j = 0; j < n; j++) {
            out_degree += a[i][j];
            in_degree += a[j][i];
        }

        if (choice == 0)
            degree = out_degree;
        else
            degree = in_degree + out_degree;

        if (degree == 1) {
            printf("%d ", i + 1);
            found = 1;
        }
    }

    if (!found)
        printf("нет");

    // Поиск доминирующих вершин
    printf("\nДоминирующие вершины: ");
    found = 0;

    for (int i = 0; i < n; i++) {
        degree = 0;

        for (int j = 0; j < n; j++) {
            degree += a[i][j];
        }

        if (degree == n - 1) {
            printf("%d ", i + 1);
            found = 1;
        }
    }

    if (!found)
        printf("нет");

    printf("\n");
    free(a);

    return 0;
}
