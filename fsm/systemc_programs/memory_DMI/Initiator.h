#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

// Initiator module
SC_MODULE(Initiator) {
    tlm_utils::simple_initiator_socket<Initiator> socket;

    SC_CTOR(Initiator) : socket("socket") {
        SC_THREAD(sendData);
    }

    void sendData() {
        CustomPayload customPayload;
        customPayload.data = 42;
        customPayload.address = 0x100;

        tlm_generic_payload payload;
        payload.set_data_ptr(reinterpret_cast<unsigned char*>(&customPayload));
        payload.set_address(0); // Set address if necessary
        payload.set_data_length(sizeof(CustomPayload));
        payload.set_streaming_width(sizeof(CustomPayload));
        payload.set_byte_enable_ptr(0); // Optional
        payload.set_byte_enable_length(0); // Optional
        payload.set_dmi_allowed(true); // Enable DMI

        sc_time delay = SC_ZERO_TIME;
        tlm_command cmd = TLM_WRITE_COMMAND;

        cout << "Initiator: Sending WRITE request. Address = " << customPayload.address << ", Data = " << customPayload.data << endl;
        socket->b_transport(payload, delay); // Blocking call

        // Assuming you want to read the data back
        cmd = TLM_READ_COMMAND;
        cout << "Initiator: Sending READ request. Address = " << customPayload.address << endl;
        socket->b_transport(payload, delay); // Blocking call

        cout << "Initiator: Received READ response. Data = " << customPayload.data << endl;
    }

};

