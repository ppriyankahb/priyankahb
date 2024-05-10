#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

// Convert 4-bit Grey code to Binary-Coded Decimal (BCD)
unsigned int gray_to_bcd(unsigned int num) {
    return ((num >> 3) & 1) * 8 + ((num >> 2) & 1) * 4 + ((num >> 1) & 1) * 2 + (num & 1);
}

SC_MODULE(GrayToBcdConverter) {
    tlm_utils::simple_target_socket<GrayToBcdConverter> socket;

    SC_CTOR(GrayToBcdConverter) : socket("socket") {
        socket.register_b_transport(this, &GrayToBcdConverter::b_transport);
    }

    void b_transport(tlm_generic_payload& payload, sc_time& delay) {
        tlm_command cmd = payload.get_command();
        sc_dt::uint64 addr = payload.get_address();

        if (cmd == TLM_WRITE_COMMAND) {
            int data = *(reinterpret_cast<int*>(payload.get_data_ptr()));
            int bcd_code = gray_to_bcd(data);
            cout << "Converter: Converted " << data << " (Gray code) to " << bcd_code << " (BCD)" << endl;
            payload.set_response_status(TLM_OK_RESPONSE);
        } else if (cmd == TLM_READ_COMMAND) {
            cout << "Converter: Read operation not supported" << endl;
            payload.set_response_status(TLM_COMMAND_ERROR_RESPONSE);
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

        // Write Grey code to the converter
        int gray_code = 0b0101; // Example 4-bit Grey code
        payload.set_address(0);
        payload.set_data_ptr(reinterpret_cast<unsigned char*>(&gray_code));
        payload.set_data_length(sizeof(int));
        payload.set_command(TLM_WRITE_COMMAND);
        socket->b_transport(payload, delay);

        // Read from the converter (not supported)
        payload.set_address(0);
        payload.set_data_ptr(reinterpret_cast<unsigned char*>(&gray_code));
        payload.set_data_length(sizeof(int));
        payload.set_command(TLM_READ_COMMAND);
        socket->b_transport(payload, delay);
    }
};

int sc_main(int argc, char* argv[]) {
    GrayToBcdConverter converter("converter");
    Initiator initiator("initiator");

    initiator.socket.bind(converter.socket);

    sc_start();

    return 0;
}

