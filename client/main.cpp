#include <zhelpers.hpp>

int main()
{
    try {
        zmq::context_t context{1};
        zmq::socket_t subscriber(context, ZMQ_SUB);
        subscriber.connect("tcp://127.0.0.1:5555");
        subscriber.setsockopt(ZMQ_SUBSCRIBE, "A", 1);

        while (true) {
            std::clog << "Receiving topic..." << std::endl;
            const auto topic = s_recv(subscriber);
            std::clog << "Receiving content..." << std::endl;
            const auto content = s_recv(subscriber);
            std::clog << topic << ": " << content << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
