#include<systemc.h>

SC_MODULE(monitor)
{
sc_in<bool>s,r,q,qb,clk;

void function(){
cout<< " Inputs are " << s << r<<" "<<"clock " <<clk<<" "<< "Output "<<q<<qb<<endl;
}

SC_CTOR(monitor){
SC_METHOD(function);
sensitive << clk.pos();

}

};
