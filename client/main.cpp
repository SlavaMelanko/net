#include <zhelpers.hpp>

#include <Log.h>
#if 0
int main()
{
    try {
        zmq::context_t context{1};
        zmq::socket_t subscriber{context, ZMQ_SUB};
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
#endif
int main()
{
    try {
        InitLogging();

        srandom((unsigned)time(NULL));

        zmq::context_t context{1};
        zmq::socket_t worker{context, ZMQ_DEALER};
#if (defined (WIN32))
        s_set_id(worker, (intptr_t)args);
#else
        s_set_id(worker); // set a printable identity
#endif
        INFO("Connecting to localhost:5566");
        worker.connect("tcp://localhost:5566");

        while (true) {
            INFO("Tell the broker we're ready for work");
            INFO("Sending delimiter");
            s_sendmore(worker, "");
            INFO("Sending message");
            s_send(worker, std::string{"Hey server"});
            INFO("Get workload from broker, until finished");
            const std::string delimiter = s_recv(worker);
            INFO("Envelope delimiter: \"{}\"", delimiter);
            const std::string workload = s_recv(worker);
            INFO("Workload: {}", workload);

            s_sleep(within(500) + 1);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
