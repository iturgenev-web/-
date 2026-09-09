#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n;
	int* a;
	printf("¬ведите размер массива:");
	scanf_s("%d", &n);
	a = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		printf("¬ведите элемент массива:");
		scanf_s("%d", &a[i]);
	}

	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	free(a);
}