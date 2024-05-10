#include<systemc.h>

SC_MODULE(logic)
{
sc_in<bool>a,b,cin;
sc_out<bool>sum,co;

void function(){
sum.write(a.read() ^ b.read()^cin.read());
co.write((a.read() && b.read())||(b.read() && cin.read())||(cin.read() && a.read()));
}

SC_CTOR(logic){
SC_METHOD(function);
sensitive << a << b<<cin;

}

};
