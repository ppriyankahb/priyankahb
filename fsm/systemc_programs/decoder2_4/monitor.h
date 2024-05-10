#include<systemc.h>

SC_MODULE(monitor)
{
sc_in<bool>enable;
sc_in<sc_uint<2>>in;
sc_in<sc_uint<4>>out;

void function(){
cout<< " Inputs are " << in <<" "<< "Output "<<out <<endl;
}

SC_CTOR(monitor){
SC_METHOD(function);
sensitive << enable<<in;

}

};
