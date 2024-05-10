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

