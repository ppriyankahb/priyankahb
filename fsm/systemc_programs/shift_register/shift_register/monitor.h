#include <systemc.h>

SC_MODULE(monitor){
sc_in<bool>clk;
sc_in<bool>rst,in;
sc_in<sc_uint<4>>output;

void mon()
{
cout<<"reset: "<<rst.read()<<" Input: "<<in.read()<<" Output: "<<output.read()<<endl;
}
SC_CTOR(monitor){
SC_METHOD(mon);
sensitive <<clk.pos()<<rst<<in;
}
};
