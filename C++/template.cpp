#include<iostream>
using namespace std;

template <class T>
class Vector{
    public:
    int size;
    T * array;

    public:
    Vector(int m){
        size=m;
        array = new T[size];
    }

    T dotProduct(Vector &v){
        T d=0;
        for(int i=0;i<size;i++){
        d  += this->array[i] *array[i];
        }
        return d;


    }
};

int main(){
    Vector <float> v1(4);
    v1.array[0] = 0.1;
    v1.array[1] = 1.1;
    v1.array[2] = 2.1;
    v1.array[3] = 3.1;
    Vector <float> v2(4);
    v2.array[0] = 0.1;
    v2.array[1] = 1.1;
    v2.array[2] = 2.1;
    v2.array[3] = 3.1;
    cout<< v1.dotProduct(v2)<<endl;
    return 0;
}