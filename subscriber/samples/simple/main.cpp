#include "ZmqSubscriber.h"

#include <Log.h>

#include <memory>

int main()
{
  utils::InitLogging();

  try {
    zmq::context_t context{ 1 };
    std::unique_ptr<net::Subscriber> subscriber =
      std::make_unique<net::ZmqSubscriber>(context, "127.0.0.1", 5555);
    subscriber->subscribeToAllTopics();

    while (true) {
      subscriber->waitForNotification();
    }
  } catch (const std::exception& e) {
    ERROR(e.what());
  }

  return 0;
}

#if 0
int main()
{
    try {
        InitLogging();

        srandom((unsigned)time(NULL));

        zmq::context_t context{1};
        zmq::socket_t worker{context, ZMQ_DEALER};
#if (defined(WIN32))
        const int id = 10;
        s_set_id(worker, static_cast<intptr_t>(id));
#else
        s_set_id(worker); // set a printable identity
#endif
        INFO("Connecting to localhost:5566");
        worker.connect("tcp://localhost:5566");

        while (true) {
            INFO("Tell the broker we're ready for work");
            INFO("Sending delimiter");
            s_sendmore(worker, std::string{""});
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
#endif
