#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include "Encoder.h"
#include "Initiator.h"


using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;
/*

SC_MODULE(Initiator) {
    simple_initiator_socket<Initiator> initiator_socket;

    SC_CTOR(Initiator) : initiator_socket("initiator_socket") {
        SC_THREAD(sendData);
    }

    void sendData() {
        // Create a CustomPayload object
        CustomPayload customPayload;
        customPayload.data = 42;
        customPayload.address = 0x100;
        
        sc_time delay = SC_ZERO_TIME;
        // Create a tlm_generic_payload object
        tlm_generic_payload payload;
        payload.set_data_ptr(reinterpret_cast<unsigned char*>(&customPayload));
        payload.set_address(0); // Set address if necessary
        payload.set_data_length(sizeof(CustomPayload));
        payload.set_streaming_width(sizeof(CustomPayload));
        payload.set_byte_enable_ptr(0); // Optional
        payload.set_byte_enable_length(0); // Optional
        payload.set_dmi_allowed(false); // Mandatory initial value
        payload.set_response_status(TLM_INCOMPLETE_RESPONSE); // Mandatory initial value

        // Send the payload using blocking transport
        initiator_socket->b_transport(payload, delay);

        // Check the response
        if (payload.get_response_status() == TLM_OK_RESPONSE) {
            cout << "Initiator sent data: Address = " << customPayload.address << ", Data = " << customPayload.data << endl;
        } else {
            cout << "Initiator failed to send data" << endl;
        }
    }
};

SC_MODULE(Encoder) {
    simple_target_socket<Encoder> target_socket;

    SC_CTOR(Encoder) : target_socket("target_socket") {
        target_socket.register_b_transport(this, &Encoder::processData);
    }

    void processData(tlm_generic_payload& payload, sc_time& delay) {
        // Retrieve data from the payload
        CustomPayload* customPayload = reinterpret_cast<CustomPayload*>(payload.get_data_ptr());

        cout << "Encoder received data: Address = " << customPayload->address << ", Data = " << customPayload->data << endl;

        // Set response status
        payload.set_response_status(TLM_OK_RESPONSE);
    }
};

*/
int sc_main(int argc, char* argv[]) {
    Initiator initiator("initiator");
    Encoder encoder("encoder");

    initiator.initiator_socket.bind(encoder.target_socket);

    sc_start();

    return 0;
}

