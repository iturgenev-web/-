#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_matrix(int* m, int n)
{
    for (int i = 0; i < n * n; i++)
        m[i] = rand() % 100 + 1;
}

int main()
{
    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
    int count_sizes = sizeof(sizes) / sizeof(sizes[0]);

    srand((unsigned)time(NULL));

    printf("N\tProgram_Time\tMultiply_Time\n");

    for (int s = 0; s < count_sizes; s++)
    {
        int N = sizes[s];

        clock_t program_start, program_end;
        clock_t mult_start, mult_end;

        program_start = clock();

        int* A = (int*)malloc(N * N * sizeof(int));
        int* B = (int*)malloc(N * N * sizeof(int));
        int* C = (int*)malloc(N * N * sizeof(int));

        if (A == NULL || B == NULL || C == NULL)
        {
            printf("Memory allocation error for N = %d\n", N);

            free(A);
            free(B);
            free(C);

            continue;
        }

        fill_matrix(A, N);
        fill_matrix(B, N);

        mult_start = clock();

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int sum = 0;

                for (int r = 0; r < N; r++)
                {
                    sum += A[i * N + r] * B[r * N + j];
                }

                C[i * N + j] = sum;
            }
        }

        mult_end = clock();

        free(A);
        free(B);
        free(C);

        program_end = clock();

        double program_time =
            (double)(program_end - program_start) / CLOCKS_PER_SEC;

        double multiply_time =
            (double)(mult_end - mult_start) / CLOCKS_PER_SEC;

        printf("%d\t%.6f\t%.6f\n",
            N,
            program_time,
            multiply_time);
    }

    return 0;
}