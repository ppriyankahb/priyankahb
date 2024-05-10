#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

// Convert 3-bit binary code to Grey code
unsigned int binary_to_gray(unsigned int num) {
    return num ^ (num >> 1);
}

SC_MODULE(BinaryToGrayConverter) {
    tlm_utils::simple_target_socket<BinaryToGrayConverter> socket;

    SC_CTOR(BinaryToGrayConverter) : socket("socket") {
        socket.register_b_transport(this, &BinaryToGrayConverter::b_transport);
    }

    void b_transport(tlm_generic_payload& payload, sc_time& delay) {
        tlm_command cmd = payload.get_command();
        sc_dt::uint64 addr = payload.get_address();

        if (cmd == TLM_WRITE_COMMAND) {
            int data = *(reinterpret_cast<int*>(payload.get_data_ptr()));
            int gray_code = binary_to_gray(data);
            cout << "Converter: Converted " << data << " (binary) to " << gray_code << " (Gray code)" << endl;
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

        // Write binary code to the converter
        int binary_code = 0b101; // Example binary code
        payload.set_address(0);
        payload.set_data_ptr(reinterpret_cast<unsigned char*>(&binary_code));
        payload.set_data_length(sizeof(int));
        payload.set_command(TLM_WRITE_COMMAND);
        socket->b_transport(payload, delay);

        // Read from the converter (not supported)
        payload.set_address(0);
        payload.set_data_ptr(reinterpret_cast<unsigned char*>(&binary_code));
        payload.set_data_length(sizeof(int));
        payload.set_command(TLM_READ_COMMAND);
        socket->b_transport(payload, delay);
    }
};

int sc_main(int argc, char* argv[]) {
    BinaryToGrayConverter converter("converter");
    Initiator initiator("initiator");

    initiator.socket.bind(converter.socket);

    sc_start();

    return 0;
}

