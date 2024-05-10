#include<systemc.h>
#include"logic.h"
#include"monitor.h"
#include"driver.h"

int sc_main(int argc,char* agrv[])
{

sc_signal<bool>s,r,q,qb;
sc_clock clk("clk",2,SC_NS,0.5);

logic log("log");
log.s(s);
log.r(r);
log.q(q);
log.qb(qb);
log.clk(clk);

monitor mon("mon");
mon.s(s);
mon.r(r);
mon.q(q);
mon.qb(qb);
mon.clk(clk);

driver drive("drive");
drive.s(s);
drive.r(r);
drive.clk(clk);

sc_trace_file *Tf;
Tf=sc_create_vcd_trace_file("traces");
sc_trace(Tf,s,"s");
sc_trace(Tf,r,"r");
sc_trace(Tf,q,"q");
sc_trace(Tf,qb,"qb");
sc_trace(Tf,clk,"clk");

sc_start(60,SC_NS);
sc_close_vcd_trace_file(Tf);

return 0;
}
