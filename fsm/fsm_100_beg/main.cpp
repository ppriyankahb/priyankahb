#include <systemc.h>

SC_MODULE(Monitor) {
    sc_in<bool> clk;
    sc_in<int> data;
    sc_in<bool> reset;

    void monitor_process() {
        while (true) {
            wait(); // Wait for the next clock edge
            if (reset.read()) {
                cout << "Reset detected" << endl;
            } else {
                cout << "Data: " << data.read() << endl;
            }
        }
    }

    SC_CTOR(Monitor) {
        SC_THREAD(monitor_process);
        sensitive << clk.pos();
    }
};

SC_MODULE(Driver) {
    sc_out<bool> reset;
    sc_out<int> data;
    sc_in<bool> clk;

    void driver_process() {
        // Reset
        reset.write(true);
        wait(); // Wait for one clock cycle
        reset.write(false);

        // Send data
        data.write(1); // Example input
        wait(); // Wait for one clock cycle

        data.write(0); // Example input
        wait(); // Wait for one clock cycle

        data.write(0); // Example input
        wait(); // Wait for one clock cycle

        data.write(1); // Example input
        wait(); // Wait for one clock cycle

        // End simulation
        sc_stop();
    }

    SC_CTOR(Driver) {
        SC_THREAD(driver_process);
        sensitive << clk.pos();
    }
};

SC_MODULE(FSM) {
    sc_in<int> data;
    sc_out<bool> output1;
    sc_in<bool> clk;

    enum State { START, S1, S2, OUTPUT };

    State state;

    void fsm_process() {
        state = START;
        int num = 0;
        while (true) {
            wait(); // Wait for the next clock edge
            switch (state) {
                case START:
                    if (data.read() == 1) {
                        state = S1;
                    }
                    break;
                case S1:
                    if (data.read() == 0) {
                        state = S2;
                    } else if (data.read() == 1) {
                        state = S1;
                    } else {
                        state = START;
                    }
                    break;
                case S2:
                    if (data.read() == 0) {
                        state = OUTPUT;
                    } else if (data.read() == 1) {
                        state = S1;
                    } else {
                        state = START;
                    }
                    break;
                case OUTPUT:
                    output1.write(true);
                    break;
            }
        }
    }

    SC_CTOR(FSM) {
        SC_THREAD(fsm_process);
        sensitive << clk.pos();
    }
};

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 1, SC_NS); // Clock period of 1 ns
    sc_signal<bool> reset;
    sc_signal<int> data;
    sc_signal<bool> output1;

    Monitor monitor("monitor");
    monitor.clk(clk);
    monitor.data(data);
    monitor.reset(reset);

    Driver driver("driver");
    driver.clk(clk);
    driver.data(data);
    driver.reset(reset);

    FSM fsm("fsm");
    fsm.clk(clk);
    fsm.data(data);
    fsm.output1(output1);

    sc_start(); // Start simulation

    return 0;
}

