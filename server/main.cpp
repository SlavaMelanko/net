#include <zmq.hpp>

#include <iostream>

int main()
{
    try {
        zmq::context_t context;
        zmq::socket_t socket{context, zmq::socket_type::rep};
        if (!socket.handle()) {
            std::cout << "Unable to create socket\n";
            return 1;
        }
        socket.bind("tcp://127.0.0.1:5555");

        while (true) {
            zmq::message_t message;
            socket.recv(message);
            std::cout << "Received: " << message.str() << '\n';

            socket.send(zmq::str_buffer("World"), zmq::send_flags::dontwait);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
