#include<iostream>
using namespace std;

template <class T1=int ,class T2=float ,class T3 = string>

class Myclass{
    public :
    T1 a;
    T2 b;
    T3 c;

    public :
    Myclass(T1 x,T2 y,T3 z){
        a=x;
        b=y;
        c=z;
    }
    void display(){
        cout<< " The value of a is " << a<<endl;
        cout<<" The value of b is " << b<<endl;
        cout<<" The value of c is "<< c<<endl;
    }
};

int main(){
    Myclass<> m(9,9.7,"Priyanka");
    m.display();
    cout<<endl;
    Myclass<float,string,string> m1(9.8,"bhuvi","priya");
    m1.display();
    return 0;
}