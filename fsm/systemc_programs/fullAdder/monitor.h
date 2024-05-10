#include<systemc.h>

SC_MODULE(monitor)
{
sc_in<bool>a,b,cin,sum,co;

void function(){
cout<< " Inputs are " << a <<b<<cin<<" "<< "Output "<<sum<<" "<<co<<endl;
}

SC_CTOR(monitor){
SC_METHOD(function);
sensitive << a << b<<cin;

}

};
