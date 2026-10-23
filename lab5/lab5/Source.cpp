#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void main(){
    setlocale(LC_ALL, "russian");
    int a[100][100] = { 0 };
    int n, m = 0;
    int degree;
    int found;

    srand(time(NULL));

    printf("Введите количество вершин: ");
    scanf("%d", &n);

    if (n < 1 || n > 100)
    {
        printf("Некорректное количество вершин!\n");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                a[i][j] = rand() % 2;
                a[j][i] = a[i][j];
            }
        }

        printf("\nМатрица смежности:\n");

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        // 2. Определение размера графа
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (a[i][j] == 1)
                    m++;
            }
        }

        printf("\nПорядок графа: %d\n", n);
        printf("Размер графа: %d\n", m);

        // 3. Поиск изолированных вершин
        printf("\nИзолированные вершины: ");
        found = 0;

        for (int i = 0; i < n; i++)
        {
            degree = 0;

            for (int j = 0; j < n; j++)
                degree += a[i][j];

            if (degree == 0)
            {
                printf("%d ", i + 1);
                found = 1;
            }
        }

        if (!found)
            printf("нет");

        // Поиск концевых вершин
        printf("\nКонцевые вершины: ");
        found = 0;

        for (int i = 0; i < n; i++)
        {
            degree = 0;

            for (int j = 0; j < n; j++)
                degree += a[i][j];

            if (degree == 1)
            {
                printf("%d ", i + 1);
                found = 1;
            }
        }

        if (!found)
            printf("нет");

        // Поиск доминирующих вершин
        printf("\nДоминирующие вершины: ");
        found = 0;

        for (int i = 0; i < n; i++)
        {
            degree = 0;

            for (int j = 0; j < n; j++)
                degree += a[i][j];

            if (degree == n - 1)
            {
                printf("%d ", i + 1);
                found = 1;
            }
        }

        if (!found)
            printf("нет");

        printf("\n");
    }
}
