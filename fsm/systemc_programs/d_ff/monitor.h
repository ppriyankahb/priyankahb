#include<systemc.h>

SC_MODULE(monitor)
{
sc_in<bool>d,q,qb,clk;
void function(){
cout<< " Inputs are " << d <<" "<< "Output are "<<q <<qb <<endl;
}

SC_CTOR(monitor){
SC_METHOD(function);
sensitive << clk.pos();

}

};
