#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define MAX 20
#define MAXV (MAX * MAX)

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
            printf("%d ", a[i][j]);
        putchar('\n');
    }
}

void print_product(int n, int a[MAXV][MAXV])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", a[i][j]);
        putchar('\n');
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int a[MAX][MAX], b[MAX][MAX];
    int c[MAXV][MAXV];
    int n, m, N;
    double p, q;

    srand((unsigned)time(NULL));

    printf("Введите число вершин и вероятность p1 в процентах для графа G1: ");
    if (scanf("%d %lf", &n, &p) != 2)
        return 1;

    printf("Введите число вершин и вероятность p2 в процентах для графа G2: ");
    if (scanf("%d %lf", &m, &q) != 2)
        return 1;

    generate(n, p, a);
    generate(m, q, b);

    printf("\nМатрица смежности графа G1:\n");
    print_matrix(n, a);

    printf("\nМатрица смежности графа G2:\n");
    print_matrix(m, b);

    N = n * m;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            int x = i / m, y = i % m;   // вершина i = (x, y)
            int z = j / m, w = j % m;   // вершина j = (z, w)
            c[i][j] = (x == z && b[y][w]) || (y == w && a[x][z]);
        }
    printf("\nМатрица смежности декартова произведения (вершин: %d):\n", N);
    print_product(N, c);

    return 0;
}
