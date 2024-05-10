#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include "Memory.h"
#include "Initiator.h"


using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

int sc_main(int argc, char* argv[]) {
    Initiator initiator("initiator");
    Memory encoder("encoder");

    initiator.socket.bind(encoder.socket);

    sc_start();

    return 0;
}

