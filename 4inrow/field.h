#include <iostream>
#include <vector>

const int FIELD_WIDTH = 7;
const int FIELD_HEIGHT = 6;
const int WIN_LENGTH = 4;

enum Cell {
    EMPTY = 0,
    RED = 1,
    YELLOW = 2
};

class Field {
    Cell cells[FIELD_WIDTH][FIELD_HEIGHT]; // Двумерный массив ячеек
    bool isRedTurn;
    Cell winner;

    void checkWinner(); //метод проверки победы

public:
    Field(bool isRedFirst = true);
    void clear(bool isRedFirst);
    bool makeTurn(int column); // Выполнение хода
    
    bool isOver() const; //Контроль окончания игры
    bool isRedTurnNow() const { return isRedTurn; }
    Cell getWinner() const { return winner; }
    
    void print() const; // отрисовка поля в консоли
};