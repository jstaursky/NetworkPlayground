#ifndef MR_NETWORK_H
#define MR_NETWORK_H

#include <memory>
#include <vector>
#include <viface/viface.hpp>
#include <tins/tins.h>
#include <zmq.hpp>


class VirtIface : public viface::VIface
{
public:
    virtual ~VirtIface() {}
    VirtIface(std::string name, std::string ip)
        : viface::VIface::VIface(name, true)
    {
        this->setIPv4(ip);
    }
    using viface::VIface::send;
    void send(Tins::PDU* packet) const {
        if (packet == NULL) {
            puts("Attempt to send null packet.");
            exit(EXIT_FAILURE);
        }
        std::vector<uint8_t> raw = packet->serialize();
        this->send(raw);
    }

        using viface::VIface::receive;
        Tins::PDU* receive_tins() {
            std::vector<uint8_t> raw = this->receive();
            if (raw.size() == 0) {
                return NULL;
            }
            return new Tins::RawPDU(&raw[0], raw.size());
        }

};


class NetworkServer
{
public:
    NetworkServer() {}
    virtual ~NetworkServer() {}
};

class TCPserver : public NetworkServer
{
    zmq::context_t context;
    std::unique_ptr<zmq::socket_t> backend;
public:
    TCPserver(unsigned port) : backend(new zmq::socket_t(context, zmq::socket_type::stream)) {
        backend->set(zmq::sockopt::stream_notify, true); // Not sure I believe this does anything.
        backend->bind("tcp://*:" + std::to_string(port));
    }
    virtual ~TCPserver() {}

    void up();
};

#endif /* MR_NETWORK_H */
