#include<systemc.h>

SC_MODULE(logic)
{
sc_in<bool>d,clk;
sc_out<bool>q,qb;

void function(){
if(clk.posedge()){
q.write(d.read());
qb.write(!d.read());
}

}

SC_CTOR(logic){
SC_METHOD(function);
sensitive <<clk.pos();

}

};
