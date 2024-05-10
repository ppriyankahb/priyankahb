#include<systemc.h>

SC_MODULE(driver)
{

sc_out<bool>t;
sc_in<bool>clk;

void drive(){

wait(5,SC_NS);
t.write(0);
wait(5,SC_NS);
t.write(1);
wait(5,SC_NS);
t.write(0);
wait(5,SC_NS);
t.write(1);
wait(5,SC_NS);

sc_stop();
}

SC_CTOR(driver){
SC_THREAD(drive);
sensitive<<clk.pos();
}

};
