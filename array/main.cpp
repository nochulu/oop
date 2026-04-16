#include <iostream>
#include <ctime>
#include <fstream>
#include "array.h"

using namespace std;

int main() {
    Array arr(4);
    for (int i = 0; i < 4; i++) arr.insert(i + 1);
    cout << arr << endl;
    for (int i = 0; i < 8; i += 2) arr.insert(10 + i, i);
    cout << arr << endl;
    for (int i = 1; i < 8; i += 2) arr[i] = 20 + i;
    cout << arr << endl;
    for (int i = 6; i >= 0; i -= 3) arr.remove(i);
    cout << arr << endl;

    int k, count;
    cout << "Enter the number of tries(count): ";
    cin >> count;
    cout << "Enter the elimination step (k): ";
    cin >> k;

    ifstream checkFile("results.csv");
    bool isEmpty = checkFile.peek() == EOF;
    checkFile.close();

    ofstream file("results.csv", ios::app);

    if (isEmpty) {
        file << "N, Answer, Calculation time (sec)" << endl;
    }

    for (int i = 0; i < count; i++) {
        int N;
        cout << "Enter the value N" << i + 1 << ": ";
        cin >> N;

        Array people(N);
        for (int j = 1; j <= N; j++) {
            people.insert(j);
        }

        clock_t start = clock();

        int currentIndex = 0;
        while (people.getSize() > 1) {
            currentIndex = (currentIndex + k - 1) % people.getSize();
            people.remove(currentIndex);
        }

        clock_t end = clock();
        double duration = (double)(end - start) / CLOCKS_PER_SEC;

        file << N << "," << people[0] << "," << duration << endl;
        
        cout << "N=" << N << " solved. The winner: " << people[0]
             << ". Time: " << duration << " sec." << endl;
    }

    file.close();
    cout << "The data is recorded in results.csv (appended)" << endl;

    return 0;
}
