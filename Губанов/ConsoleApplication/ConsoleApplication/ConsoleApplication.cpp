#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>

const int SIZE = 20;
const int SHIPS_COUNT = 10;

struct Ship {
    int size;
    int x;
    int y;
    bool horizontal;
    int hits;
    bool dead;
};

void init_map(char map[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((i == 0 || i == SIZE - 1) && (j == 0 || j == SIZE - 1)) {
                map[i][j] = '+';
            }
            else if (i == 0 || i == SIZE - 1) {
                map[i][j] = '-';
            }
            else if (j == 0 || j == SIZE - 1) {
                map[i][j] = '|';
            }
            else {
                map[i][j] = ' ';
            }
        }
    }
}

bool can_place(char map[SIZE][SIZE], Ship ship) {
    for (int i = 0; i < ship.size; i++) {
        int x = ship.horizontal ? ship.x : ship.x + i;
        int y = ship.horizontal ? ship.y + i : ship.y;
        if (x < 1 || x >= SIZE - 1 || y < 1 || y >= SIZE - 1) {
            return false;
        }
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (map[x + dx][y + dy] == '#') {
                    return false;
                }
            }
        }
    }
    return true;
}

void draw_ship(char map[SIZE][SIZE], Ship ship) {
    for (int i = 0; i < ship.size; i++) {
        if (ship.horizontal) {
            map[ship.x][ship.y + i] = '#';
        }
        else {
            map[ship.x + i][ship.y] = '#';
        }
    }
}

void place_ships(char map[SIZE][SIZE], Ship* ships) {
    for (int i = 0; i < SHIPS_COUNT; i++) {
        bool placed = false;
        while (!placed) {
            ships[i].size = (rand() % 4) + 1;
            ships[i].horizontal = (rand() % 2 == 0);
            ships[i].hits = 0;
            ships[i].dead = false;

            if (ships[i].horizontal) {
                ships[i].x = (rand() % (SIZE - 2)) + 1;
                ships[i].y = (rand() % (SIZE - 1 - ships[i].size)) + 1;
            }
            else {
                ships[i].x = (rand() % (SIZE - 1 - ships[i].size)) + 1;
                ships[i].y = (rand() % (SIZE - 2)) + 1;
            }

            if (can_place(map, ships[i])) {
                draw_ship(map, ships[i]);
                placed = true;
            }
        }
    }
}

void start_game(char enemy_map[SIZE][SIZE], char player_map[SIZE][SIZE], Ship* player_ships) {
    init_map(enemy_map);
    init_map(player_map);
    place_ships(player_map, player_ships);
}

void print_map(const char* title, char map[SIZE][SIZE]) {
    printf("  ================= %s =================\n\n", title);
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
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

void print_status(int status) {
    printf("\n");
    if (status == 2) printf("Dead!\n");
    else if (status == 1) printf("Hit!\n");
    else if (status == 0) printf("Away\n");
    else if (status == 3) printf("Already shot!\n");
    else if (status == 4) printf("Wrong input!\n");
}

void draw_screen(char enemy_map[SIZE][SIZE], char player_map[SIZE][SIZE], int status) {
    system("cls");
    print_map("ENEMY", enemy_map);
    printf("\n");
    print_map("YOU", player_map);
    print_status(status);
}

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

bool read_shot(int& x, int& y) {
    char letter = ' ';
    printf("\nx: ");
    if (scanf_s("%d", &x) != 1) {
        clear_input();
        return false;
    }
    printf("y: ");
    if (scanf_s(" %c", &letter, 1) != 1) {
        clear_input();
        return false;
    }
    clear_input();

    if (letter >= 'a' && letter <= 'z') {
        letter = letter - 'a' + 'A';
    }
    y = letter - 'A' + 1;

    return (x > 0 && x < SIZE - 1 && y > 0 && y < SIZE - 1);
}

int read_result() {
    int res = -1;
    printf("Result (0 - away, 1 - hit, 2 - dead): ");
    if (scanf_s("%d", &res) != 1) {
        clear_input();
        return 4;
    }
    clear_input();
    if (res < 0 || res > 2) {
        return 4;
    }
    return res;
}

void mark_dead_ship(char map[SIZE][SIZE], int x, int y) {
    int min_x = x, max_x = x;
    int min_y = y, max_y = y;

    while (min_x > 1 && map[min_x - 1][y] == '*') min_x--;
    while (max_x < SIZE - 2 && map[max_x + 1][y] == '*') max_x++;
    while (min_y > 1 && map[x][min_y - 1] == '*') min_y--;
    while (max_y < SIZE - 2 && map[x][max_y + 1] == '*') max_y++;

    for (int i = min_x - 1; i <= max_x + 1; i++) {
        for (int j = min_y - 1; j <= max_y + 1; j++) {
            if (map[i][j] == ' ') {
                map[i][j] = '.';
            }
        }
    }
}

int mark_shot(char map[SIZE][SIZE], int x, int y) {
    if (map[x][y] != ' ') {
        return 3;
    }

    int res = read_result();
    if (res == 0) {
        map[x][y] = '.';
    }
    else if (res == 1) {
        map[x][y] = '*';
    }
    else if (res == 2) {
        map[x][y] = '*';
        mark_dead_ship(map, x, y);
    }
    return res;
}

void game_loop(char enemy_map[SIZE][SIZE], char player_map[SIZE][SIZE]) {
    int status = -1;

    while (true) {
        draw_screen(enemy_map, player_map, status);

        int x = 0, y = 0;
        if (!read_shot(x, y)) {
            status = 4;
            continue;
        }

        status = mark_shot(enemy_map, x, y);
    }
}

int main() {
    srand((unsigned int)time(NULL));

    char enemy_map[SIZE][SIZE];
    char player_map[SIZE][SIZE];
    Ship player_ships[SHIPS_COUNT];

    start_game(enemy_map, player_map, player_ships);
    game_loop(enemy_map, player_map);

    return 0;
}
