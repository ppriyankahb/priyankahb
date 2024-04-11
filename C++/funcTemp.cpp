#include<iostream>
using namespace std;

template <class T1,class T2>

float funcAvg(T1 a, T2 b){
    float c= (a+b)/2.0;
    return c;
}

int main(){
    
    printf(" The avg value is %.2f \n",funcAvg(2,3));
    return 0;
}