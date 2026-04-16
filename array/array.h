#include <iostream>

using namespace std;

const int DEFAULT_CAPACITY = 10;

class ArrayException {};

class Array {
private:
    int* ptr;
    int size;
    int capacity;
public:
    explicit Array(int startCapacity = DEFAULT_CAPACITY);
    ~Array();
    Array(const Array& arr);
    Array& operator =(const Array& arr);
    int& operator[](int index);
    int operator[](int index) const;
    void insert(int elem, int index);
    void insert(int elem);
    void remove(int index);
    int get(int index) const;
    void set(int index, int elem);
    void increaseCapacity(int newCapacity);
    int getSize() const;
    friend ostream& operator <<(ostream& out,
        const Array& arr);
};