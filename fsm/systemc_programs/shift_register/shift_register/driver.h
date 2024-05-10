#include <systemc.h>

SC_MODULE(driver){
sc_in<bool>clk;
sc_out<bool>rst,in;

void input(){
	wait(5,SC_NS);
	rst.write(true);
	
	wait(5,SC_NS);
	rst.write(false);
	
	wait(5,SC_NS);
	in.write(true);
	
	wait(5,SC_NS);
	in.write(true);
	
	wait(5,SC_NS);
	in.write(false);
	
	wait(5,SC_NS);
	in.write(true);
	
	wait(5,SC_NS);
	in.write(true);
	
	wait(5,SC_NS);
	rst.write(false);
	
	
}
SC_CTOR(driver){
	SC_THREAD(input);
}
};
