#include<systemc.h>

SC_MODULE(logic)
{
sc_in<bool>rst,clk;
sc_out<sc_uint<4>>count;
sc_uint<4> counter;

void function(){
if(clk.posedge()){
if(rst.read()){
counter=0;
count.write(counter);
}
else{
counter = (counter+1)%8;
count.write(counter);
}

}

}
SC_CTOR(logic){
SC_METHOD(function);
sensitive <<clk.pos();

}

};
