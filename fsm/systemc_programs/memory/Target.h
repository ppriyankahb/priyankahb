#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

struct CustomPayload : public tlm_base_protocol_types {
	int data;
	int address;
};


// Decoder module
SC_MODULE(Target) {
    simple_target_socket<Target> target_socket;

    SC_CTOR(Target) : target_socket("target_socket") {
        target_socket.register_b_transport(this, &Target::processData);
    }

    void processData(tlm_generic_payload& payload, sc_time& delay) {
        // Retrieve data from the payload
        CustomPayload* customPayload = reinterpret_cast<CustomPayload*>(payload.get_data_ptr());

        if (payload.get_command() == TLM_WRITE_COMMAND) {
            // Write data to memory
            cout << "Memory: Received WRITE request. Address = " << customPayload->address << ", Data = " << customPayload->data << endl;
        } else if (payload.get_command() == TLM_READ_COMMAND) {
            // Read data from memory
            cout << "Memory: Received READ request. Address = " << customPayload->address << endl;
            // Assuming memory returns some data
            customPayload->data = 42;
        }
        // Set response status
        payload.set_response_status(TLM_OK_RESPONSE);
    }
};


/*SC_MODULE(Encoder) {
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
};*/

