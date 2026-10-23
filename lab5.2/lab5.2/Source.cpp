#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void main() {
    setlocale(LC_ALL, "russian");
    int a[100][100] = { 0 };
    int degree[100] = { 0 };
    int n, m = 0;
    int found, k = 0;

    srand(time(NULL));

    printf("Введите количество вершин: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 100)
    {
        printf("Некорректное количество вершин!\n");
    }
    else {
        // Генерация матрицы смежности
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
                printf("%d ", a[i][j]);

            printf("\n");
        }

        // Подсчет количества ребер
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
                m += a[i][j];
        }

        printf("\nРазмер графа: %d\n", m);

        // ЗАДАНИЕ 2
        // Создание матрицы инцидентности
        int cols = (m > 0) ? m : 1;
        int* b = (int*)calloc((size_t)n * cols, sizeof(int));

        // Заполнение матрицы инцидентности
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (a[i][j] == 1)
                {
                    b[i * cols + k] = 1;
                    b[j * cols + k] = 1;
                    k++;
                }
            }
        }

        // Вывод матрицы инцидентности
        printf("\nМатрица инцидентности:\n");

        if (m == 0)
        {
            printf("В графе нет ребер.\n");
        }
        else
        {
            printf("     ");
            for (int j = 0; j < m; j++)
                printf("%3d", j + 1);

            printf("\n");

            for (int i = 0; i < n; i++)
            {
                printf("v%-3d ", i + 1);

                for (int j = 0; j < m; j++)
                    printf("%3d", b[i * cols + j]);

                printf("\n");
            }
        }

        // Определение размера графа
        // по матрице инцидентности
        int sum = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                sum += b[i * cols + j];
                degree[i] += b[i * cols + j];
            }
        }

        printf("\nРазмер графа по матрице инцидентности: %d\n",
            sum / 2);

        // Поиск изолированных вершин
        printf("\nИзолированные вершины: ");
        found = 0;

        for (int i = 0; i < n; i++)
        {
            if (degree[i] == 0)
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
            if (degree[i] == 1)
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
            if (degree[i] == n - 1)
            {
                printf("%d ", i + 1);
                found = 1;
            }
        }

        if (!found)
            printf("нет");

        printf("\n");

        free(b);
    }
}