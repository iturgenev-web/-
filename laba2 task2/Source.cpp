#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 50000



void shell(int* items, int count)
{
    int i, j, gap, k;
    int x;
    int a[5] = { 9, 5, 3, 2, 1 };

    for (k = 0; k < 5; k++)
    {
        gap = a[k];

        for (i = gap; i < count; i++)
        {
            x = items[i];

            for (j = i - gap;
                (j >= 0) && (x < items[j]);
                j -= gap)
            {
                items[j + gap] = items[j];
            }

            items[j + gap] = x;
        }
    }
}



void qs(int* items, int left, int right)
{
    int i = left;
    int j = right;
    int pivot = items[(left + right) / 2];

    while (i <= j)
    {
        while (items[i] < pivot)
            i++;

        while (items[j] > pivot)
            j--;

        if (i <= j)
        {
            int temp = items[i];
            items[i] = items[j];
            items[j] = temp;

            i++;
            j--;
        }
    }

    if (left < j)
        qs(items, left, j);

    if (i < right)
        qs(items, i, right);
}



int compare(const void* a, const void* b)
{
    int x = *(const int*)a;
    int y = *(const int*)b;

    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}



void fill_random(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000;
}

void fill_ascending(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i;
}

void fill_descending(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

void fill_half_half(int arr[], int n)
{
    int i;

    for (i = 0; i < n / 2; i++)
        arr[i] = i;

    for (i = n / 2; i < n; i++)
        arr[i] = n - i + n / 2;
}



void copy_array(int src[], int dst[], int n)
{
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
}



double test_shell(int arr[], int n)
{
    clock_t start, end;

    start = clock();

    shell(arr, n);

    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

double test_qs(int arr[], int n)
{
    clock_t start, end;

    start = clock();

    qs(arr, 0, n - 1);

    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

double test_qsort(int arr[], int n)
{
    clock_t start, end;

    start = clock();

    qsort(arr, n, sizeof(int), compare);

    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}



int main()
{
    srand((unsigned)time(NULL));

    int sizes[] = { 1000, 5000, 10000, 20000, 50000 };
    int count_sizes = sizeof(sizes) / sizeof(sizes[0]);

    int source[MAX_N];
    int arr1[MAX_N];
    int arr2[MAX_N];
    int arr3[MAX_N];

    printf("===== RANDOM =====\n");

    for (int s = 0; s < count_sizes; s++)
    {
        int n = sizes[s];

        fill_random(source, n);

        copy_array(source, arr1, n);
        copy_array(source, arr2, n);
        copy_array(source, arr3, n);

        printf("N = %d\n", n);

        printf("Shell  : %.6f sec\n",
            test_shell(arr1, n));

        printf("QS     : %.6f sec\n",
            test_qs(arr2, n));

        printf("qsort  : %.6f sec\n\n",
            test_qsort(arr3, n));
    }

    printf("\n===== ASCENDING =====\n");

    for (int s = 0; s < count_sizes; s++)
    {
        int n = sizes[s];

        fill_ascending(source, n);

        copy_array(source, arr1, n);
        copy_array(source, arr2, n);
        copy_array(source, arr3, n);

        printf("N = %d\n", n);

        printf("Shell  : %.6f sec\n",
            test_shell(arr1, n));

        printf("QS     : %.6f sec\n",
            test_qs(arr2, n));

        printf("qsort  : %.6f sec\n\n",
            test_qsort(arr3, n));
    }

    printf("\n===== DESCENDING =====\n");

    for (int s = 0; s < count_sizes; s++)
    {
        int n = sizes[s];

        fill_descending(source, n);

        copy_array(source, arr1, n);
        copy_array(source, arr2, n);
        copy_array(source, arr3, n);

        printf("N = %d\n", n);

        printf("Shell  : %.6f sec\n",
            test_shell(arr1, n));

        printf("QS     : %.6f sec\n",
            test_qs(arr2, n));

        printf("qsort  : %.6f sec\n\n",
            test_qsort(arr3, n));
    }

    printf("\n===== HALF ASC / HALF DESC =====\n");

    for (int s = 0; s < count_sizes; s++)
    {
        int n = sizes[s];

        fill_half_half(source, n);

        copy_array(source, arr1, n);
        copy_array(source, arr2, n);
        copy_array(source, arr3, n);

        printf("N = %d\n", n);

        printf("Shell  : %.6f sec\n",
            test_shell(arr1, n));

        printf("QS     : %.6f sec\n",
            test_qs(arr2, n));

        printf("qsort  : %.6f sec\n\n",
            test_qsort(arr3, n));
    }

    return 0;
}