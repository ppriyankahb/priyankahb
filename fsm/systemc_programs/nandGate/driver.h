#include<systemc.h>

SC_MODULE(driver)
{

sc_out<bool>a,b;

void drive(){

wait(5,SC_NS);
a.write(0);
b.write(0);
wait(5,SC_NS);
b.write(1);
wait(5,SC_NS);
a.write(1);
wait(5,SC_NS);
b.write(0);
wait(5,SC_NS);
sc_stop();
}

SC_CTOR(driver){
SC_THREAD(drive);
}

};
