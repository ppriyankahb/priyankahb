#include<systemc.h>

SC_MODULE(logic)
{
sc_in<bool>t,clk;
sc_out<bool>q,qb;
bool currentState;
void function(){
if(clk.posedge()){
if(t.read()==1)
{
currentState = !currentState;
}
q.write(currentState);
qb.write(!currentState);
}

}

SC_CTOR(logic){
SC_METHOD(function);
sensitive <<clk.pos();

}

};
