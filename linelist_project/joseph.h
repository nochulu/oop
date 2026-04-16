#include "linelist.h"

int solveJosephus(int n, int k) {
    LineList<int> people;
    for (int i = n; i >= 1; i--) {
        people.insertFirst(i);
    }

    LineListElem<int>* curr = people.start;
    LineListElem<int>* prev = nullptr;

    while (people.size > 1) {
        for (int i = 1; i < k; i++) {
            prev = curr;
            curr = curr->next;
            if (!curr) {
                prev = nullptr;
                curr = people.start;
            }
        }

        LineListElem<int>* nextToKill = curr->next;

        if (curr == people.start) {
            people.deleteFirst();
            curr = people.start;
        } else {
            people.deleteAfter(prev);
            curr = nextToKill;
        }

        if (!curr) curr = people.start;
    }

    return people.start->data;
}
