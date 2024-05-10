#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

// Define a simple payload struct
struct CustomPayload {
    int data;
    int address;
};

// Initiator module
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

    // Prepare phase and delay
    tlm_phase phase = BEGIN_REQ;
    sc_time delay = SC_ZERO_TIME;

    // Send the payload
    tlm_sync_enum sync_enum = initiator_socket->nb_transport_fw(payload, phase, delay);

    // Check the response
    if (sync_enum == TLM_ACCEPTED) {
        cout << "Initiator sent data: Address = " << customPayload.address << ", Data = " << customPayload.data << endl;
    } else {
        cout << "Initiator failed to send data" << endl;
    }
}

};

// Decoder module
SC_MODULE(Decoder) {
    simple_target_socket<Decoder> target_socket;

    SC_CTOR(Decoder) : target_socket("target_socket") {
        target_socket.register_nb_transport_fw(this, &Decoder::processData);
    }

    // Process incoming payload
    tlm_sync_enum processData(tlm_generic_payload& payload, tlm_phase& phase, sc_time& delay) {
        if (phase == BEGIN_REQ) {
            CustomPayload* customPayload = reinterpret_cast<CustomPayload*>(payload.get_data_ptr());
            cout << "Decoder received data: Address = " << customPayload->address << ", Data = " << customPayload->data << endl;
            return TLM_ACCEPTED;
        }
        return TLM_COMPLETED;
    }
};

int sc_main(int argc, char* argv[]) {
    Initiator initiator("initiator");
    Decoder decoder("decoder");

    initiator.initiator_socket.bind(decoder.target_socket);

    sc_start();

    return 0;
}

