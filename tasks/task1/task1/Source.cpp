#include <stdio.h>

void main() {
    int a[10] = { 5,12,8,3,4,5,6,7,8,9 };
    int max = a[0];
    int min = a[0];
    int i = 1;

    while (i < 10) {
        if (a[i] > max)
            max = a[i];

        if (a[i] < min)
            min = a[i];

        i++;
    }

    printf("%d", max - min);
}