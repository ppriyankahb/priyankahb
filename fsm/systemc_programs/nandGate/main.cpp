#include<systemc.h>
#include"logic.h"
#include"monitor.h"
#include"driver.h"

int sc_main(int argc,char* agrv[])
{

sc_signal<bool>a,b,out;

logic log("log");
log.a(a);
log.b(b);
log.out(out);

monitor mon("mon");
mon.a(a);
mon.b(b);
mon.out(out);

driver drive("drive");
drive.a(a);
drive.b(b);

sc_trace_file *Tf;
Tf=sc_create_vcd_trace_file("traces");
sc_trace(Tf,a,"a");
sc_trace(Tf,b,"b");
sc_trace(Tf,out,"out");

sc_start(60,SC_NS);
sc_close_vcd_trace_file(Tf);

return 0;
}
