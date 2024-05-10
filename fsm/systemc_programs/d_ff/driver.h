#include<systemc.h>

SC_MODULE(driver)
{

sc_out<bool>d;
sc_in<bool>clk;

void drive(){

wait(5,SC_NS);
d.write(0);
wait(5,SC_NS);
d.write(1);
wait(5,SC_NS);
d.write(0);
wait(5,SC_NS);
d.write(1);
wait(5,SC_NS);

sc_stop();
}

SC_CTOR(driver){
SC_THREAD(drive);
sensitive<<clk.pos();
}

};
