#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define MAX 50

void generate(int n, double p, int a[MAX][MAX])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = 0;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (rand() % 101 < p)
                a[i][j] = a[j][i] = 1;
}

void print_matrix(int n, int a[MAX][MAX])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d", a[i][j]);
        putchar('\n');

    }
}

// Удаление изолированных вершин из графа
void remove_isol(int* n, int c[MAX][MAX]) {
    int del[MAX] = { 0 }, idx[MAX], k = 0;
    int t[MAX][MAX];
    for (int i = 0; i < *n; i++) {
        int deg = 0;
        for (int j = 0; j < *n; j++) {
            deg += c[i][j];
        }
        if (deg == 0) {
            del[i] = 1;
        }
    }
    for (int i = 0; i < *n; i++) {
        if (!del[i]) {
            idx[k++] = i;
        }
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            t[i][j] = c[idx[i]][idx[j]];
        }
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            c[i][j] = t[i][j];
        }
    }
    *n = k;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int a[MAX][MAX], b[MAX][MAX], c[MAX][MAX];
    int n, n1, op;
    double p, q;

    srand((unsigned)time(NULL));

    printf("Введите количество вершин n1 и n2 и вероятности p1 и p2: ");
    scanf("%d %d %lf %lf", &n, &n1, &p, &q);


    generate(n, p, a);
    generate(n1, q, b);

    printf("\nМатрица смежности графа G1:\n");
    print_matrix(n, a);

    printf("\nМатрица смежности графа G2:\n");
    print_matrix(n1, b);

    printf("\nВыберите операцию:");
    printf("  1 — объединение");
    printf("  2 — пересечение");
    printf("  3 — симметрическая разность (xor)");
    printf("\nНомер операции: ");
    scanf("%d", &op);

    // операции выполняются по меньшему числу вершин 
    if (n1 < n)
        n = n1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (op == 1)
                c[i][j] = a[i][j] || b[i][j];
            else if (op == 2)
                c[i][j] = a[i][j] && b[i][j];
            else
                c[i][j] = a[i][j] != b[i][j];   // симметрическая разность 
        }

    // При вызове симметрической разности убрать изолированные вершины результата
    if (op == 3) {
        int before = n;
        remove_isol(&n, c);
        printf("\nУдалено изолированных вершин: %d\n", before - n);
    }

    printf("\nРезультат:\n");
    print_matrix(n, c);

    return 0;
}
