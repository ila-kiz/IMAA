#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int SIZE = 12;

char t1[SIZE][SIZE]; // поле моих кораблей
char t2[SIZE][SIZE]; // поле кораблей противника

int popPopal = 0;     // сколько раз я попал по врагу
int popPoluchil = 0;  // сколько раз враг попал по мне

struct ship {
    bool isHor;
    int x;
    int y;
    int razm;
};

// мои корабли
ship odn = { true,  4, 7, 0 };
ship dwu = { true,  7, 2, 1 };
ship tri = { true,  1, 8, 2 };

void znak(char t[SIZE][SIZE])
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

// печатает оба поля рядом
void vod()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%c ", t1[i][j]);
        }
        printf("      ");
        for (int j = 0; j < SIZE; j++)
        {
            printf("%c ", t2[i][j]);
        }
        printf("\n");
    }
}

// ставит один корабль на любое поле
void mena(char ch, ship* z, char t[SIZE][SIZE]) {

    for (int k = 0; k < SIZE; k++)//строки
    {
        for (int j = 0; j < SIZE; j++)//столбцы
        {
            if (z->isHor == true) {
                if (k == z->y && j >= z->x && j <= (z->x + z->razm)) {
                    t[k][j] = ch;
                }
            }
            else {
                if (k >= z->y && k <= (z->y + z->razm) && j == z->x) {
                    t[k][j] = ch;
                }
            }
        }
    }
}

// случайно расставляет корабли противника (1-палубный, 2-палубный, 3-палубный)
void postavitVragov()
{
    srand((unsigned)time(NULL));
    int razmery[3] = { 0, 1, 2 }; // как у odn, dwu, tri

    for (int i = 0; i < 3; i++)
    {
        bool stavitOk = false;
        while (!stavitOk)
        {
            int x = 1 + rand() % (SIZE - 2);
            int y = 1 + rand() % (SIZE - 2);
            bool gorizontal = (rand() % 2 == 0);
            int razm = razmery[i];

            // проверяем, что корабль влезает в поле и не пересекается с чужими
            bool svobodno = true;
            for (int c = 0; c <= razm; c++)
            {
                int kx = gorizontal ? x + c : x;
                int ky = gorizontal ? y : y + c;
                if (kx > SIZE - 2 || ky > SIZE - 2) { svobodno = false; break; }
                if (t2[ky][kx] == '0') { svobodno = false; break; }
            }

            if (svobodno)
            {
                ship z = { gorizontal, x, y, razm };
                mena('0', &z, t2);
                stavitOk = true;
            }
        }
    }
}

// выстрел по полю: возвращает true, если попали
bool vistrel(char t[SIZE][SIZE], int x, int y, int* counter)
{
    if (t[y][x] == '0') {
        t[y][x] = '#';
        (*counter)++;
        return true;
    }
    else if (t[y][x] == '.') {
        t[y][x] = '*'; // промах
    }
    return false;
}

int main() {
    char ch = '0';

    znak(t1);
    znak(t2);

    // ставлю мои корабли (те же координаты, что были у тебя)
    mena(ch, &odn, t1);
    mena(ch, &dwu, t1);
    mena(ch, &tri, t1);

    // расставляю корабли противника случайно
    postavitVragov();

    int x, y;

    // всего клеток под кораблями: 1 + 2 + 3 = 6
    while (popPopal < 6 && popPoluchil < 6)
    {
        system("cls");
        printf("  MOI KORABLI          PROTIVNIK\n");
        vod();
        printf("\npopadki po vragu: %d   popadki po mne: %d\n", popPopal, popPoluchil);
        printf("vvesti x y (1-10): ");

        if (scanf_s("%d %d", &x, &y) != 2) break;

        if (x < 1 || x > SIZE - 2 || y < 1 || y > SIZE - 2) {
            printf("takoj kletki net!\n");
            system("pause");
            continue;
        }bool popal = vistrel(t2, x, y, &popPopal);
        if (popal) printf("POPAL!\n");
        else       printf("mimo.\n");

        // ход противника: стреляет случайно, пока не попадёт по чистой клетке
        if (popPopal < 6)
        {
            bool hodVraga = true;
            while (hodVraga)
            {
                int vx = 1 + rand() % (SIZE - 2);
                int vy = 1 + rand() % (SIZE - 2);
                if (t1[vy][vx] == '#' || t1[vy][vx] == '*') continue; // сюда уже стреляли

                bool popalVrag = vistrel(t1, vx, vy, &popPoluchil);
                if (popalVrag) printf("vrag popal v tebja (%d,%d)!\n", vx, vy);
                else           printf("vrag mimo (%d,%d).\n", vx, vy);
                hodVraga = false;
            }
        }
        system("pause");
    }

    system("cls");
    printf("  MOI KORABLI          PROTIVNIK\n");
    vod();
    printf("\npopadki po vragu: %d   popadki po mne: %d\n", popPopal, popPoluchil);

    if (popPopal == 6) printf("POBEDA! vsi korabli vraga potopleny!\n");
    else               printf("Porazenie. tvoi korabli potopleny.\n");

    system("pause");
    return 0;
}