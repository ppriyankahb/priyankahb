#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

// Define a custom payload
struct CustomPayload : public tlm_generic_payload {
    int data;
    int address;
};

// Grey code to binary conversion function
int greyToBinary(int num) {
    int mask;
    for (mask = num >> 1; mask != 0; mask = mask >> 1)
        num = num ^ mask;
    return num;
}

// BCD to binary conversion function
int bcdToBinary(int num) {
    return ((num / 16) * 10) + (num % 16);
}

// Memory module
SC_MODULE(Memory) {
    tlm_utils::simple_target_socket<Memory> socket;
    int prevCmd;

    Memory(sc_module_name name) : sc_module(name), prevCmd(-1) {
        socket.register_b_transport(this, &Memory::b_transport);
    }

    void b_transport(tlm_generic_payload& payload, sc_time& delay) {
        CustomPayload* customPayload = reinterpret_cast<CustomPayload*>(payload.get_data_ptr());
        
        if (payload.get_command() == TLM_WRITE_COMMAND) {
            // Store the value of the previous command for debugging
            prevCmd = customPayload->data;

            // Convert Grey code to BCD
            int greyCode = customPayload->data;
            int binary = greyToBinary(greyCode);
            int bcd = bcdToBinary(binary);

            cout << "Memory: Received WRITE request. Grey Code = " << greyCode << ", BCD = " << bcd << endl;
        } else if (payload.get_command() == TLM_READ_COMMAND) {
            cout << "Memory: Received READ request. Previous Command = " << prevCmd << endl;
        }

        // Response is always OK
        payload.set_response_status(TLM_OK_RESPONSE);
    }
};

// Initiator module
SC_MODULE(Initiator) {
    tlm_utils::simple_initiator_socket<Initiator> socket;

    SC_CTOR(Initiator) : socket("socket") {
        SC_THREAD(sendData);
    }

    void sendData() {
        CustomPayload customPayload;
        customPayload.data = 7; // Example 4-bit Grey code
        customPayload.address = 0x100;

        tlm_generic_payload payload;
        payload.set_data_ptr(reinterpret_cast<unsigned char*>(&customPayload));
        payload.set_address(0); // Set address if necessary
        payload.set_data_length(sizeof(CustomPayload));
        payload.set_streaming_width(sizeof(CustomPayload));
        payload.set_byte_enable_ptr(0); // Optional
        payload.set_byte_enable_length(0); // Optional
        payload.set_dmi_allowed(false); // Mandatory initial value
        payload.set_response_status(TLM_INCOMPLETE_RESPONSE); // Mandatory initial value

        sc_time delay = SC_ZERO_TIME;
        tlm_command cmd = TLM_WRITE_COMMAND;

        cout << "Initiator: Sending WRITE request. Grey Code = " << customPayload.data << endl;
        socket->b_transport(payload, delay); // Blocking call

        // Assuming you want to read the data back
        cmd = TLM_READ_COMMAND;
        cout << "Initiator: Sending READ request for previous command." << endl;
        socket->b_transport(payload, delay); // Blocking call

        cout << "Initiator: Received READ response. Previous Command = " << customPayload.data << endl;
    }
};

int sc_main(int argc, char* argv[]) {
    Memory memory("memory");
    Initiator initiator("initiator");

    initiator.socket.bind(memory.socket);

    sc_start();

    return 0;
}

