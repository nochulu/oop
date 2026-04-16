#include <iostream>

class LineListException {};

template <class T>
class LineListElem {
public:
    T data;
    LineListElem<T>* next;

    LineListElem(const T& adata, LineListElem<T>* anext) {
        data = adata;
        next = anext;
    }
};

template <class T>
class LineList {
public:
    LineListElem<T>* start;
    int size;

    LineList() {
        start = nullptr;
        size = 0;
    }

    ~LineList() {
        while (start) deleteFirst();
    }

    void insertFirst(const T& adata) {
        LineListElem<T>* second = start;
        start = new LineListElem<T>(adata, second);
        size++;
    }

    void insertAfter(LineListElem<T>* ptr, const T& adata) {
        if (ptr) {
            LineListElem<T>* temp = ptr->next;
            ptr->next = new LineListElem<T>(adata, temp);
            size++;
        }
    }

    void deleteFirst() {
        if (start) {
            LineListElem<T>* temp = start->next;
            delete start;
            start = temp;
            size--;
        } else throw LineListException();
    }

    void deleteAfter(LineListElem<T>* ptr) {
        if (ptr && ptr->next) {
            LineListElem<T>* temp = ptr->next;
            ptr->next = ptr->next->next;
            delete temp;
            size--;
        } else throw LineListException();
    }
};

template <class T>
std::ostream& operator<<(std::ostream& out, LineList<T>& list) {
    LineListElem<T>* ptr = list.start;
    if (!ptr) out << "EMPTY";
    else while (ptr) {
        out << ptr->data << " ";
        ptr = ptr->next;
    }
    return out;
}
