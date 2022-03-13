#include "../deps/CLI11.hpp"
#include "../include/mr_network.hpp"

int main(int argc, char** argv)

{
    CLI::App app{"App description"};

    std::string ip = "192.168.20.20";
    app.add_option("--ip,--ipaddress", ip, "An ip address to assign.");
    unsigned port = 7890;
    app.add_option("-p,--port", ip, "Set port number.");


    CLI11_PARSE(app, argc, argv);

    VirtIface iface("viface%d", ip);
    iface.up();
    while (true) {
        Tins::PDU* received = iface.receive_tins();
        auto s = received->serialize();
        for (auto b : s)
            std::cout << b << std::endl;
    }

    // TCPserver server(port);
    // server.up();

    return 0;
}

