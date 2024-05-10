#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

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
        
        tlm_dmi dmi_data;
        if(initiator_socket->get_direct_mem_ptr(payload,dmi_data)){
        
        cout<< "Initiator using DMI for address = " <<customPayload.address<<endl;
        initiator_socket->b_transport(payload, delay);
        
        }else
        {
        initiator_socket->b_transport(payload,delay);
        }
        
        cout <<"Initiator sent data : Address = "<<customPayload.address<<",Data = "<<customPayload.data<<endl;
        }
};
/*SC_MODULE(Initiator) {
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
};*/




