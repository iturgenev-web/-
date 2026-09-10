#include <stdio.h>
#include <stdlib.h>   // для malloc, free
#include <string.h>   // для strlen, strncmp
#include <Windows.h>

struct student {
	char famil[20];
	char name[20], facult[20];
	int Nomzach;
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setvbuf(stdin, NULL, _IONBF, 0);// отключение буферизации 
	setvbuf(stdout, NULL, _IONBF, 0); 

	int n, i;
	char fam[20];

	printf("Введите количество студентов\n");
	scanf("%d", &n);

	struct student* stud = (struct student*)malloc(n * sizeof(struct student));
	if (stud == NULL) {
		printf("Ошибка выделения памяти!\n");
		return 1;
	}

	for (i = 0; i < n; i++) {
		printf("Введите фамилию студента\n");
		scanf("%20s", stud[i].famil);
	}
	for (i = 0; i < n; i++) {
		printf("Введите имя студента %s\n", stud[i].famil);
		scanf("%20s", stud[i].name);
	}
	for (i = 0; i < n; i++) {
		printf("Введите название факультета студента %s %s\n", stud[i].famil, stud[i].name);
		scanf("%20s", stud[i].facult);
	}
	for (i = 0; i < n; i++) {
		printf("Введите номер зачётной книжки студента %s %s\n", stud[i].famil, stud[i].name);
		scanf("%d", &stud[i].Nomzach);
	}

	printf("Введите фамилию студента, о котором хотите узнать информацию\n");
	scanf("%20s", fam);          

	int found = 0;               
	size_t len = strlen(fam);    

	for (i = 0; i < n; i++) {

		if (strncmp(fam, stud[i].famil, len) == 0) {
			found = 1;
			printf("Фамилия: %s\nИмя: %s\nФакультет: %s\nНомер зачётной книжки: %d\n\n",
				stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
		}
	}

	if (!found) {
		printf("Студент %s не найден\n", fam);
	}

	free(stud); 
	return 0;
}