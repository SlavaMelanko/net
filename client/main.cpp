#include <zhelpers.hpp>

int main()
{
    try {
        zmq::context_t context{1};
        zmq::socket_t subscriber(context, ZMQ_SUB);
        subscriber.connect("tcp://127.0.0.1:5555");
        subscriber.setsockopt(ZMQ_SUBSCRIBE, "A", 1);

        while (true) {
            std::clog << "Receiving address..." << std::endl;
            const auto address = s_recv(subscriber);
            std::clog << "Receiving content..." << std::endl;
            const auto content = s_recv(subscriber);
            std::clog << "[" << address << "] " << content << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
