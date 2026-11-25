#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <windows.h>


const int B_SIZE = 12;


char t[B_SIZE ][B_SIZE];
char wrag[B_SIZE][B_SIZE];
char ch = '0';//корабль
char ch2 = '#';//промох
char ch3 = '*';//поподание


struct ship {
	bool isHor;
	int x;
	int y;
	int razm;
};


ship odn = { true, 4, 7, 1 };
ship dwu = { true, 7, 2, 2 };
ship tri = { true, 1, 8, 3 };
ship chetir = { true, 9, 3, 4 };


void table()
{
	for (int k = 0; k < B_SIZE; k++)
	{
		for (int j = 0; j < B_SIZE; j++)
		{
			if (k == 0 || k == B_SIZE - 1) {
				t[k][j] = '-';
			}
			else if (j == 0 || j == B_SIZE - 1) {
				t[k][j] = '|';
			}
			else {
				t[k][j] = '.';
			}
		}
	}
}

void table2()
{
	for (int k = 0; k < B_SIZE; k++)
	{
		for (int j = 0; j < B_SIZE; j++)
		{
			if (k == 0 || k == B_SIZE - 1) {
				wrag[k][j] = '-';
			}
			else if (j == 0 || j == B_SIZE - 1) {
				wrag[k][j] = '|';
			}
			else {
				wrag[k][j] = '.';
			}
		}
	}
}

void vod(){
	system("cls");
	printf("     A Б В Г Д Е Ж З И К");
	printf("			");
	printf("     A Б В Г Д Е Ж З И К");
	printf("\n");
	for (int i = 0 ; i < B_SIZE; i++)
	{
		if (i != 0 && i != 11) {
			if (i == 10) {
				printf("%d ", i);
			}
			else {
				printf("%d  ", i);
			}
		}
		else {
			printf("   ");
		}
		for (int j = 0; j < B_SIZE; j++)
		{
			printf("%c ", t[i][j]);
		}
		printf("			");
		if (i != 0 && i != 11) {
			if (i == 10) {
				printf("%d ", i);
			}
			else {
				printf("%d  ", i);
			}
		}
		else {
			printf("   ");
		}
		for (int k = 0; k < B_SIZE; k++)
		{
			printf("%c ", wrag[i][k]);
		}
		printf("\n");
	}
}


void mena(ship *z, int b, int c, bool ish) {
	z->x = b;
	z->y = c;
	for (int k = 0; k < B_SIZE; k++)//строки
	{
		for (int j = 0; j < B_SIZE; j++)//столбцы
		{
			if (k == 0 || k == B_SIZE - 1) {
				t[k][j] = '-';
			}
			else if (j == 0 || j == B_SIZE - 1) {
				t[k][j] = '|';
			}
			else if (ish == true) {
				if (k == z->y && j >= z->x && j <= (z->x + (z->razm - 1))) {
					t[k][j] = ch;
					vod();
				}
			}
			else if (ish == false) {
				if (k >= z->y && k <= (z->y + (z->razm - 1)) && j == z->x) {
					t[k][j] = ch;
					vod();
				}
			}
			else
			{
				t[k][j] = '.';
				vod();
			}
		}
	}
}


void popodanie(){
	int v;
	char q;
	int m;
	printf("1 - по врагу\n");
	printf("2 - по мне\n");
	printf("> ");
	int h;
	scanf_s("%d", &h);
	printf("куда выстрелить\n");
	printf("> ");
	scanf_s("%d", &v);
	printf("> ");
	scanf_s(" %c", &q, 1);
	switch (q) {
	case 'А': case 'а': m = 1; break;
	case 'Б': case 'б': m = 2; break;
	case 'В': case 'в': m = 3; break;
	case 'Г': case 'г': m = 4; break;
	case 'Д': case 'д': m = 5; break;
	case 'Е': case 'е': m = 6; break;
	case 'Ж': case 'ж': m = 7; break;
	case 'З': case 'з': m = 8; break;
	case 'И': case 'и': m = 9; break;
	case 'К': case 'к': m = 10; break;
	default:
		printf("Неверная буква, выбран столбец А\n");
		m = 1;
		break;
	}
	if (h == 1) {
		int g;
		printf("1 - попал\n");
		printf("2 - не попал\n");
		printf("> ");
		scanf_s("%d", &g);
		if (g == 1) {
			wrag[v][m] = ch3;
		}
		else if (g == 2){
			wrag[v][m] = ch2;
		}
		else {
			printf("ERROR\n");
		}
	}
	else if (h == 2){
		if (t[v][m] == ch) {
			t[v][m] = ch3;
		}
		else if (t[v][m] == '.') {
			t[v][m] = ch2;
		}
		else {
			printf("ERROR\n");
		}
	}


	
}


void Ship_place() {
	printf("какой поставить корабль\n");
	printf("> ");
	int a;
	scanf_s("%d", &a);
	printf("введите координаты\n");
	printf("> ");
	int b;
	int c;
	scanf_s("%d", &b);
	printf("> ");
	scanf_s("%d", &c);
	printf("горизонтально?\n");
	printf("1 - да ; 2 - нет\n");
	printf("> ");
	int h;
	bool ish;
	scanf_s("%d", &h);
	if (h == 1) {
		ish = true;
	}
	else {
		ish = false;
	}
	if (a == 1) {
		mena(&odn, b, c, ish);
	}
	else if (a == 2) {
		mena(&dwu, b, c, ish);
	}
	else if (a == 3) {
		mena(&tri, b, c, ish);
	}
	else if (a == 4) {
		mena(&chetir, b, c, ish);
	}
}



int main() {
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	table();
	table2();
	vod();

	while (true) {

		char y;

		printf("1 - поставить корабль\n");
		printf("2 - выстрел\n");
		printf("3 - выход\n");
		printf("> ");
		scanf_s(" %c", &y, 1);
		if (y == '1') {
			Ship_place();
			vod();
		}
		else if (y == '2') {
			popodanie();
			vod();
		}
		else if (y == '3') {
			break;
		}
		else {
			printf("ERROR\n");
		}
	}
}