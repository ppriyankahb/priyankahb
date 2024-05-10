#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

// Define custom payload type
struct CustomPayload : public tlm_base_protocol_types {
    int data;
    int address;
};

// Memory module with DMI support
SC_MODULE(Memory) {
    simple_target_socket<Memory> target_socket;

    int memory_array[256]; // Example memory array
    tlm_dmi dmi_data; // DMI data structure

    SC_CTOR(Memory) : target_socket("target_socket") {
        target_socket.register_b_transport(this, &Memory::processTransaction);
        target_socket.register_get_direct_mem_ptr(this, &Memory::getDirectMemPtr);
    }

    virtual void processTransaction(CustomPayload& payload, tlm_command& cmd, sc_time& delay) {
        if (cmd == TLM_WRITE_COMMAND) {
            memory_array[payload.address] = payload.data;
            cout << "Memory wrote data: Address = " << payload.address << ", Data = " << payload.data << endl;
        } else if (cmd == TLM_READ_COMMAND) {
            payload.data = memory_array[payload.address];
            cout << "Memory read data: Address = " << payload.address << ", Data = " << payload.data << endl;
        }
    }

    virtual bool getDirectMemPtr(CustomPayload& payload, tlm_dmi& dmi_data) {
        dmi_data.allow_read_write();
        dmi_data.set_start_address(0);
        dmi_data.set_end_address(sizeof(memory_array) - 1);
        dmi_data.set_dmi_ptr(reinterpret_cast<unsigned char*>(memory_array));
        dmi_data.set_read_latency(delay);
        dmi_data.set_write_latency(delay);
        return true;
    }
};

// Initiator module
SC_MODULE(Initiator) {
    simple_initiator_socket<Initiator> initiator_socket;

    SC_CTOR(Initiator) : initiator_socket("initiator_socket") {
        SC_THREAD(sendData);
    }

    void sendData() {
        CustomPayload payload;
        payload.data = 101; // Example data
        payload.address = 0x200; // Example address

        tlm_command cmd = TLM_WRITE_COMMAND;

        sc_time delay = SC_ZERO_TIME;
        initiator_socket->b_transport(payload, cmd, delay);

        cout << "Initiator sent data: Address = " << payload.address << ", Data = " << payload.data << endl;
    }
};

int sc_main(int argc, char* argv[]) {
    Initiator initiator("initiator");
    Memory memory("memory");

    initiator.initiator_socket.bind(memory.target_socket);

    sc_start();

    return 0;
}

