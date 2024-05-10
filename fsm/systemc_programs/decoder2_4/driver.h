#include<systemc.h>

SC_MODULE(driver)
{

sc_out<bool>enable;
sc_out<sc_uint<2>>in;

void drive(){

wait(5,SC_NS);
enable.write(0);
in.write(0);
wait(5,SC_NS);
enable.write(1);
in.write(0);
wait(5,SC_NS);
in.write(1);
wait(5,SC_NS);
in.write(2);
wait(5,SC_NS);
in.write(3);
wait(5,SC_NS);
sc_stop();
}

SC_CTOR(driver){
SC_THREAD(drive);
}

};
