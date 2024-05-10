#include<systemc.h>
#include"logic.h"
#include"monitor.h"
#include"driver.h"

int sc_main(int argc,char* agrv[])
{

sc_signal<bool>enable;
sc_signal<sc_uint<2>>in;
sc_signal<sc_uint<4>>out;

logic log("log");
log.enable(enable);
log.in(in);
log.out(out);

monitor mon("mon");
mon.enable(enable);
mon.in(in);
mon.out(out);

driver drive("drive");
drive.enable(enable);
drive.in(in);

sc_trace_file *Tf;
Tf=sc_create_vcd_trace_file("traces");
sc_trace(Tf,enable,"enable");
sc_trace(Tf,in,"in");
sc_trace(Tf,out,"out");

sc_start(60,SC_NS);
sc_close_vcd_trace_file(Tf);

return 0;

}

