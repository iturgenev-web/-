#include <stdio.h>
#include <Windows.h>
void main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	int i;
	char fam[20];
	struct student {
		char famil[20];
		char name[20], facult[20];
		int Nomzach;
	} 
	stud[3];
	for (i = 0; i < 3; i++)
	{
		printf("Введите фамилию студента\n"); 
		scanf("%20s", stud[i].famil);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите имя студента %s\n", stud[i].famil); 
		scanf("%20s", stud[i].name);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите название факультета студента %s %s\n", stud[i].famil, stud[i].name); 
		scanf("%20s", stud[i].facult);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите номер зачётной книжки студента %s %s\n", stud[i].famil, stud[i].name); 
		scanf("%d", &stud[i].Nomzach);
	}
	printf("Введите фамилию студента о котором хотите узнать информацию?\n");
	scanf("%20s", &fam);
	for (int i = 0; i < 3; i++) {
		if (strcmp(fam, stud[i].famil) == 0) {
			printf("Фамилия: %s\nИмя: %s\nФакультет: %s\nНомер зачётной книжки: %d\n", stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
		}
	}
}