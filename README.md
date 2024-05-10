# priyankahb

export SYSTEMC_HOME=/usr/local/systemc-2.3.3

g++ -I/usr/local/systemc-2.3.3/include -L/usr/local/systemc-2.3.3/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o hello main.cpp -lsystemc -lm

g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o hello hello.cpp -lsystemc -lm

./hello
gtkwave traces.vcd

