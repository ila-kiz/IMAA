#include <cstdio>   // Для printf и scanf
#include <windows.h>
#include <cstdlib>
// библиотеки рандомайзера
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h> // библиотека для русского языка


const int h = 10; // высота
const int w = 10; // ширина
char arry[h][w]; //поле
char fru[h][w]; // второе поле
int choice; // выбор для меню
const int num = 10;

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
			arry[i][j] = '.'; fru[i][j] = '.';

		}
	}
	for (int j = 0; j < w; j++)
	{
		arry[0][j] = '_'; fru[0][j] = '_';
		arry[9][j] = '_'; fru[9][j] = '_';
	}
	for (int i = 1; i < 9; i++)
	{
		arry[i][0] = '|'; fru[i][0] = '|';
		arry[i][9] = '|'; fru[i][9] = '|';
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


void draw()
{

	printf("    "); // Заголовок
	for (int j = 0; j < w; j++) {
		printf("%2d ", j + 1); // %2d выравнивает числа по правому краю в 2 символа
	}
	printf("\n");

	for (int i = 0; i < h; i++) {
		printf("%2c  ", i + 'A'); // Номер строки слева
		for (int j = 0; j < w; j++) {
			printf(" %c ", arry[i][j]); 
		}
		printf("\n");
	}

	printf("\n"); 

	printf("    ");
	for (int j = 0; j < w; j++) {
		printf("%2d ", j + 1);
	}
	printf("\n");

	for (int i = 0; i < h; i++) {
		printf("%2c  ", i + 'A');
		for (int j = 0; j < w; j++) {
			printf(" %c ", fru[i][j]);
		}
		printf("\n");
	}
}

bool menu()
{
	int choice;
	while (true)
	{
		printf("\n Введите цифру (1 - Начать; 0 - выход): "); 
		scanf_s("%d", &choice);

		if (choice == 1) { return true; }

		else if (choice == 0) { return false;}
		else { printf("Ошибка! Вы вели не ту цифру."); Sleep(2000); return false; }
	}
}

void boat()
{
	int count = 0; //сколько кораблей 
	int num = 0;
	int place = 0;

	clear();
	printf("Сколько кораблей вы хотите выставить? (от 1 до 10): ");
	scanf_s("%d", &count);

	while (place < count)
	{
		int row, col, length, isMorizontal;

		clear();
		draw();
		printf("\nТаблица кораблей:\n");

		printf("\n Введите строку (2-9): ");
		scanf_s("%d", &row);

		printf("\n Введите столбик (2-9): ");
		scanf_s("%d", &col);

		printf("\n Введите длину (1-4): ");
		scanf_s("%d", &length);

		printf("\n Ориентация (1 - вертикально, 0 - горизонтально)");
		scanf_s("%d", &isMorizontal);

		int r = row - 1;
		int c = col - 1;
		bool canPlace = true;

		if (length >= 1 && length <= 4 && isMorizontal == 1 && r >= 1 && r + length - 1 <= 8 && c >= 1 && c <= 8)
		{ //диапозон и координаты, ограничения корабля, корабль длиной от 1 до 4, не лезит за 13 строку
			for (int i = 0; i < length; i++)
			{
				arry[r + i][c] = '#';
			}
			break;
		}
		else if (length >= 1 && length <= 4 && isMorizontal == 0 && r >= 1 && r <= 8 && c >= 1 && c + length - 1 <= 8)
		{
			for (int i = 0; i < length; i++)
			{
				arry[r][c + i] = '#';
			}
			break;
		}
		else
		{
			printf("Error!\n");
		}
	}

	}


void Player()
{
	int row, col, length, isMorizontal;
	while (true)
	{
		draw();
		clear();
		printf("\nТаблица игрока:\n");

		printf("\n Введите строку (2-9): ");
		scanf_s("%d", &row);

		printf("\n Введите столбик (2-9): ");
		scanf_s("%d", &col); //адрес переменой

		int r = row - 1;
		int c = col - 1;


		if (isMorizontal == 1 && r >= 1 && r + length - 1 <= 9 && c >= 1 && c <= 9)
		{
			for (int i = 0; i < length; i++)
			{
				fru[r + i][c] = '#';
			}
			break;
		}

		else if (isMorizontal == 0 && r >= 1 && r <= 9 && c >= 1 && c + length - 1 <= 9)
		{
			for (int i = 0; i < length; i++)
			{
				fru[r][c + i] = '#';
			}
			break;
		}
		else
		{
			printf("Корабль выходит за границы поля!\n");
		}
	}


}

void win()
{
	int row, col, length, isMorizontal;
	int shipR, shipC;

	if (shipR == row && shipC == col)
		printf("\nВы выиграли!\n");
	else
		printf("\nВы проиграли!\n");

}


int main()
{
	setlocale(LC_ALL, "Russian"); // для русского языка
	srand((unsigned int)time(NULL));

	if (!menu()) { return 0; } // !menu то же самое, что menu == false

	line();

	int row, col, length, isMorizontal;
	int shipR, shipC;

	boat();
	Player();

	clear();
	draw();
	win();
}