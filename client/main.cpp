#include <zmq_addon.hpp>

#include <iostream>

int main()
{
    zmq::context_t context;
    zmq::socket_t socket(context, zmq::socket_type::req);
    socket.connect("tcp://localhost:5555");

    for (int i = 0; i != 10; ++i) {
        std::cout << "Sending Hello " << i << "...\n";
        socket.send("Hello", 5);
        char buffer[10];
        socket.recv(buffer, 10);
        std::cout << "Received World " << i << '\n';
    }

    return 0;
}
