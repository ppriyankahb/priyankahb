#include<systemc.h>

SC_MODULE(monitor)
{
sc_in<bool>rst,clk;
sc_in<sc_uint<4>>count;
void function(){
cout<< " Inputs are " << rst <<" "<< "Output are "<<count <<endl;
}

SC_CTOR(monitor){
SC_METHOD(function);
sensitive << clk.pos();

}

};
