#include<systemc.h>
#include"logic.h"
#include"monitor.h"
#include"driver.h"

int sc_main(int argc,char* agrv[])
{

sc_signal<bool>a,b,sum,co;

logic log("log");
log.a(a);
log.b(b);
log.sum(sum);
log.co(co);

monitor mon("mon");
mon.a(a);
mon.b(b);
mon.sum(sum);
mon.co(co);

driver drive("drive");
drive.a(a);
drive.b(b);

sc_trace_file *Tf;
Tf=sc_create_vcd_trace_file("traces");
sc_trace(Tf,a,"a");
sc_trace(Tf,b,"b");
sc_trace(Tf,sum,"sum");
sc_trace(Tf,co,"co");

sc_start(60,SC_NS);
sc_close_vcd_trace_file(Tf);

return 0;
}
