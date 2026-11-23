
#include <iostream>

const int SIZE1 = 22;

char array[SIZE1][SIZE1];

void inittable()
{
	for (int i = 0; i < SIZE1; i++)
	{
		for (int j = 0; j < SIZE1; j++)
		{
			if (i == 0 || j == 0 || i == (SIZE1 - 1) || j == (SIZE1 - 1))
			{
				array[i][j] = '#';
			}
			else
			{
				array[i][j] = '~';
			}
		}
	}
}
void printtable()
{
	for (int i = 0; i < SIZE1; i++)
	{
		for (int j = 0; j < SIZE1; j++)
		{
			printf("%c ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void shot()
{
	int x;
	int y;

	printf("введите каординаты выстрела: \n");
	scanf_s("%d", &x);
	scanf_s("%d", &y);

	array[x][y] = '*';
}

int main()
{
	inittable();
	printtable();
	
	while(true)
	{
		shot();
		printtable();
	}
}

