#include<systemc.h>

SC_MODULE(monitor)
{
sc_in<bool>t,q,qb,clk;
void function(){
cout<< " Inputs are " << t <<" "<< "Output are "<<q <<qb <<endl;
}

SC_CTOR(monitor){
SC_METHOD(function);
sensitive << clk.pos();

}

};
