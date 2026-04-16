#include <iostream>
#include <fstream>
#include <ctime>
#include "joseph.h"

using namespace std;

int main() {
    int count, k;
    cout << "Enter count: "; cin >> count;
    cout << "Enter k: "; cin >> k;

    ofstream file("results.csv", ios::app);
    ifstream check("results.csv");
    bool isEmpty = check.peek() == EOF;
    check.close();

    if (isEmpty) {
        file << "N, Winner, Time(sec)" << endl;
    }

    for (int i = 0; i < count; i++) {
        int N;
        cout << "N" << i + 1 << ": "; cin >> N;

        clock_t start = clock();
        int winner = solveJosephus(N, k);
        clock_t end = clock();

        double duration = (double)(end - start) / CLOCKS_PER_SEC;

        file << N << "," << winner << "," << duration << endl;
        cout << "N=" << N << " | Winner: " << winner << " | Time: " << duration << "s" << endl;
    }

    file.close();
    return 0;
}