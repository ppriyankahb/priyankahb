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



