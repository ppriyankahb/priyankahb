#include<systemc.h>

SC_MODULE(monitor)
{
sc_in<bool>a,b,out;

void function(){
cout<< " Inputs are " << a <<b<<" "<< "Output "<<out<<endl;
}

SC_CTOR(monitor){
SC_METHOD(function);
sensitive << a << b;

}

};
