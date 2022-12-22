#include <iostream>
using namespace std;

template <class T>
class AMVector {
private:
    int size, capacity;
    T *data;
public:

    // Initialize by specific capacity
    AMVector(int cap = 100) {
        capacity = cap;
        size = 0;
        data = new T[capacity];
    }

    // Initialize by list
    AMVector(initializer_list<T> list) {
        capacity = list.size() + 1;
        size = list.size();
        delete[] data;
        T *data = new T[list.size()];
        int k = 0;
        for (auto const &i: list) {
            data[k] = i;
            k++;
        }
    }

    // Initialize by n items from array
    AMVector(T *arr, int n) {
        size = n;
        capacity = n + 1;
        data = new T[n];
        for (int i = 0; i < n; ++i) {
            data[i] = arr[i];
        }
    }

    // Initialize with a copy constructor
    AMVector(const AMVector &other) {
        if (this != &other) {
            delete[] data;
            size = other.getSize();
            capacity = other.get_capacity();
            data = new T[capacity];
            for (int i = 0; i < other.getSize(); i++) {
                data[i] = other.data[i];
            }
        }
    }

    //--------------------------------- Destructor ------------------------------
    ~AMVector() {
        delete[] data;
    }
    
};










