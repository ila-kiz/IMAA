
#include <iostream>

const int SIZE1 = 5;

char array[SIZE1][SIZE1];

char array1[SIZE1];

//	0 1 2 3 4 


int main()
{
	printf("c%", array[][]);



	for (int i = 0; i < SIZE1; i++)
	{
		printf("c%", array1[i]);
	}

}

































void printtable()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (i == 0 || j == 0)
			{
				array[i][j] = '|';
			}
			else
				array[i][j] = '.';

			printf("c%", array[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	printtable();
    std::cout << "Hello World!\n";
}

