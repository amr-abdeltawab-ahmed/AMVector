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

    // Access operations
    T& operator[](int index){
        if(index > size-1){
            cout << "An error has occured, index out of the range." << endl;
            exit(-1);
        }
        return data[index];
    }

    // Copy assignment
    AMVector &operator=(const AMVector& other){
        size = other.getSize();
        capacity = other.get_capacity();
        data = new T[capacity];
        for(int i = 0; i < other.getSize(); i++){
            data[i] = other.data[i];
        }
    }

    // Move assignment
    AMVector &operator=(const AMVector&& other){
        if (this != &other){
            size = other.getSize();
            capacity = other.get_capacity();
            data = new T[capacity];
            for (int i = 0; i < other.getSize(); i++){
                data[i] = other.data[i];
            }
            //do clear for other
            other.size = 0;
            other.capacity = 0;
            other.data = nullptr;
        }
        return *this;
    }


    T& operator=(const T& other){
        if(this != &other){
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for(int i = 0; i < other.size; i++){
                data[i] = other.data[i];
            }
        }
        else{
            cout << "Cannot delete self" << endl;
        }
    }


    //push_back and pop_back
    void push_back(T item){
        if(size < capacity){
            data[size++] = item;
        }
        else{
            T* newdata = new T[capacity*2];
            capacity *= 2;
            for(int i = 0; i < size; i++){
                newdata[i] = data[i];
            }
            delete[] data;
            data = newdata;
            newdata = nullptr;
            data[size++] = item;
        }
    }
    T pop_back(){
        if (size > 0)  {
            return data[size-- - 1];
        }
        else {
            cout << "nothing to pop";
        }
    }




};










