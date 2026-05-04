#include <iostream>
#include "field.h"

using namespace std;

int main() {
    Field field(true);

    while (!field.isOver()) {
        field.print();
        
        //  Вывод текущего игрока
        cout << (field.isRedTurnNow() ? "Red" : "Yellow") 
                  << " player's turn. Enter column (1-7): ";
        
        int column;
        if (!(cin >> column)) {
            cout << "Invalid input. Game terminated." << endl;
            break;
        }

        // Попытка сделать ход
        if (!field.makeTurn(column)) {
            cout << "Invalid move! Column is full or out of range. Try again." << endl;
        }
    }

    field.print();
    
    // Вывод финального результата 
    Cell winner = field.getWinner();
    if (winner == RED) {
        cout << "Congratulations! RED player wins!" << endl;
    } else if (winner == YELLOW) {
       cout << "Congratulations! YELLOW player wins!" << endl;
    } else {
        cout << "It's a DRAW! The board is full." << endl;
    }

    cin.ignore();
    cin.get();    
    return 0;
}