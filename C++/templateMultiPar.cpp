#include<iostream>
using namespace std;

template <class T1,class T2>
class Vector{
    public:
    T1 data1;
    T2 data2;

    public :
    Vector(T1 a,T2 b){
        data1 = a;
        data2 = b;
    }

    void display(){
        cout << this->data1 <<endl<<this->data2<< endl;
    }
};

int main(){

    Vector <float, char> v1(2.2,'p');
    v1.display();
    return 100;
}