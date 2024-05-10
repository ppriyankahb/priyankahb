#include<systemc.h>
#include"logic.h"
#include"monitor.h"
#include"driver.h"

int sc_main(int argc,char* agrv[])
{

sc_signal<bool>rst;
sc_signal<sc_uint<4>>count;
sc_clock clk("clk",2,SC_NS,0.5);

logic log("log");
log.rst(rst);
log.count(count);
//log.q(q);
log.clk(clk);

monitor mon("mon");
mon.clk(clk);
mon.rst(rst);
mon.count(count);
//mon.qb(qb);

driver drive("drive");
drive.rst(rst);
drive.clk(clk);

sc_trace_file *Tf;
Tf=sc_create_vcd_trace_file("traces");
sc_trace(Tf,clk,"clk");
sc_trace(Tf,rst,"rst");
sc_trace(Tf,count,"count");
//sc_trace(Tf,qb,"qb");

sc_start(60,SC_NS);
sc_close_vcd_trace_file(Tf);

return 0;

}

