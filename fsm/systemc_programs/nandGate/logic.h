#include<systemc.h>

SC_MODULE(logic)
{
sc_in<bool>a,b;
sc_out<bool>out;

void function(){
out.write(!(a.read() && b.read()));
}

SC_CTOR(logic){
SC_METHOD(function);
sensitive << a << b;

}

};
