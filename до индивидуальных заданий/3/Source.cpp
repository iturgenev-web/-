#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX 50

void generate(int n, int p, int a[MAX][MAX])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = 0;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (rand() % 100 < p)
                a[i][j] = a[j][i] = 1;
}

void print_matrix(int n, int a[MAX][MAX])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%2d ", a[i][j]);
        printf("\n");
    }
}

int main()
{
    int a[MAX][MAX], b[MAX][MAX], c[MAX][MAX];
    int n, op, p, q;

    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(NULL));

    printf("Введите количество вершин и вероятности в процентах p1 и p2: ");
    if (scanf("%d %d %d", &n, &p, &q) != 3) {
        printf("Ошибка: не удалось прочитать исходные данные.\n");
        return 1;
    }

    if (n < 1 || n > MAX || p < 0 || p > 100 || q < 0 || q > 100) {
        printf("Ошибка: n должно быть 1..%d, вероятности — целые 0..100.\n", MAX);
        return 1;
    }

    generate(n, p, a);
    generate(n, q, b);

    printf("\nМатрица смежности графа G1:\n");
    print_matrix(n, a);

    printf("\nМатрица смежности графа G2:\n");
    print_matrix(n, b);

    printf("\nВыберите операцию:\n");
    printf("  1 — объединение\n");
    printf("  2 — пересечение\n");
    printf("  3 — симметрическая разность\n");
    printf("Номер операции: ");
    if (scanf("%d", &op) != 1 || op < 1 || op > 3) {
        printf("Ошибка: неизвестная операция.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (op == 1)
                c[i][j] = a[i][j] || b[i][j];
            else if (op == 2)
                c[i][j] = a[i][j] && b[i][j];
            else
                c[i][j] = a[i][j] != b[i][j];
        }

    printf("\nРезультат:\n");
    print_matrix(n, c);

    return 0;
}