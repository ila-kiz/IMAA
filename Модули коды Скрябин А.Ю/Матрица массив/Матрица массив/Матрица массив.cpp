/*#include <iostream>

const int SIZE = 10
char t[SIZE][SIZE];


void simvoly()
{
    for (int a = 0; a < SIZE; a++)//строка
    {
        for (int b = 0; b < SIZE; b++)// столбец
        {
            if (b == 0 || b == 9)
            {
                t[a][b] = '|';
            }
            else if (a == 0 || a == 9)
            {
                t[a][b] = '-';
            }
            else
            {
                t[a][b] = '.';
            }
        }
    }

}

void vyvod()
{
    for (int i = 0; i < 10; i++)
    {
        for (int b = 0; b < 10; b++)
        {
            printf("%c ", t[i][b]);
        }
        printf("\n");
    }
}

void izm()
{
    int a, b;
    char c;

    printf("Vvedite stroku, stolbec i simvol (naprimer: 3 5 X): ");
 if (scanf_s("%d %d %c", &a, &b, &c, 1) != 3) {
           printf("Error: neverniy vvod\n");
           return;
  }
 if (a > 0 && a < 9 && b > 0 && b < 9)
    {
        t[a][b] = c;
    }
    else{
        printf("Error: koordinaty vnutri ramki (1-8)\n");
    }
}

int main()
{
    simvoly();
    vyvod();

    izm();
    vyvod();

    return 0;
}*/







#include <iostream>
#include <stdlib.h>
#include <stdio.h>

const int SIZE = 10;
char t[SIZE][SIZE];  // ваше поле (на нём корабли)
char e[SIZE][SIZE];  // поле куда стрелял противник

int ships = 0;   // сколько клеток занято кораблями
int hits = 0;    // сколько попаданий у противника

void simvoly()
{
    for (int a = 0; a < SIZE; a++)// строка
    {
        for (int b = 0; b < SIZE; b++)// столбец
        {
            if (b == 0 || b == SIZE - 1)
            {
                t[a][b] = '|';
                e[a][b] = '|';
            }
            else if (a == 0 || a == SIZE - 1)
            {
                t[a][b] = '-';
                e[a][b] = '-';
            }
            else
            {
                t[a][b] = '.';
                e[a][b] = '.';
            }
        }
    }
}

// выводим поля
void vyvod()
{
    printf("Vashe pole              Vystrely protivnika\n");
    for (int i = 0; i < SIZE; i++)
    {
        for (int b = 0; b < SIZE; b++)
            printf("%c ", t[i][b]);
        printf("      ");
        for (int b = 0; b < SIZE; b++)
            printf("%c ", e[i][b]);
        printf("\n");
    }
}

// расстановка кораблей на первом поле
void izm()
{
    int a, b;
    char c;
    printf("Stavte korabli: stroka stolbec simvol (naprimer: 3 5 X).\n");
    printf("X - postavit korabl, . - ubrat. 0 0 X - zakonchit.\n");

    while (1)
    {
        printf("Vvod: ");
        if (scanf_s("%d %d %c", &a, &b, &c, 1) != 3)
        {
            printf("Error: neverniy vvod\n");
            while (getchar() != '\n'); // очищает ввод
            continue;
        }
        if (a == 0 && b == 0)
        {
            if (ships == 0)
            {
                printf("Nuzhen khotya by odin korabl!\n");
                continue;
            }
            break;
        }
        if (a > 0 && a < SIZE - 1 && b > 0 && b < SIZE - 1 && (c == 'X' || c == '.'))
        {
            if (c == 'X' && t[a][b] == '.') ships++;
            if (c == '.' && t[a][b] == 'X') ships--;
            t[a][b] = c;
            vyvod();
        }
        else
        {
            printf("Error: koordinaty vnutri ramki (1-8), simvol X ili .\n");
        }
    }
}

// один выстрел противника
void hodProtivnika()
{
    int a, b;
    do
    {
        a = rand() % (SIZE - 2) + 1;
        b = rand() % (SIZE - 2) + 1;
    } while (e[a][b] != '.'); // дважды в одну клетку не стреляет

    if (t[a][b] == 'X')
    {
        e[a][b] = 'X';
        hits++;
        printf("Protivnik strelyal v %d %d - POPADANIE!\n", a, b);
    }
    else
    {
        e[a][b] = 'O';
        printf("Protivnik strelyal v %d %d - mimo.\n", a, b);
    }
}

int main()
{
    simvoly();
    vyvod();
    izm();

    printf("\nRasstanovka okonchena. Nachinaem boy!\n");
    printf("Nazhmite Enter, chtoby protivnik sdelal vystrel.\n");

    while (hits < ships)
    {
        getchar(); // ждём Enter
        hodProtivnika();
        vyvod();
        printf("Popadaniy: %d iz %d\n", hits, ships);
    }

    printf("\n Vse korabli potopleny. Protivnik pobedil! \n");
    return 0;
}