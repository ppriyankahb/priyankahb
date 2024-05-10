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
SC_MODULE(Memory) {
    tlm_utils::simple_target_socket<Memory> socket;

    int memory_array[256]; // Example memory array

    Memory(sc_module_name name) : sc_module(name) {
        socket.register_b_transport(this, &Memory::b_transport);
        socket.register_get_direct_mem_ptr(this, &Memory::get_direct_mem_ptr);
        // Initialize memory array
        for (int i = 0; i < 256; ++i) {
            memory_array[i] = i;
        }
    }

    void b_transport(tlm_generic_payload& payload, sc_time& delay) {
        CustomPayload* customPayload = reinterpret_cast<CustomPayload*>(payload.get_data_ptr());

        if (payload.get_command() == TLM_WRITE_COMMAND) {
            // Write data to memory
            cout << "Memory: Received WRITE request. Address = " << customPayload->address << ", Data = " << customPayload->data << endl;
            memory_array[customPayload->address] = customPayload->data;
        } else if (payload.get_command() == TLM_READ_COMMAND) {
            // Read data from memory
            cout << "Memory: Received READ request. Address = " << customPayload->address << endl;
            customPayload->data = memory_array[customPayload->address];
        }

        // Response is always OK
        payload.set_response_status(TLM_OK_RESPONSE);
    }

    bool get_direct_mem_ptr(tlm_generic_payload& payload, tlm_dmi& dmi_data) {
        dmi_data.set_dmi_ptr(reinterpret_cast<unsigned char*>(memory_array));
        dmi_data.set_start_address(0);
        dmi_data.set_end_address(255);
        dmi_data.set_read_latency(sc_time(1, SC_NS)); // Set read latency
        dmi_data.set_write_latency(sc_time(1, SC_NS)); // Set write latency
        dmi_data.allow_read_write();

        return true;
    }
};

