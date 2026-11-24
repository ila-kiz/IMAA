#include <cstdio>   // Для printf и scanf
#include <windows.h>
#include <cstdlib>
// библиотеки рандомайзера
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h> // библиотека для русского языка


const int h = 15; // высота
const int w = 15; // ширина
char arry[h][w]; //поле
char fru[h][w]; // второе поле


void clear()
{
	system("cls"); // Функция очистки
}

struct Ship {
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
		arry[0][j] = '_';
		arry[14][j] = '_';
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
		fru[0][j] = '_';
		fru[14][j] = '_';
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
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			printf("%c ", fru[i][j]);

		}
		printf("\n");
	}

}



int main()
{
	setlocale(LC_ALL, "Russian"); // для русского языка
	srand((unsigned int)time(NULL));
	line();
	line2();
	int row, col, length, isMorizontal;


	while (true)
	{
		clear();
		draw();
		printf("\nТаблица кораблей:\n");

		printf("\n Введите строку (2-14): ");
		scanf_s("%d", &row);

		printf("\n Введите столбик (2-14): ");
		scanf_s("%d", &col);

		printf("\n Введите длину (1-4): ");
		scanf_s("%d", &length);

		printf("\n Ориентация (1 - вертикально, 0 - горизонтально)");
		scanf_s("%d", &isMorizontal);

		if (row >= 2 && row <= h && col >= 2 && col <= w)
		{
			arry[14][14] = '#';
			break;
		}
		else
		{
			printf("Error!");
		}
	}

	printf("Таблица игрока:\n ");


	while (true)
	{
		draw();
		clear();

		printf("\nТаблица игрока:\n");


		printf("\n Введите строку (1-15): ");

		scanf_s("%d", &row);

		printf("\n Введите столбик (1-15): ");
		scanf_s("%d", &col); //адрес переменой

		int r = row - 1;
		int c = col - 1;


		if (isMorizontal == 1 && r >= 1 && r + length - 1 <= 13 && c >= 1 && c <= 13) {
			for (int i = 0; i < length; i++) {
				fru[r + i][c] = '#';
			}
			break;
		}
		else if (isMorizontal == 0 && r >= 1 && r <= 13 && c >= 1 && c + length - 1 <= 13) {
			for (int i = 0; i < length; i++) {
				fru[r][c + i] = '#';
			}
			break;
		}
		else {
			printf("Корабль выходит за границы поля!\n");

		}
	}

	clear();
	draw();
	printf("\nWell done!\n");
}
