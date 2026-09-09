#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	int a[10][10], sum_column = 0, sum_string = 0, answer;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			a[i][j] = rand()%10;
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%5d ", a[i][j]);
		}
		printf("\n");
	}
	printf("Какую сумму вы хотите найти? (1 - суммы строк, 2 - суммы столбцов): ");
	scanf_s("%d", &answer);
	if (answer == 1) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				sum_string += a[i][j];
			}
			printf("Сумма строки %d: %d\n", i, sum_string);
			sum_string = 0;
		}
	}
	else {
		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < 10; i++) {
				sum_column += a[i][j];
			}
			printf("Сумма столбца %d: %d\n", j, sum_column);
			sum_column = 0;
		}
	}
}