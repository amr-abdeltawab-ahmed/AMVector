#include <iostream>
#include <vector>
using namespace std;
/*
template<typename AMVector>
class VectorIterator{
public:
    using ValueType = typename AMVector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
public:
    VectorIterator(PointerType ptr){_Ptr = ptr;}
    VectorIterator& operator++(){
        _Ptr++;
        return *this;
    }
    VectorIterator operator++(int){
        VectorIterator iterator = *this;
        ++(*this);
        return iterator;
    }
    VectorIterator& operator--(){
        _Ptr--;
        return *this;
    }
    VectorIterator operator--(int){
        VectorIterator iterator = *this;
        --(*this);
        return iterator;
    }
    ReferenceType operator[](int index){
        return *(_Ptr + index);
    }
    ReferenceType operator*(){
        return *_Ptr;
    }
    bool operator ==(const VectorIterator& other) const{
        return _Ptr == other._Ptr;
    }
private:
    PointerType _Ptr;
};
*/

template< typename T >
class AMVector {
/*
public:
    using ValueType = T;
    using Iterator = VectorIterator<AMVector<T>>;
*/
private:
    int Size,Capacity;
    T *Data;
public:
    int getSize(){
        return Size;
    }
    int getCapacity(){
        return Capacity;
    }
    //-------------------------------- constructor
    AMVector (int capa = 2){
        Capacity = capa;
        Size = 0;
        Data = new T[Capacity];
    }
    //AMVector (T*, int  n )

    //------------------------------ copy constructor
    AMVector (const AMVector& other){
        if(this != &other){
            delete[] Data;
            Capacity = other.Capacity;
            Size = other.Size;
            Data = new T[Capacity];
            for(int i = 0; i < other.Size; i++){
                Data[i] = other.Data[i];
            }
        }
        else{
            cout << "Cannot delete self" << endl;
        }
    }
    //--------------------------------- Destructor
    ~AMVector(){
        delete[] Data;
    }
    //--------------------------------- copy assignment
    T& operator=(const T& other){
        cout<<"use copy"<<endl;
        if(this == &other)
            return *this;
        if(this != &other){
            delete[] Data;
            Size = other.Size;
            Capacity = other.Capacity;
            Data = new T[Capacity];
            for(int i = 0; i < Size; i++){
                Data[i] = other.Data[i];
            }
        }
        return *this;

    }
    //--------------------------------- move assignment
    AMVector& operator=(AMVector&& other) noexcept{
        cout<<endl<<"move"<<endl;
        if (this != &other)
        {
            // Free the existing resource.
            delete[] Data;

            // Copy the data pointer and its length from the
            // source object.
            Data = other.Data;
            Capacity = other.Capacity;
            Size = other.Size;

            // Release the data pointer from the source object so that
            // the destructor does not free the memory multiple times.
            other.Data = nullptr;
            other.Capacity = 0;
            other.Size = 0;
        }
        return *this;
    }
    //---------------------------------- operator[]
    T& operator[](int index){
        if(index > Size-1){
            cout << "Error, index out of range." << endl;
            exit(0);
        }
        return Data[index];
    }
    //------------------------------- push_back
    int push_back(const T& element){
        if(Size < Capacity){
            Data[Size++] = element;
        }
        else{
            T* nData = new T[Capacity*2];
            Capacity *= 2;
            for(int i = 0; i < Size; i++){
                nData[i] = Data[i];
            }
            delete[] Data;
            Data = nData;
            nData = nullptr;
            Data[Size++] = element;
        }
        return Size;
    }
    //----------------------------- pop_back
    T pop_back(){
        T* nData = new T[Capacity];
        for(int i = 0;i < Size-1 ;i++){
            nData[i] = Data[i];
        }
        Size--;
        delete[] Data;
        Data = nData;
        nData = nullptr;
        return Data[Size];
    }
    //void erase(iterator)
    //void erase(iterator1, iterator2)
    //------------------------------ clear
    void clear(){
        Data = nullptr;
        Size =0;
    }
    //void insert(iterator, T)

    const T begin(){
        return *Data;
    }
    const T end(){
        return Data[Size-1];
    }
    //---------------------------- operator ==
    bool operator==(const AMVector<T>& other){
        if(Size != other.Size)return false;
        else{
            for(int i = 0;i < Size;i++){
                return
                        Data[i] == other.Data[i]?true : false;
            }
        }
    }
    //---------------------------- operator <
    bool operator< (const AMVector<T>&){
        /*
        int counter= 0;
        if(other.Size > Size){
            for(int i = Size;i < other.Size;i++){
                Data[i] = 0;
            }
        }
        if(Size > other.Size){
            for(int i = other.Size;i < Size;i++){
                other.Data[i] = 0;
            }
        }
        for(int i = 0;i < Size;i++)
            if(Data[i] < other.Data[i])counter++;
        //--//
        */

    }
    //----------------------------- Size
    int size() const{
        return Size;
    }
    //----------------------------- Capacity
    int capacity() const{
        return Capacity;
    }
    //---------------------------- resize
    void resize(){
        Capacity *= 2;
    }
    //----------------------------- empty
    bool empty(){
        return
                Size?false:true;
    }
    //----------------------------- operator <<
    friend ostream& operator << (ostream& out,const AMVector<T>& obj){
        for(int i = 0; i < obj.Size;i++){
            out<<obj.Data[i]<<endl;
        }
        return out;
    }

};

main(){
    AMVector <string> vec(1);
    vec.push_back("mohamed");
    vec.push_back("and");
    vec.push_back("amr");
    AMVector<string> vec2(1);
    vec2.push_back("mohamed");
    vec2.push_back("and");
    vec2.push_back("amr");


    std::vector<int> alice{1, 2, 3};
    std::vector<int> bob{0, 0, 0,1};
    std::vector<int> eve{1, 2, 3};
    std::cout << "alice <  bob returns " << (alice < bob) << '\n';


}












