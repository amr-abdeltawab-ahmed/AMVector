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

    // Capacity operations
    int getSize() const{
        return size;
    }
    int get_capacity() const {
        return capacity;
    }
    bool empty(){
        if (size == 0){
            return true;
        }
        return false;
    }
    void resize(){
        capacity *= 2;
    }

    // Comparison operations
    bool operator==(const AMVector<T>& other){
        if (size == other.getSize()) {
            for (int i = 0; i < size; i ++)
                if (data[i] != other[i]){
                    return false;
                }
            return true;
        }
        else{
            return false;
        }
    }

    bool operator< (const AMVector<T>& other){
        int smaller_size;
        if (size < other.getSize()){
            smaller_size = size;
        }
        else {
            smaller_size = other.getSize();
        }
        for (int i = 0; i < smaller_size; i++){
            if (data[i] != other[i]){ // Find the first mismatching element
                return data[i] < other[i];
            }
        }
        return size < other.getSize();
    }

    bool operator> (const AMVector<T>& other){
        if (other > data){
            return true;
        }
        else{
            return false;
        }
    }

    //----------------------------------------- Iterator ---------------------------------------//
    class iterator {
    private:
        T* ptr;
    public:
        explicit iterator() : ptr(nullptr){}
        explicit iterator(T* p): ptr(p){}

        bool operator==(const iterator& obj) {
            return ptr == obj.ptr;
        }

        bool operator!= (const iterator &obj) {
            return !(*this == obj);
        }

        T operator*() const{
            return *ptr;
        }

        iterator& operator++(){
            ++ptr;
            return *this;
        }

        iterator& operator--(){
            --ptr;
            return *this;
        }

        iterator operator++(int){
            iterator temp(*this);
            ++*this;
            return temp;
        }

        iterator operator--(int){
            iterator temp(*this);
            --*this;
            return temp;
        }

        iterator begin() const;
        iterator end() const;

        iterator erase(iterator pos);
        iterator erase(iterator first, iterator last);

    };


    // return begin iterator
    AMVector<T>::iterator begin() const {
        return iterator(data);
    }
    // return class to return end iterator
    AMVector<T>::iterator end() const {
        return iterator(data + size);
    }

//Erase functions
    AMVector<T>::iterator erase(iterator pos) {
        int counter = 0,counter2 = 0;
        T*data_temp = new T[capacity];
        for(int i = 0;i < size; i++){
            if(counter2 == 0 && data[i] == *pos){
                counter2++;
                continue;
            }
            else{
                data_temp[counter] = data[i];
                counter++;
            }
        }
        delete[]data;
        size--;
        T* data = new T[capacity];
        for(int i = 0;i < size; i++)
            data[i] = data_temp[i];

        delete[] data_temp;

    }

    AMVector<T>::iterator erase(iterator first, iterator last){
        int counter=0,pos_first,pos_end;
        T* data_temp = new T[size];

        for(int i = 0;i < size ;i++){
            if(data[i] == *first){
                cout << *last << "   This is first   \n";
                pos_first = i;
            }
            else if(data[i] == *last){
                cout << *last << "   This is last   \n";
                pos_end = i;
            }
        }

        for(int i = 0; i < size; i++){
            if(i < pos_first || i > pos_end){
                data_temp[counter] = data[i];
                counter++;
            }
        }

        delete[] data;
        size = counter;
        T* data = new T[size];
        for(int i = 0;i < size; i++){
            data[i] = data_temp[i];
        }
        delete [] data_temp;

    }



};










