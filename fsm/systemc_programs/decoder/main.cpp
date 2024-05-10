#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include "Decoder.h"
#include "Initiator.h"

using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

// Define a simple payload struct
/*struct CustomPayload {
    int data;
    int address;
};
*/
int sc_main(int argc, char* argv[]) {
    Initiator initiator("initiator");
    Decoder decoder("decoder");

    initiator.initiator_socket.bind(decoder.target_socket);

    sc_start();

    return 0;
}

