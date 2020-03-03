#include <zhelpers.hpp>

#include <thread>
#if 0
int main()
{
    try {
        zmq::context_t context{1};
        zmq::socket_t publisher{context, ZMQ_PUB};
        publisher.bind("tcp://127.0.0.1:5555");

        int i = 0;
        while (true) {
            const std::string message{"Message #" + std::to_string(++i)};

            std::clog << "Sending \"" << message << "\" to A..." << std::endl;
            s_sendmore(publisher, "A");
            s_send(publisher, message);

            std::clog << "Sending \"" << message << "\" to B..." << std::endl;
            s_sendmore(publisher, "B");
            s_send(publisher, message);

            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
#endif
int main()
{
    try {
        zmq::context_t context{1};
        zmq::socket_t broker{context, ZMQ_ROUTER};
        broker.bind("tcp://127.0.0.1:5566");

        while (true) {
            const std::string identity = s_recv(broker);
            std::clog << "Identity: " << identity << std::endl;
            const std::string delimiter = s_recv(broker);
            std::clog << "Envelope delimiter: \"" << delimiter << "\"\n";
            const std::string workerMessage = s_recv(broker);
            std::clog << "Worker message: " << workerMessage << std::endl;
            s_sendmore(broker, identity);
            s_sendmore(broker, "");
            s_send(broker, std::string{"Hi client"});
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
