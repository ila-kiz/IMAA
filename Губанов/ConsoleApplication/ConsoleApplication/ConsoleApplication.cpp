#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <windows.h>

const int BOARD_SIZE = 12;
const int SHIP_COUNT = 10;
const int TOTAL_DECKS = 20;
const int MAX_UNDO = 10;
const int SHIP_LENGTHS[SHIP_COUNT] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
const char RUS_LETTERS[] = "АБВГДЕЖЗИК";
const int SYM_MAX_LEN = 20;

char SYM_EMPTY[SYM_MAX_LEN] = "\033[94m.\033[0m"; // Синий
char SYM_SHIP[SYM_MAX_LEN] = "\033[93m#\033[0m"; // Желтый
char SYM_HIT[SYM_MAX_LEN] = "\033[91mX\033[0m"; // Красный
char SYM_MISS[SYM_MAX_LEN] = "\033[96m0\033[0m"; // Голубой
char SYM_BORDER_CORNER[SYM_MAX_LEN] = "\033[37m+\033[0m"; // Белый
char SYM_BORDER_H[SYM_MAX_LEN] = "\033[37m-\033[0m"; // Белый
char SYM_BORDER_V[SYM_MAX_LEN] = "\033[37m|\033[0m"; // Белый

struct Ship {
    int length;
    int x;
    int y;
    bool isHorizontal;
    int hits;
    bool isSunk;
};

struct GameState {
    char table[BOARD_SIZE][BOARD_SIZE];
    char enemy_table[BOARD_SIZE][BOARD_SIZE];
    Ship ships[SHIP_COUNT];
};

struct Game {
    GameState current;
    GameState history[MAX_UNDO];
    int history_count = 0;
};

// Очищает буфер ввода от лишних символов и переносов строки после scanf_s
void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Проверяет, находятся ли координаты внутри игрового поля
bool is_valid_cell(int x, int y) {
    return x >= 1 && x < BOARD_SIZE - 1 && y >= 1 && y < BOARD_SIZE - 1;
}

// Сохраняет текущее состояние игры в массив истории для возможности отмены хода
void save_state(Game& game) {
    if (game.history_count == MAX_UNDO) {
        // Сдвигаем историю влево, удаляя самый старый элемент, чтобы освободить место для нового
        for (int i = 0; i < MAX_UNDO - 1; i++) {
            game.history[i] = game.history[i + 1];
        }
        game.history_count--;
    }
    game.history[game.history_count++] = game.current;
}

// Откатывает текущее состояние игры на один сохраненный ход назад
void restore_state(Game& game) {
    game.current = game.history[--game.history_count];
}

// Инициализирует игровое поле: рисует внешнюю рамку и заполняет внутренние клетки точками
void init_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            bool is_top_bottom = (i == 0 || i == BOARD_SIZE - 1);
            bool is_left_right = (j == 0 || j == BOARD_SIZE - 1);

            if (is_top_bottom && is_left_right) board[i][j] = '+';
            else if (is_top_bottom) board[i][j] = '-';
            else if (is_left_right) board[i][j] = '|';
            else board[i][j] = '.';
        }
    }
}

// Проверяет, можно ли разместить корабль по заданным координатам с учетом границ поля и отступа в 1 клетку от других кораблей
bool can_place(const char board[BOARD_SIZE][BOARD_SIZE], Ship s) {
    for (int i = 0; i < s.length; i++) {
        int cur_x = s.x + (s.isHorizontal ? 0 : i);
        int cur_y = s.y + (s.isHorizontal ? i : 0);

        if (!is_valid_cell(cur_x, cur_y)) return false;

        // Проверяем окружающие клетки на наличие других кораблей
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (board[cur_x + dx][cur_y + dy] == '#') {
                    return false;
                }
            }
        }
    }
    return true;
}

// Отрисовывает палубы корабля на игровом поле
void draw_ship(char board[BOARD_SIZE][BOARD_SIZE], Ship s) {
    for (int i = 0; i < s.length; i++) {
        int cur_x = s.x + (s.isHorizontal ? 0 : i);
        int cur_y = s.y + (s.isHorizontal ? i : 0);
        board[cur_x][cur_y] = '#';
    }
}

// Автоматически расставляет все 10 кораблей случайным образом, если корали расставились не правильно (радом) генерирует заного
void place_all_ships(GameState& state) {
    init_board(state.table);
    for (int i = 0; i < SHIP_COUNT; i++) {
        bool placed = false;
        int attempts = 0;

        while (!placed) {
            if (++attempts > 100) {
                // Если не удалось разместить корабль за 100 попыток, сбрасываем всё и начинаем с первого корабля
                init_board(state.table);
                i = -1;
                break;
            }

            Ship& s = state.ships[i];
            s.length = SHIP_LENGTHS[i];
            s.isHorizontal = (rand() % 2 == 0);
            s.hits = 0;
            s.isSunk = false;

            // Вычисляем максимальные координаты, чтобы корабль не вышел за границы игрового поля
            int max_x = BOARD_SIZE - 2 - (s.isHorizontal ? 0 : s.length - 1);
            int max_y = BOARD_SIZE - 2 - (s.isHorizontal ? s.length - 1 : 0);
            s.x = (rand() % max_x) + 1;
            s.y = (rand() % max_y) + 1;

            if (can_place(state.table, s)) {
                draw_ship(state.table, s);
                placed = true;
            }
        }
    }
}

// Проверяет попадание по координатам на своем поле, увеличивает счетчик попаданий корабля и возвращает результат (0 - мимо, 1 - попал, 2 - убил)
int check_hit(Ship ships[], int x, int y) {
    for (int i = 0; i < SHIP_COUNT; i++) {
        for (int j = 0; j < ships[i].length; j++) {
            int cur_x = ships[i].x + (ships[i].isHorizontal ? 0 : j);
            int cur_y = ships[i].y + (ships[i].isHorizontal ? j : 0);

            if (cur_x == x && cur_y == y) {
                ships[i].hits++;
                if (ships[i].hits >= ships[i].length && !ships[i].isSunk) {
                    ships[i].isSunk = true;
                    return 2; // Убил
                }
                return 1; // Попал
            }
        }
    }
    return 0; // Мимо
}

// Помечает последнюю палубу как 'X', находит границы всего уничтоженного корабля и обводит его
void mark_sunk(char board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    board[x][y] = 'X';

    int min_x = x, max_x = x;
    int min_y = y, max_y = y;

    // Ищем реальные границы потопленного корабля, двигаясь от точки попадания вверх/вниз и влево/вправо
    while (min_x > 1 && board[min_x - 1][y] == 'X') min_x--;
    while (max_x < BOARD_SIZE - 2 && board[max_x + 1][y] == 'X') max_x++;
    while (min_y > 1 && board[x][min_y - 1] == 'X') min_y--;
    while (max_y < BOARD_SIZE - 2 && board[x][max_y + 1] == 'X') max_y++;

    // Обводим найденные границы зоной промахов
    for (int i = min_x - 1; i <= max_x + 1; i++) {
        for (int j = min_y - 1; j <= max_y + 1; j++) {
            if (is_valid_cell(i, j) && board[i][j] == '.') {
                board[i][j] = '0';
            }
        }
    }
}

// Вспомогательная функция для получения символа из цветной строки, чтобы нормально выводились цветные символы
char get_char_from_sym(const char* sym_str) {
    const char* p = sym_str;
    while (*p) {
        if (*p == '\033') {
            while (*p && *p != 'm') p++;
            if (*p == 'm') p++;
        }
        else {
            return *p;
        }
    }
    return '?';
}

// Выводит игровое поле в консоль вместе с заголовком
void print_board(const char board[BOARD_SIZE][BOARD_SIZE], const char* title) {
    printf("%s\n     ", title);
    for (int j = 0; j < BOARD_SIZE - 2; ++j) {
        printf("%c ", RUS_LETTERS[j]);
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (i > 0 && i < BOARD_SIZE - 1) printf("%2d ", i);
        else printf("   ");

        for (int j = 0; j < BOARD_SIZE; ++j) {
            char cell = board[i][j];
            const char* color_sym = nullptr;

            // Выбираем цветную строку в зависимости от символа в ячейке
            if (cell == '+') color_sym = SYM_BORDER_CORNER;
            else if (cell == '-') color_sym = SYM_BORDER_H;
            else if (cell == '|') color_sym = SYM_BORDER_V;
            else if (cell == '.') color_sym = SYM_EMPTY;
            else if (cell == '#') color_sym = SYM_SHIP;
            else if (cell == 'X') color_sym = SYM_HIT;
            else if (cell == '0') color_sym = SYM_MISS;
            else color_sym = "?";

            printf("%s ", color_sym);
        }
        printf("\n");
    }
}

// Выводит информационное сообщение о результате последнего действия или ошибке ввода, после чего сбрасывает флаги сообщений
void print_status_message(int& msg_type, int& last_status) {
    if (msg_type == 1) printf("\nНеверный ввод!\n");
    else if (msg_type == 2) printf("\nСюда уже стреляли!\n");
    else if (msg_type == 3) printf("\nНет ходов для отмены!\n");
    else if (msg_type == 4) printf("\nХод отменен!\n");
    else if (last_status == 2) printf("\nКорабль уничтожен!\n");
    else if (last_status == 1) printf("\nПопал!\n");

    msg_type = 0;
    last_status = 0;
}

// Переводит введенную русскую букву столбца (в любом регистре) в числовой индекс массива
int get_col_index(char c) {
    if (c >= 'а' && c <= 'я') {
        c = c - 'а' + 'А';
    }
    for (int i = 0; i < BOARD_SIZE - 2; i++) {
        if (RUS_LETTERS[i] == c) return i + 1;
    }
    return -1;
}

// Запрашивает у пользователя координаты выстрела и проверяет их корректность
bool get_coordinates(int& x, int& y) {
    char col_char = ' ';
    printf("x: ");
    if (scanf_s("%d", &x) != 1) {
        clear_input();
        return false;
    }
    printf("y: ");
    if (scanf_s(" %c", &col_char, 1) != 1) {
        clear_input();
        return false;
    }
    clear_input();

    y = get_col_index(col_char);
    return is_valid_cell(x, y);
}

// Обрабатывает запрос на отмену последнего хода: проверяет наличие истории, запрашивает подтверждение и восстанавливает предыдущее состояние
void handle_undo(Game& game, int& msg_type) {
    if (game.history_count == 0) {
        msg_type = 3;
        return;
    }
    int confirm = 0;
    printf("Точно отменить ход? (1 - Да, 2 - Нет): ");
    if (scanf_s("%d", &confirm) != 1 || (confirm != 1 && confirm != 2)) {
        clear_input();
        msg_type = 1;
        return;
    }
    clear_input();

    if (confirm == 1) {
        restore_state(game);
        msg_type = 4;
    }
}

// Обрабатывает выстрел противника по своему полю: проверяет повторный выстрел, сохраняет ход для отмены и обновляет статус корабля и клетки
void handle_my_board_shot(Game& game, int x, int y, int& msg_type, int& last_status) {
    char& cell = game.current.table[x][y];
    if (cell == '0' || cell == 'X') {
        msg_type = 2;
        return;
    }

    save_state(game);

    if (cell == '#') {
        last_status = check_hit(game.current.ships, x, y);
        if (last_status == 2) mark_sunk(game.current.table, x, y);
        else cell = 'X';
    }
    else {
        cell = '0';
        last_status = 0;
    }
}

// Обрабатывает выстрел игрока по полю врага: запрашивает у пользователя результат выстрела и отмечает его на карте
void handle_enemy_board_shot(Game& game, int x, int y, int& msg_type) {
    char& cell = game.current.enemy_table[x][y];
    if (cell != '.') {
        msg_type = 2;
        return;
    }

    int res = 0;
    printf("1 - Мимо, 2 - Попал, 3 - Убил: ");
    if (scanf_s("%d", &res) != 1 || res < 1 || res > 3) {
        clear_input();
        msg_type = 1;
        return;
    }
    clear_input();

    save_state(game);

    if (res == 1) cell = '0';
    else if (res == 2) cell = 'X';
    else if (res == 3) mark_sunk(game.current.enemy_table, x, y);
}

// Проверяет условия окончания игры: возвращает 1 при победе, 2 при поражении или 0, если игра продолжается
int check_game_over(const GameState& state) {
    int my_sunk_ships = 0;
    for (int i = 0; i < SHIP_COUNT; i++) {
        if (state.ships[i].isSunk) my_sunk_ships++;
    }
    if (my_sunk_ships == SHIP_COUNT) return 2;

    int enemy_hits = 0;
    for (int i = 1; i < BOARD_SIZE - 1; i++) {
        for (int j = 1; j < BOARD_SIZE - 1; j++) {
            if (state.enemy_table[i][j] == 'X') enemy_hits++;
        }
    }
    if (enemy_hits >= TOTAL_DECKS) return 1;

    return 0;
}

// Запуск, галвная функция: настраивает консоль, инициализирует игровые поля, расставляет корабли и запускает основной игровой цикл
int main() {
    // поддержва кирилицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    // включает цветной текст и управление курсором в консоли
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode)) {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }

    MoveWindow(GetConsoleWindow(), 1350, 300, 600, 700, TRUE); // размеры консоли

    Game game;
    init_board(game.current.enemy_table);
    place_all_ships(game.current);

    int last_status = 0;
    int msg_type = 0;

    while (true) {
        system("cls");
        print_board(game.current.enemy_table, " ======= ПОЛЕ ВРАГА =======\n");
        printf("\n\n");
        print_board(game.current.table, "  ======= МОЕ ПОЛЕ =======\n");

        int game_result = check_game_over(game.current);
        if (game_result == 1) {
            printf("\nВы уничтожили весь флот противника!\n");
            break;
        }
        else if (game_result == 2) {
            printf("\nВесь ваш флот потоплен.\n");
            break;
        }

        print_status_message(msg_type, last_status);

        int target = 0;
        printf("\n1 - Мое поле, 2 - Поле врага, 3 - Отмена хода: ");
        if (scanf_s("%d", &target) != 1 || target < 1 || target > 3) {
            clear_input();
            msg_type = 1;
            continue;
        }
        clear_input();

        if (target == 3) {
            handle_undo(game, msg_type);
            continue;
        }

        int x = 0, y = 0;
        if (!get_coordinates(x, y)) {
            msg_type = 1;
            continue;
        }

        if (target == 1) {
            handle_my_board_shot(game, x, y, msg_type, last_status);
        }
        else if (target == 2) {
            handle_enemy_board_shot(game, x, y, msg_type);
        }
    }


    system("pause");
    return 0;
}
