#include <iostream>
#include <stdlib.h>
#include <stdio.h>

const int SIZE = 12;



char t[SIZE][SIZE];
char wistrel[SIZE][SIZE];
char ch = '0';
char ch2 = '#';
char ch3 = '!';

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
	for (int k = 0; k < SIZE; k++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (k == 0 || k == SIZE - 1) {
				t[k][j] = '-';
			}
			else if (j == 0 || j == SIZE - 1) {
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
	for (int k = 0; k < SIZE; k++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (k == 0 || k == SIZE - 1) {
				wistrel[k][j] = '-';
			}
			else if (j == 0 || j == SIZE - 1) {
				wistrel[k][j] = '|';
			}
			else {
				wistrel[k][j] = '.';
			}
		}
	}
}



void vod(){
	system("cls");
	for (int i = 0 ; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%c ", t[i][j]);
		}
		printf("\n");
	}
}

void vod2() {
	system("cls");
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%c ", wistrel[i][j]);
		}
		printf("\n");
	}
}


void mena(ship *z, int b, int c, bool ish) {
	z->x = b;
	z->y = c;
	for (int k = 0; k < SIZE; k++)//строки
	{
		for (int j = 0; j < SIZE; j++)//столбцы
		{
			if (k == 0 || k == SIZE - 1) {
				t[k][j] = '-';
			}
			else if (j == 0 || j == SIZE - 1) {
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


void popodanie(int v, int m){
	if (t[v][m] == ch) {
		wistrel[v][m] = ch3;
	}
	else {
		wistrel[v][m] = ch2;
	}
}




int main() {
	table();
	vod();
	printf("how ship place\n");
	int a;
	scanf_s("%d", &a);
	printf("print coordinate\n");
	int b;
	int c;
	scanf_s("%d", &b);
	scanf_s("%d", &c);
	printf("Is horisontal\n");
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

	printf("Where to shoot\n");
	int v;
	int m;
	scanf_s("%d", &v);
	scanf_s("%d", &m);
}