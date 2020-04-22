#include <Log.h>
#include <ZmqPublisher.h>

#include <zmq.hpp>

#include <thread>

int main()
{
  utils::Log::initialize();

  try {
    zmq::context_t context{ 1 };
    std::unique_ptr<net::Publisher> publisher{ std::make_unique<net::ZmqPublisher>(
      context, "127.0.0.1", 5555) };
    int i = 0;
    while (true) {
      const std::string message{ "Message #" + std::to_string(++i) };
      publisher->broadcast(message);
      std::this_thread::sleep_for(std::chrono::seconds{ 1 });
    }
  } catch (const std::exception& e) {
    utils::Log::error(e.what());
  }

  return 0;
}
