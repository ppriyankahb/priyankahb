#include <systemc.h>

#include "shift.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc,char *argv[])
{
sc_signal<bool>in,rst;
sc_signal<sc_uint<4>>output;
sc_clock clk("clk",5,SC_NS,0.5);

shift logic("shift");
driver drive("driver");
monitor mon("monitor");

logic.rst(rst);
logic.in(in);
logic.clk(clk);
logic.output(output);

drive.in(in);
drive.rst(rst);
drive.clk(clk);

mon.rst(rst);
mon.in(in);
mon.clk(clk);
mon.output(output);

sc_start(60,SC_NS);
return 0;

}
