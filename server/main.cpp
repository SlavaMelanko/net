#include <zhelpers.hpp>

#include <thread>

int main()
{
    try {
        zmq::context_t context{1};
        zmq::socket_t publisher(context, ZMQ_PUB);
        publisher.bind("tcp://127.0.0.1:5555");

        while (true) {
            std::clog << "Sending message to A..." << std::endl;
            s_sendmore(publisher, "A");
            s_send(publisher, std::string{"Message #1"});
            std::clog << "Sending message to B..." << std::endl;
            s_sendmore(publisher, "B");
            s_send(publisher, std::string{"Message #2"});

            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
