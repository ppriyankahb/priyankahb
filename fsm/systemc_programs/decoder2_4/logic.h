#include<systemc.h>

SC_MODULE(logic)
{
sc_in<bool>enable;
sc_in<sc_uint<2>>in;
sc_out<sc_uint<4>>out;

void function(){
sc_uint<4>value =0;
if(enable){
value[in.read()]=1;
out.write(value);
}
else
out.write(0);
}

SC_CTOR(logic){
SC_METHOD(function);
sensitive << enable<<in;

}

};
