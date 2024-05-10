#include<systemc.h>

SC_MODULE(monitor)
{
sc_in<bool>a,b,sum,co;

void function(){
cout<< " Inputs are " << a <<b<<" "<< "Output "<<sum<<" "<<co<<endl;
}

SC_CTOR(monitor){
SC_METHOD(function);
sensitive << a << b;

}

};
