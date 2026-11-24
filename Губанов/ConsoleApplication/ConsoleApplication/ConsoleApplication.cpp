#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>

const int SIZE = 20;
const int SHIP_COUNT = 5;
char table[SIZE][SIZE];
char enemy_table[SIZE][SIZE];

struct Ship {
    int length;
    int x;
    int y;
    bool isHorizontal;
    int hits;
    bool isSunk;
};

void matrix(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((i == 0 || i == SIZE - 1) && (j == 0 || j == SIZE - 1)) {
                board[i][j] = '+';
            }
            else if (i == 0 || i == SIZE - 1) {
                board[i][j] = '-';
            }
            else if (j == 0 || j == SIZE - 1) {
                board[i][j] = '|';
            }
            else {
                board[i][j] = ' ';
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

void print_board(char board[SIZE][SIZE], const char* title) {
    printf("%s\n", title);
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
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void mark_sunk_enemy(int x, int y) {
    enemy_table[x][y] = '*';

    int min_x = x, max_x = x;
    int min_y = y, max_y = y;

    while (min_x > 1 && enemy_table[min_x - 1][y] == '*') min_x--;
    while (max_x < SIZE - 2 && enemy_table[max_x + 1][y] == '*') max_x++;
    while (min_y > 1 && enemy_table[x][min_y - 1] == '*') min_y--;
    while (max_y < SIZE - 2 && enemy_table[x][max_y + 1] == '*') max_y++;

    for (int i = min_x - 1; i <= max_x + 1; i++) {
        for (int j = min_y - 1; j <= max_y + 1; j++) {
            if (i >= 1 && i < SIZE - 1 && j >= 1 && j < SIZE - 1) {
                if (enemy_table[i][j] == ' ') {
                    enemy_table[i][j] = '.';
                }
            }
        }
    }
}

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    matrix(table);
    matrix(enemy_table);

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
    int msg_type = 0;

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

        print_board(enemy_table, " ================= ENEMY =================\n");
        printf("\n\n");
        print_board(table, " ================== MY ===================\n");

        if (x != -1 && y != -1) {
            table[x][y] = prev_char;
            x = -1;
            y = -1;
        }

        if (msg_type == 1) {
            printf("\nWrong input!\n");
            msg_type = 0;
        }
        else if (msg_type == 2) {
            printf("\nMove already made!\n");
            msg_type = 0;
        }
        else if (last_status == 2) {
            printf("\nShip destroyed!\n");
            last_status = 0;
        }
        else if (last_status == 1) {
            printf("\nHit!\n");
            last_status = 0;
        }

        int target = 0;
        printf("\n1 - My, 2 - Enemy: ");
        if (scanf_s("%d", &target) != 1 || (target != 1 && target != 2)) {
            clear_input();
            msg_type = 1;
            continue;
        }

        int new_x = 0;
        char col_char = ' ';
        printf("x: ");
        if (scanf_s("%d", &new_x) != 1) {
            clear_input();
            msg_type = 1;
            continue;
        }
        printf("y: ");
        if (scanf_s(" %c", &col_char, 1) != 1) {
            clear_input();
            msg_type = 1;
            continue;
        }

        if (col_char >= 'a' && col_char <= 'z') {
            col_char = col_char - 'a' + 'A';
        }
        int new_y = col_char - 'A' + 1;

        if (new_x <= 0 || new_x >= SIZE - 1 || new_y <= 0 || new_y >= SIZE - 1) {
            msg_type = 1;
            continue;
        }

        if (target == 1) {
            if (table[new_x][new_y] == '.' || table[new_x][new_y] == '*') {
                msg_type = 2;
                continue;
            }
            x = new_x;
            y = new_y;
        }
        else if (target == 2) {
            if (enemy_table[new_x][new_y] != ' ') {
                msg_type = 2;
                continue;
            }

            int res = 0;
            printf("1 - Miss, 2 - Hit, 3 - Sunk: ");
            if (scanf_s("%d", &res) != 1 || res < 1 || res > 3) {
                clear_input();
                msg_type = 1;
                continue;
            }

            if (res == 1) {
                enemy_table[new_x][new_y] = '.';
            }
            else if (res == 2) {
                enemy_table[new_x][new_y] = '*';
            }
            else if (res == 3) {
                mark_sunk_enemy(new_x, new_y);
            }
        }
    }

    return 0;
}