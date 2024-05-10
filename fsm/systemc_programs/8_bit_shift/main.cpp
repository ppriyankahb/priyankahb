#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include <bitset>
using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

SC_MODULE(ShiftRegister) {
    tlm_utils::simple_target_socket<ShiftRegister> socket;

    sc_uint<8> register_data;

    SC_CTOR(ShiftRegister) : socket("socket"), register_data(0) {
        socket.register_b_transport(this, &ShiftRegister::b_transport);
    }

    void b_transport(tlm_generic_payload& payload, sc_time& delay) {
        tlm_command cmd = payload.get_command();
        sc_dt::uint64 addr = payload.get_address();

        if (cmd == TLM_WRITE_COMMAND) {
            // Write to the shift register
            int data = *(reinterpret_cast<int*>(payload.get_data_ptr()));
            register_data = data;
            payload.set_response_status(TLM_OK_RESPONSE);
        } else if (cmd == TLM_READ_COMMAND) {
            // Read from the shift register
            payload.set_response_status(TLM_OK_RESPONSE);
            *(reinterpret_cast<int*>(payload.get_data_ptr())) = register_data.to_uint();
            // Shift the register data
            register_data = register_data << 1;
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

        // Write data to the shift register
        int data = 0b11001100; // Example data
        payload.set_address(0);
        payload.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
        payload.set_data_length(sizeof(int));
        payload.set_command(TLM_WRITE_COMMAND);
        socket->b_transport(payload, delay);
        cout << "Initiator: Wrote data = " << std::bitset<8>(data) << endl;

        // Read data from the shift register
        int read_data = 0;
        payload.set_address(0);
        payload.set_data_ptr(reinterpret_cast<unsigned char*>(&read_data));
        payload.set_data_length(sizeof(int));
        payload.set_command(TLM_READ_COMMAND);
        socket->b_transport(payload, delay);
        cout << "Initiator: Read data = " << std::bitset<8>(read_data) << endl;
    }
};

int sc_main(int argc, char* argv[]) {
    ShiftRegister shift_register("shift_register");
    Initiator initiator("initiator");

    initiator.socket.bind(shift_register.socket);

    sc_start();

    return 0;
}

