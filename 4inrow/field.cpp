#include "field.h"

Field::Field(bool isRedFirst) {
    clear(isRedFirst); // Инициализация через конструктор
}

void Field::clear(bool isRedFirst) {
    isRedTurn = isRedFirst;
    winner = EMPTY;
    for (int i = 0; i < FIELD_WIDTH; i++)
        for (int j = 0; j < FIELD_HEIGHT; j++)
            cells[i][j] = EMPTY;
}

bool Field::makeTurn(int column) {
    // Проверка корректности колонки и наличия победителя
    if (winner != EMPTY || column < 1 || column > FIELD_WIDTH) return false;

    int i = column - 1;
    for (int j = 0; j < FIELD_HEIGHT; j++) {
        if (cells[i][j] == EMPTY) {
            cells[i][j] = isRedTurn ? RED : YELLOW;
            checkWinner();
            isRedTurn = !isRedTurn;
            return true;
        }
    }
    return false; // Колонка полная
}

void Field::checkWinner() {
    // Направления поиска: горизонталь, вертикаль, две диагонали
    const int di[] = {1, 0, 1, 1};
    const int dj[] = {0, 1, -1, 1};

    for (int i = 0; i < FIELD_WIDTH; i++) {
        for (int j = 0; j < FIELD_HEIGHT; j++) {
            Cell start = cells[i][j];
            if (start == EMPTY) continue;

            for (int dir = 0; dir < 4; dir++) {
                int length = 0, iline = i, jline = j;
                while (++length < WIN_LENGTH) {
                    iline += di[dir];
                    jline += dj[dir];
                    if (iline < 0 || iline >= FIELD_WIDTH || jline < 0 || jline >= FIELD_HEIGHT) break;
                    if (cells[iline][jline] != start) break;
                }
                if (length == WIN_LENGTH) {
                    winner = start;
                    return;
                }
            }
        }
    }
}

bool Field::isOver() const {
    if (winner != EMPTY) return true;
    for (int i = 0; i < FIELD_WIDTH; i++)
        if (cells[i][FIELD_HEIGHT - 1] == EMPTY) return false;
    return true; // Ничья, если все поле занято
}

void Field::print() const {
    for (int j = FIELD_HEIGHT - 1; j >= 0; j--) {
        for (int i = 0; i < FIELD_WIDTH; i++) {
            if (cells[i][j] == RED) std::cout << "R ";
            else if (cells[i][j] == YELLOW) std::cout << "Y ";
            else std::cout << ". ";
        }
        std::cout << "\n";
    }
    std::cout << "1 2 3 4 5 6 7\n";
}