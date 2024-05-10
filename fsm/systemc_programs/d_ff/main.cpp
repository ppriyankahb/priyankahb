#include<systemc.h>
#include"logic.h"
#include"monitor.h"
#include"driver.h"

int sc_main(int argc,char* agrv[])
{

sc_signal<bool>d,q,qb;
sc_clock clk("clk",2,SC_NS,0.5);

logic log("log");
log.d(d);
log.qb(qb);
log.q(q);
log.clk(clk);

monitor mon("mon");
mon.clk(clk);
mon.d(d);
mon.q(q);
mon.qb(qb);

driver drive("drive");
drive.d(d);
drive.clk(clk);

sc_trace_file *Tf;
Tf=sc_create_vcd_trace_file("traces");
sc_trace(Tf,clk,"clk");
sc_trace(Tf,d,"d");
sc_trace(Tf,q,"q");
sc_trace(Tf,qb,"qb");

sc_start(60,SC_NS);
sc_close_vcd_trace_file(Tf);

return 0;

}

