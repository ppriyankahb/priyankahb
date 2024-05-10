#include<systemc.h>

SC_MODULE(logic)
{
sc_in<bool>a,b;
sc_out<bool>sum,co;

void function(){
sum.write(a.read() ^ b.read());
co.write(a.read() && b.read());
}

SC_CTOR(logic){
SC_METHOD(function);
sensitive << a << b;

}

};
