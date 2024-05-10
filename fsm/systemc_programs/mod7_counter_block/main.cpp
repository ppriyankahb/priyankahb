#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

SC_MODULE(Mod7Counter) {
    tlm_utils::simple_target_socket<Mod7Counter> socket;

    int counter;

    SC_CTOR(Mod7Counter) : socket("socket"), counter(0) {
        socket.register_b_transport(this, &Mod7Counter::b_transport);
    }

    void b_transport(tlm_generic_payload& payload, sc_time& delay) {
        tlm_command cmd = payload.get_command();
        sc_dt::uint64 addr = payload.get_address();

        if (cmd == TLM_READ_COMMAND) {
            // Read the current counter value
            payload.set_response_status(TLM_OK_RESPONSE);
            *(reinterpret_cast<int*>(payload.get_data_ptr())) = counter;
        } else if (cmd == TLM_WRITE_COMMAND) {
            // Write to the counter
            int data = *(reinterpret_cast<int*>(payload.get_data_ptr()));
            counter = (counter + data) % 7;
            payload.set_response_status(TLM_OK_RESPONSE);
        }
    }
};

SC_MODULE(Initiator) {
    tlm_utils::simple_initiator_socket<Initiator> socket;

    SC_CTOR(Initiator) : socket("socket") {
        SC_THREAD(run);
    }

    void run() {
        tlm_generic_payload payload;
        sc_time delay = SC_ZERO_TIME;

        // Write to the counter
        int data = 9;
        payload.set_address(0);
        payload.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
        payload.set_data_length(sizeof(int));
        payload.set_command(TLM_WRITE_COMMAND);
        socket->b_transport(payload, delay);
        cout << "Initiator: Wrote data = " << data << endl;

        // Read from the counter
        payload.set_address(0);
        payload.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
        payload.set_data_length(sizeof(int));
        payload.set_command(TLM_READ_COMMAND);
        socket->b_transport(payload, delay);
        cout << "Initiator: Read data = " << data << endl;
    }
};

int sc_main(int argc, char* argv[]) {
    Mod7Counter counter("counter");
    Initiator initiator("initiator");

    initiator.socket.bind(counter.socket);

    sc_start();

    return 0;
}

