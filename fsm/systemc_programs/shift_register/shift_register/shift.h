#include <systemc.h>

SC_MODULE(shift){
sc_in<bool>rst;
sc_in<bool>clk;
sc_in<bool>in;
sc_out<sc_uint<4>>output;
sc_uint<4>temp;

void logic()
{
	if(rst.read())
	{
	temp=0;
	output.write(temp);
	}
	else{
	temp=(temp<<1)|in;
	output.write(temp);
	}
	}
SC_CTOR(shift){
	SC_METHOD(logic);
	sensitive<< clk.pos()<<rst<<in;
}


};
