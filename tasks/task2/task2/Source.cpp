#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void main() {
	srand(time(NULL));
	int n = 10, i = 0;
	int a[10];

	while (i < n) {
		a[i] = rand() % 100;
		printf("%d ", a[i]);
		i++;
	}
}