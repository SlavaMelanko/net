#include "TcpServer.h"

#include <Log.h>

int main()
{
    InitLogging();

    try {
        net::TcpServer{}.run();
    } catch (const std::exception &e) {
        ERROR(e.what());
    }

    return 0;
}
#if 0
int main()
{
    try {
        InitLogging();

        zmq::context_t context{1};
        zmq::socket_t broker{context, ZMQ_ROUTER};

        INFO("Binding to 127.0.0.1:5566");
        broker.bind("tcp://127.0.0.1:5566");

        while (true) {
            const std::string identity = s_recv(broker);
            INFO("Identity: {}", identity);
            const std::string delimiter = s_recv(broker);
            INFO("Envelope delimiter: \"{}\"", delimiter);
            const std::string message = s_recv(broker);
            INFO("Worker message: {}", message);

            INFO("Sending identity");
            s_sendmore(broker, identity);
            INFO("Sending delimiter");
            s_sendmore(broker, std::string{""});
            INFO("Respond");
            s_send(broker, std::string{"Hi client"});
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
#endif
