



#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

/* Размер массива: рамка + 10 игровых клеток + рамка */
const int SIZE1 = 12;

char t[SIZE1][SIZE1];   /* моё поле */
char e[SIZE1][SIZE1];   /* корабли противника */
char m[SIZE1][SIZE1];   /* мои выстрелы по противнику */

int myShips = 0;      /* клеток моих кораблей */
int enemyShips = 0;   /* клеток кораблей противника */
int myHits = 0;       /* мои попадания */
int enemyHits = 0;    /* попаданий противника */
int gameExit = 0;     /* 1 — игрок попросил выйти из игры */

/* Кириллические буквы столбцов (10 штук, Й пропускаем) */
const char stolby[10] = { 'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ж', 'З', 'И', 'К' };

/* Стандартный флот: максимум кораблей каждого размера (индекс = размер) */
const int limitFlota[5] = { 0, 4, 3, 2, 1 };


/* Инициализация полей */
void simvoly(void)
{
    int a, b;
    for (a = 0; a < SIZE1; a++)
        for (b = 0; b < SIZE1; b++)
        {
            if (b == 0 || b == SIZE1 - 1) { t[a][b] = '|'; e[a][b] = '|'; m[a][b] = '|'; }
            else if (a == 0 || a == SIZE1 - 1) { t[a][b] = '-'; e[a][b] = '-'; m[a][b] = '-'; }
            else { t[a][b] = '.'; e[a][b] = '.'; m[a][b] = '.'; }
        }
}

/* Шапка с кириллическими буквами столбцов */
void shapka(void)
{
    int b;
    printf("     ");
    for (b = 1; b <= SIZE1 - 2; b++) printf("%c ", stolby[b - 1]);
    printf("            ");
    for (b = 1; b <= SIZE1 - 2; b++) printf("%c ", stolby[b - 1]);
    printf("\n");
}

/* Вывод обоих полей */
void vyvod(int boy)
{
    int i, b;
    system("cls");
    printf("\n   ВАШЕ ПОЛЕ                        ПОЛЕ ПРОТИВНИКА\n");
    shapka();
    for (i = 0; i < SIZE1; i++)
    {
        if (i >= 1 && i <= SIZE1 - 2) printf("%2d ", i); else printf("   ");
        for (b = 0; b < SIZE1; b++) printf("%c ", t[i][b]);
        printf("    ");
        if (i >= 1 && i <= SIZE1 - 2) printf("%2d ", i); else printf("   ");
        for (b = 0; b < SIZE1; b++)
        {
            if (boy && e[i][b] == 'O' && m[i][b] == '.')
                printf(". ");                     /* корабль противника ещё не найден */
            else if (boy)
                printf("%c ", m[i][b]);           /* видно только мои выстрелы */
            else
                printf("%c ", e[i][b]);           /* при расстановке корабли видны */
        }
        printf("\n");
    }
}

/* Перевод кириллической буквы столбца в индекс (А=1 ... К=10) */
int perevodStolbca(char c)
{
    int i;
    unsigned char u = (unsigned char)c;

    /* Приводим введённый байт к CP1251 (кодировка исходника) */
    if (u >= 0xE0 && u <= 0xFF) u -= 32;         /* CP1251: строчная -> заглавная */
    else if (u >= 0xA0 && u <= 0xAF) u += 0x20;  /* CP866: строчная -> CP1251 заглавная */
    else if (u >= 0x80 && u <= 0x9F) u += 0x40;  /* CP866: заглавная -> CP1251 */

    for (i = 0; i < 10; i++)
        if (u == (unsigned char)stolby[i]) return i + 1;
    return -1;
}

/* Можно ли поставить корабль: клетки внутри поля и нигде рядом (даже по диагонали) нет 'O' */
int mozhnoLi(char pole[SIZE1][SIZE1], int a, int b, int razmer, char orient)
{
    int k, ra, rb, da, db;

    for (k = 0; k < razmer; k++)
    {
        ra = (orient == 'H') ? a : a + k;
        rb = (orient == 'H') ? b + k : b;

        if (ra < 1 || ra > SIZE1 - 2 || rb < 1 || rb > SIZE1 - 2) return 0;

        /* сама клетка и все 8 соседей */
        for (da = -1; da <= 1; da++)
            for (db = -1; db <= 1; db++)
                if (pole[ra + da][rb + db] == 'O') return 0;
    }
    return 1;
}

/* Стереть весь корабль, проходящий через клетку (a, b); вернуть его размер, 0 если там пусто */
int udalitKorabl(char pole[SIZE1][SIZE1], int a, int b, int* vsego)
{
    int stA[4], stB[4];
    int top = 0, razmer = 0;
    int da, db, ra, rb;

    if (pole[a][b] != 'O') return 0;

    stA[top] = a; stB[top] = b; top++;

    while (top > 0)
    {
        top--;
        ra = stA[top]; rb = stB[top];
        if (pole[ra][rb] != 'O') continue;

        pole[ra][rb] = '.';
        (*vsego)--;
        razmer++;

        /* ищем соседние клетки того же корабля (4-связность) */
        for (da = -1; da <= 1; da++)
            for (db = -1; db <= 1; db++)
            {
                if (da != 0 && db != 0) continue;        /* по диагонали другой корабль */
                if (pole[ra + da][rb + db] == 'O' && top < 4)
                {
                    stA[top] = ra + da; stB[top] = rb + db; top++;
                }
            }
    }
    return razmer;
}

void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/* Спрашиваем подтверждение выхода; при согласии ставим флаг */
int sprositVykhod(void)
{
    char otvet;
    printf("Точно выйти из игры? (Y - да / N - нет): ");
    scanf_s(" %c", &otvet, 1);
    while (getchar() != '\n');   /* съедаем остаток строки */
    if (otvet == 'Y' || otvet == 'y') { gameExit = 1; return 1; }
    return 0;
}

/* Расстановка кораблей: строка (1-10), столбец (А-К), размер (1-4), ориентация (H/V)
   Ввод "-" — отменить последний поставленный корабль */
void razmestit(char pole[SIZE1][SIZE1], const char* kto, int* vsego)
{
    int a, b, razmer, k;
    int kolVo[5] = { 0, 0, 0, 0, 0 };   /* сколько кораблей каждого размера уже стоит */
    int i, udal, kolVseh = 0;
    char bChar, orient;
    char stroka[100];

    /* история поставленных кораблей: до 10 (весь флот) */
    int hA[10], hB[10], hR[10];
    char hO[10];
    set_color(15);
    printf("\n--- УСЛОВНЫЕ ОБОЗНАЧЕНИЯ ---\n");
    set_color(10);
    printf("O  — корабль\n");
    printf("#  — промах\n");
    printf("X  — попадание\n");
    printf("%%  — подбитая клетка (уже поражена)\n");
    printf(".  — неизвестная/пустая клетка\n");
    printf("S — пропуск хода, Q — выход из игры.");
    set_color(11);
    printf("Столбцы — А..К (без Й), строки — 1..10\n");
    printf("\n%s: введите строку (1-10), столбец (А-К), размер (1-4) и ориентацию.\n", kto);
    printf("Пример: 5 Б 3 H  (корабль из 3 клеток горизонтально от Б5)\n");
    printf("H - горизонтально, V - вертикально (латинские буквы).\n");
    printf("-            — отменить последний поставленный корабль\n");
    printf("Удалить корабль по клетке: строка столбец 0, напр. 3 Б 0\n");
    printf("Q            — выйти из игры\n");
    printf("Закончить расстановку: 0 0 0 X\n");
    printf("Флот: 4-палубных - 1, 3-палубных - 2, 2-палубных - 3, 1-палубных - 4\n");
    printf("----------------------------\n\n");
    set_color(15);
    while (1)
    {
        printf("Ввод: ");
        if (fgets(stroka, sizeof(stroka), stdin) == NULL) continue;

        /* пропускаем ведущие пробелы и табуляции */
        i = 0;
        while (stroka[i] == ' ' || stroka[i] == '\t') i++;

        /* команда "Q": выход из игры */
        if (stroka[i] == 'Q' || stroka[i] == 'q')
        {
            if (sprositVykhod()) return;
            vyvod(0);
            continue;
        }

        /* команда "-": отмена последнего поставленного корабля */
        if (stroka[i] == '-' && (stroka[i + 1] == '\n' || stroka[i + 1] == '\0'))
        {
            if (kolVseh == 0)
            {
                printf("Отменять нечего — корабли ещё не ставились.\n");
                continue;
            }
            kolVseh--;
            razmer = hR[kolVseh];
            for (k = 0; k < razmer; k++)
            {
                if (hO[kolVseh] == 'H') pole[hA[kolVseh]][hB[kolVseh] + k] = '.';
                else                    pole[hA[kolVseh] + k][hB[kolVseh]] = '.';
            }
            *vsego -= razmer;
            kolVo[razmer]--;
            printf("Удалён последний поставленный корабль (%d клеток).\n", razmer);
            vyvod(0);
            continue;
        }

        /* обычный ввод */
        i = sscanf_s(stroka, "%d %c %d %c", &a, &bChar, 1, &razmer, &orient, 1);

        if (i != 4 && i != 3)
        {
            printf("Ошибка: неверный ввод\n");
            continue;
        }

        /* завершение: 0 0 0 X (или 0 0 0) */
        if (a == 0 && bChar == '0' && razmer == 0)
        {
            if (*vsego == 0) { printf("Нужен хотя бы один корабль!\n"); continue; }
            printf("Расставлено: 4-палубных %d/1, 3-палубных %d/2, 2-палубных %d/3, 1-палубных %d/4\n",
                kolVo[4], kolVo[3], kolVo[2], kolVo[1]);
            break;
        }

        b = perevodStolbca(bChar);
        if (b == -1) { printf("Ошибка: столбец должен быть от А до К.\n"); continue; }

        if (a < 1 || a > SIZE1 - 2 || b < 1 || b > SIZE1 - 2)
        {
            printf("Ошибка: строка 1-10, столбец А-К.\n");
            continue;
        }

        /* удаление корабля по клетке: размер 0 */
        if (razmer == 0)
        {
            udal = udalitKorabl(pole, a, b, vsego);
            if (udal == 0) printf("Ошибка: в этой клетке нет корабля.\n");
            else { kolVo[udal]--; printf("Корабль из %d клеток убран.\n", udal); vyvod(0); }
            continue;
        }

        if (razmer < 1 || razmer > 4) { printf("Ошибка: размер от 1 до 4.\n"); continue; }

        /* нормализуем ориентацию к заглавной латинской */
        if (orient >= 'a' && orient <= 'z') orient = (char)(orient - 32);
        if (orient != 'H' && orient != 'V')
        {
            printf("Ошибка: ориентация H (горизонтально) или V (вертикально).\n");
            continue;
        }

        if (kolVo[razmer] >= limitFlota[razmer])
        {
            printf("Ошибка: кораблей из %d клеток уже максимум (%d).\n", razmer, limitFlota[razmer]);
            continue;
        }

        if (!mozhnoLi(pole, a, b, razmer, orient))
        {
            printf("Ошибка: корабль не помещается или касается другого (даже по диагонали).\n");
            continue;
        }

        /* ставим */
        for (i = 0; i < razmer; i++)
        {
            if (orient == 'H') pole[a][b + i] = 'O';
            else               pole[a + i][b] = 'O';
        }
        (*vsego) += razmer;
        kolVo[razmer]++;

        /* запоминаем в историю для отмены */
        hA[kolVseh] = a;
        hB[kolVseh] = b;
        hR[kolVseh] = razmer;
        hO[kolVseh] = orient;
        kolVseh++;

        vyvod(0);
    }
}

/* Мой выстрел.
   Возвращает: 1 — выстрел сделан, 0 — пропуск хода, -1 — выход из игры */
int vashVystrel(void)
{
    int a, b, j;
    char bChar;
    char stroka[100];

    while (1)
    {
        printf("Ваш выстрел (строка и столбец, напр. 3 Б).\n");
        printf("S — пропустить ход, Q — выйти из игры: ");

        if (fgets(stroka, sizeof(stroka), stdin) == NULL) continue;

        j = 0;
        while (stroka[j] == ' ' || stroka[j] == '\t') j++;

        /* выход из игры */
        if (stroka[j] == 'Q' || stroka[j] == 'q')
        {
            if (sprositVykhod()) return -1;
            continue;
        }

        /* пропуск хода */
        if (stroka[j] == 'S' || stroka[j] == 's')
        {
            printf("Вы пропустили свой выстрел.\n");
            return 0;
        }

        if (sscanf_s(stroka, "%d %c", &a, &bChar, 1) != 2)
        {
            printf("Ошибка: неверный ввод\n");
            continue;
        }

        b = perevodStolbca(bChar);
        if (b == -1) { printf("Ошибка: столбец должен быть от А до К.\n"); continue; }

        if (a >= 1 && a <= SIZE1 - 2 && b >= 1 && b <= SIZE1 - 2)
        {
            if (m[a][b] != '.') { printf("Здесь уже стреляли! Введите другую клетку.\n"); continue; }

            if (e[a][b] == 'O')
            {
                m[a][b] = 'X';      /* попадание */
                myHits++;
                printf("ПОПАДАНИЕ!\n");
            }
            else
            {
                m[a][b] = '#';      /* промах */
                printf("Мимо.\n");
            }
            return 1;
        }
        printf("Ошибка: строка 1-10, столбец А-К.\n");
    }
}

/* Выстрел противника, рандомная клетка, без повторов */
void hodProtivnika(void)
{
    int a, b;
    do
    {
        a = rand() % (SIZE1 - 2) + 1;   /* 1–10 */
        b = rand() % (SIZE1 - 2) + 1;   /* 1–10 */
    } while (t[a][b] == '#' || t[a][b] == '%' || t[a][b] == 'X');

    if (t[a][b] == 'O')
    {
        t[a][b] = '%';                 /* подбитая клетка */
        enemyHits++;
        printf("Противник: %d %c — ПОПАДАНИЕ!\n", a, stolby[b - 1]);
    }
    else
    {
        t[a][b] = '#';
        printf("Противник: %d %c — мимо.\n", a, stolby[b - 1]);
    }
}

int main(void)
{
    system("chcp 1251 > nul");      /* кодировка консоли: ввод и вывод в 1251 */
    setlocale(LC_ALL, "Russian");   /* кириллица в консоли */

    simvoly();
    vyvod(0);

    razmestit(t, "Ваши корабли", &myShips);
    if (gameExit) { printf("\nИгра прервана по вашему требованию.\n"); return 0; }

    razmestit(e, "Корабли противника", &enemyShips);
    if (gameExit) { printf("\nИгра прервана по вашему требованию.\n"); return 0; }

    printf("\nБой! Вводите координаты выстрела: строка (1-10) и столбец (А-К).\n");
    printf("Команды: S — пропуск хода, Q — выход из игры.\n");
    vyvod(1);

    while (myHits < enemyShips && enemyHits < myShips)
    {
        int res = vashVystrel();

        if (res == -1) break;   /* выход из игры */

        if (res == 0)
            printf("Противник стреляет, пока вы пропускаете ход!\n");
        hodProtivnika();

        vyvod(1);
        printf("Счёт: вы попали %d из %d, противник %d из %d\n",
            myHits, enemyShips, enemyHits, myShips);
    }

    if (gameExit)
        printf("\nИгра прервана по вашему требованию.\n");
    else if (myHits >= enemyShips)
        printf("\nПобеда! Вы потопили все корабли противника!\n");
    else
        printf("\nПоражение. Противник потопил все ваши корабли.\n");

    return 0;
}
