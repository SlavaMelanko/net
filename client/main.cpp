#include <zmq_addon.hpp>

#include <iostream>

int main()
{
    zmq::context_t context;
    zmq::socket_t socket(context, zmq::socket_type::req);
    socket.connect("tcp://127.0.0.1:5555");

    for (int i = 0; i != 10; ++i) {
        std::cout << i << " Sending Hello...";
        socket.send("Hello", 5);
        zmq::message_t message;
        socket.recv(message);
        std::cout << " Received " << message.to_string() << '\n';
    }

    return 0;
}
