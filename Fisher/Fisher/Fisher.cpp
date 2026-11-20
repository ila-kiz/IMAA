#include <cstdio>   // Для printf и scanf
#include <windows.h>
#include <cstdlib>
// библиотеки рандомайзера
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const int h = 15; // высота
const int w = 15; // ширина
char arry[h][w];

void clear()
{
	system("cls"); // Функция очистки
}

struct Ship{
	int length;
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


int main()
{
	srand((unsigned int)time(NULL));

	line();
	draw(); 
	clear();
	printf("Player table:\n ");
	int row, col;

	while (true) {
		printf("\n Vvedite stroly (1-15): ");

		scanf_s("%d", &row);

		printf("\n Vvedite stolbec (1-15): ");
		scanf_s("%d", &col); //адрес переменой

		if (row >= 2 && row <= h && col >= 2 && col <= w) { // не выходит ли за поля

			if (rand() % 2 == 1) {
				arry[row - 1][col - 1] = 'X'; // Попадение 
				clear();
				draw();
				printf("\nPopal!\n");
			}
			else {
				arry[row - 1][col - 1] = '*'; // мимо
				clear();
				draw();
				printf("\nMimo!\n");
			}
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