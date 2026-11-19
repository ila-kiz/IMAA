#include <iostream>
#include <stdlib.h>
#include <stdio.h>

const int SIZE = 12;



char t[SIZE][SIZE];



struct ship {
	bool isHor;
	int x;
	int y;
	int razm;
};


ship odn = { true, 4, 7, 0 };


ship dwu = { true, 7, 2, 1 };


ship tri = { true, 1, 8, 2 };



void znak()
{
	for (int k = 0; k < SIZE; k++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (k == 0 || k == SIZE - 1) {
				t[k][j] = '--';
			}
			else if (j == 0 || j == SIZE - 1) {
				t[k][j] = '|' ;
			}
			else {
				t[k][j] = '.';
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
void mena(char ch, ship *z) {

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
			else if (z->isHor == true) {
				if (k == z->y && j >= z->x && j <= (z->x + z->razm)) {
					t[k][j] = ch;
					vod();
				}
			}
			else if (z->isHor == false) {
				if (k >= z->y && k <= (z->y + z->razm) && j == z->x) {
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







int main() {
	znak();
	vod();
	char ch = '0';
	char ch2 = '#';
	printf("how ship place\n");
	int a = scanf_s("%d", &a);



	if (a == 1 && a<2) 
	{
		mena(ch, &odn);
	}
	else if (a == 2 && a<3)
	{
		mena(ch, &dwu);
	}
	else if (a == 3 && a < 4)
	{
		mena(ch, &tri);
	}
}