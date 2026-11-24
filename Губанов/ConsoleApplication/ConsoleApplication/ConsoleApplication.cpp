#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>

const int SIZE = 20;
const int SHIP_COUNT = 5;
char table[SIZE][SIZE];

struct Ship {
    int length;
    int x;
    int y;
    bool isHorizontal;
    int hits;
    bool isSunk;
};

void matrix() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((i == 0 || i == SIZE - 1) && (j == 0 || j == SIZE - 1)) {
                table[i][j] = '+';
            }
            else if (i == 0 || i == SIZE - 1) {
                table[i][j] = '-';
            }
            else if (j == 0 || j == SIZE - 1) {
                table[i][j] = '|';
            }
            else {
                table[i][j] = ' ';
            }
        }
    }
}

bool can_place(Ship s) {
    for (int i = 0; i < s.length; i++) {
        int cur_x = s.isHorizontal ? s.x : s.x + i;
        int cur_y = s.isHorizontal ? s.y + i : s.y;

        if (cur_x < 1 || cur_x >= SIZE - 1 || cur_y < 1 || cur_y >= SIZE - 1) {
            return false;
        }

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (table[cur_x + dx][cur_y + dy] == '#') {
                    return false;
                }
            }
        }
    }
    return true;
}

void draw_ship(Ship s) {
    for (int i = 0; i < s.length; i++) {
        if (s.isHorizontal) {
            table[s.x][s.y + i] = '#';
        }
        else {
            table[s.x + i][s.y] = '#';
        }
    }
}

int check_hit(Ship ships[], int x, int y) {
    for (int i = 0; i < SHIP_COUNT; i++) {
        for (int j = 0; j < ships[i].length; j++) {
            int cur_x = ships[i].isHorizontal ? ships[i].x : ships[i].x + j;
            int cur_y = ships[i].isHorizontal ? ships[i].y + j : ships[i].y;

            if (cur_x == x && cur_y == y) {
                ships[i].hits++;
                if (ships[i].hits >= ships[i].length && !ships[i].isSunk) {
                    ships[i].isSunk = true;
                    return 2;
                }
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    matrix();

    Ship ships[SHIP_COUNT];
    for (int i = 0; i < SHIP_COUNT; i++) {
        bool placed = false;
        while (!placed) {
            ships[i].length = (rand() % 4) + 1;
            ships[i].isHorizontal = (rand() % 2 == 0);
            ships[i].hits = 0;
            ships[i].isSunk = false;

            if (ships[i].isHorizontal) {
                ships[i].x = (rand() % (SIZE - 2)) + 1;
                ships[i].y = (rand() % (SIZE - 1 - ships[i].length)) + 1;
            }
            else {
                ships[i].x = (rand() % (SIZE - 1 - ships[i].length)) + 1;
                ships[i].y = (rand() % (SIZE - 2)) + 1;
            }

            if (can_place(ships[i])) {
                draw_ship(ships[i]);
                placed = true;
            }
        }
    }

    int x = -1;
    int y = -1;
    int last_status = 0;

    while (true) {
        system("cls");

        char prev_char = ' ';
        if (x != -1 && y != -1) {
            prev_char = table[x][y];
            if (prev_char == '#') {
                prev_char = '*';
                last_status = check_hit(ships, x, y);
            }
            else {
                last_status = 0;
            }
            table[x][y] = '.';
        }

        printf("     ");
        for (int j = 0; j < SIZE - 2; ++j) {
            printf("%c ", 'A' + j);
        }
        printf("\n");

        for (int i = 0; i < SIZE; ++i) {
            if (i > 0 && i < SIZE - 1) {
                printf("%2d ", i);
            }
            else {
                printf("   ");
            }

            for (int j = 0; j < SIZE; ++j) {
                printf("%c ", table[i][j]);
            }
            printf("\n");
        }

        if (x != -1 && y != -1) {
            table[x][y] = prev_char;
        }

        if (last_status == 2) {
            printf("\nShip destroyed!\n");
        }
        else if (last_status == 1) {
            printf("\nHit!\n");
        }

        int new_x = 0;
        char col_char = ' ';
        printf("\nx: ");
        scanf_s("%d", &new_x);
        printf("y: ");
        scanf_s(" %c", &col_char, 1);

        if (col_char >= 'a' && col_char <= 'z') {
            col_char = col_char - 'a' + 'A';
        }
        int new_y = col_char - 'A' + 1;

        if (new_x > 0 && new_x < SIZE - 1 && new_y > 0 && new_y < SIZE - 1) {
            x = new_x;
            y = new_y;
        }
    }

    return 0;
}
