#include "linelist.h"

int solveJosephus(int n, int k) {
    if (n <= 0 || k <= 0) return -1; 

    // создаем обычный список людей
    LineList<int> people;
    for (int i = n; i >= 1; i--) {
        people.insertFirst(i);
    }

    // ищем хвост, чтобы закольцевать список
    LineListElem<int>* tail = people.start;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = people.start; // зациклили

    LineListElem<int>* curr = people.start;
    LineListElem<int>* prev = tail; // перед первым элементом идет хвост

    // удаляем людей по кругу, пока не останется один
    while (people.size > 1) {
        // сдвигаемся на k-1 шаг вперед
        for (int i = 1; i < k; i++) {
            prev = curr;
            curr = curr->next;
        }

        // если удаляем старт структуры, двигаем указатель people.start вперед
        if (curr == people.start) {
            people.start = curr->next;
        }

        // перебрасываем указатель в обход удаляемого элемента
        prev->next = curr->next;
        LineListElem<int>* nextToLive = curr->next;

        delete curr;
        people.size--;

        curr = nextToLive;
    }

    // убираем зацикливание, чтобы деструктор LineList не ушел в бесконечный цикл
    people.start->next = nullptr; 

    return people.start->data;
}