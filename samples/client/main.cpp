#include "Client.h"

#include <Log.h>

#include <zmq.hpp>

#include <thread>

int main()
{
  utils::InitLogging();

  try {
    zmq::context_t context{ 1 };
    std::unique_ptr<net::Client> publisher{ std::make_unique<net::Client>(context) };
    int i = 0;
    while (true) {
      const auto message{ "Message #" + std::to_string(++i) };
      const auto response = publisher->send(message);
      INFO("Server responded: \"{}\"", response);
      std::this_thread::sleep_for(std::chrono::seconds{ 1 });
    }
  } catch (const std::exception& e) {
    ERROR(e.what());
  }

  return 0;
}
