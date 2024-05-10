#include<systemc.h>

SC_MODULE(logic)
{
sc_in<bool>rst,clk,input;
sc_out<sc_uint<4>>registers;
sc_uint<4> registersvalue;

void function(){

if(rst.read()){
registersvalue=0;
}
else if(clk.posedge()){
registersvalue =(registersvalue<<1) | input.read();
}
registers.write(registersvalue);
}
SC_CTOR(logic){
SC_METHOD(function);
sensitive <<clk.pos();

}

};
