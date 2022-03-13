#include <iostream>

#include "../include/mr_network.hpp"

// dumps raw memory in hex byte and printable split format
static void dump(const unsigned char *data_buffer, const unsigned int length) {
    unsigned char byte;
    unsigned int i, j;
    for(i=0; i < length; i++) {
        byte = data_buffer[i];
        printf("%02x ", data_buffer[i]);  // display byte in hex
        if(((i%16)==15) || (i==length-1)) {
            for(j=0; j < 15-(i%16); j++)
                printf("   ");
            printf("| ");
            for(j=(i-(i%16)); j <= i; j++) {  // display printable bytes from line
                byte = data_buffer[j];
                if((byte > 31) && (byte < 127)) // outside printable char range
                    printf("%c", byte);
                else
                    printf(".");
            }
            printf("\n"); // end of the dump line (each line 16 bytes)
        } // end if
    } // end for
}


void TCPserver::up()

{
    std::vector<std::string> list;
    while (1) {
        zmq::message_t id, msg;
        backend->recv(id, zmq::recv_flags::none);
        std::cout << "connection from " << id.str() << std::endl;
        while (backend->recv(msg)) {
            // strip off the routing id.
            if (msg.str() == id.str()) {
                continue;
            }
            dump((unsigned char const*)msg.data(), msg.size());
        }
    }
}
