#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50
#include <locale.h>

void generate(int n, double p, int a[MAX][MAX])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = 0;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (rand()%101 < p)
                a[i][j] = a[j][i] = 1;
}

// Вывод матрицы смежности
void print_matrix(int n, int a[MAX][MAX])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d", a[i][j]);
            putchar('\n');
    }
}
// Вывод списков смежности (вершины нумеруются с 1) 
void print_lists(int n, int a[MAX][MAX])
{
    for (int i = 0; i < n; i++) {
        printf("%d:", i + 1);
        for (int j = 0; j < n; j++)
            if (a[i][j])
                printf("%d", j + 1);
                putchar('\n');
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int a[MAX][MAX], b[MAX][MAX];
    int n, m;
    double p, q;
    srand(time(NULL));

    printf("Введите количество вершин графов G1 и G2 (1..%d): ", MAX);
    if (scanf("%d %d", &n, &m) != 2)
        return 1;

    printf("Введите вероятности появления ребра p1 и p2 в процентах: ");
    if (scanf("%lf %lf", &p, &q) != 2)
        return 1;

    generate(n, p, a);
    generate(m, q, b);

    printf("\nМатрица смежности графа G1:\n");
    print_matrix(n, a);

    printf("\nМатрица смежности графа G2:\n");
    print_matrix(m, b);

    printf("\nСписки смежности графа G1:\n");
    print_lists(n, a);

    printf("\nСписки смежности графа G2:\n");
    print_lists(m, b);

    return 0;
}
