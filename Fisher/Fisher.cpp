#include <cstdio>   // Для printf и scanf
#include <windows.h>
#include <cstdlib>
// библиотеки рандомайзера
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const int h = 15; // высота
const int w = 15; // ширина
char arry[h][w]; //поле
char fru[h][w]; // второе поле


void clear()
{
	system("cls"); // Функция очистки
}

struct Ship{
	int length; // длина
	int row;
	int col;
	bool isMorizontal; //горизонт или вертикаль
};

void line()
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			arry[i][j] = '.';

		}
	}
	for (int j = 0; j < w; j++)
	{
		arry[0][j] = ' _';
		arry[14][j] = ' _';
	}
	for (int i = 1; i < 14; i++)
	{
		arry[i][0] = '|';
		arry[i][14] = '|';
	}


	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			printf("%c", arry[i][j]); //вывод одного символа - %c
		}
		printf("\n\n");
	}


}

void line2()
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			fru[i][j] = '.';

		}
	}
	for (int j = 0; j < w; j++)
	{
		fru[0][j] = ' _';
		fru[14][j] = ' _';
	}
	for (int i = 1; i < 14; i++)
	{
		fru[i][0] = '|';
		fru[i][14] = '|';
	}


	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			printf("%c", fru[i][j]); //вывод одного символа - %c
		}
		printf("\n");
	}


}



void draw()
{
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			printf("%c ", arry[i][j]);

		}
		printf("\n");
	}
}

void draw2()
{
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			printf("%c ", fru[i][j]);

		}
		printf("\n");
	}
}


int main()
{
	srand((unsigned int)time(NULL));

	line2();
	draw2();
	clear();
	printf("Boat table:\n ");
	int row, col, length, isMorizontal;


	while (true)
	{
		printf("\n Vvedite stroly (2-14): ");
		scanf_s("%d", &row);

		printf("\n Vvedite stolbec (2-14): ");
		scanf_s("%d", &col);

		printf("\n Vvedite dliny (1-4): ");
		scanf_s("%d", &length);

		printf("\n Orientachiya (1 - |, 0 - ---)");
		scanf_s("%d", &isMorizontal);

		if (row >= 2 && row <= h && col >= 2 && col <= w) 
		{
			arry[14][14] = '#';
		}
		else
		{
			printf("Error!");
		}
	}

	line();
	draw(); 
	clear();
	printf("Player table:\n ");
	

	while (true) 
	{
		printf("\n Vvedite stroly (1-15): ");

		scanf_s("%d", &row);

		printf("\n Vvedite stolbec (1-15): ");
		scanf_s("%d", &col); //адрес переменой

		if (row >= 2 && row <= h && col >= 2 && col <= w) { // не выходит ли за поля

			//if (rand() % 2 == 1) {
			//	arry[row - 1][col - 1] = 'X'; // Попадение 
			//	clear();
			//	draw();
			//	printf("\nPopal!\n");
			//}
			//else {
			//	arry[row - 1][col - 1] = '*'; // мимо
			//	clear();
			//	draw();
			//	printf("\nMimo!\n");
			//}
		}
		else
		{
			printf("Error!");
		}
	}


	clear();
	draw(); 
	printf("\nWell done!\n");



}