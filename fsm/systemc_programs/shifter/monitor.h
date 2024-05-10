#include<systemc.h>

SC_MODULE(monitor)
{
sc_in<bool>rst,clk,input;
sc_in<sc_uint<4>>registers;
void function(){
cout<< " Inputs are " << rst <<" "<<input<<" "<< "Output are "<<registers <<endl;
}

SC_CTOR(monitor){
SC_METHOD(function);
sensitive << clk.pos();

}

};
