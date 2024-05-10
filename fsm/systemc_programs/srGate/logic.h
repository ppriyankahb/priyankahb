#include<systemc.h>

SC_MODULE(logic)
{
sc_in<bool>s,r,clk;
sc_out<bool>q,qb;

bool currentState;
void function(){
if(s.read()==0 && r.read()==0){
            q=q;
            qb=qb;
        }
        else if(s.read()==0 && r.read()==1){
           q.write(0);
           qb.write(1);
        }
        else if(s.read()==1 && r.read()==0){
           q.write(1);
           qb.write(0);
        }
        else if(s.read()==1 && r.read()==1){
           q.write(0);
           qb.write(0);
        }
    }

SC_CTOR(logic){
SC_METHOD(function);
sensitive <<clk.pos();

}

};
