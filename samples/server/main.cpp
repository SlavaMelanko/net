#include "ZmqServer.h"

#include <Log.h>

#include <zmq.hpp>

int main()
{
  utils::InitLogging();

  try {
    zmq::context_t context{ 1 };
    net::ServerUnPtr server = std::make_unique<net::ZmqServer>(context, "127.0.0.1", 5555);
    while (true) {
      server->run();
    }
  } catch (const std::exception& e) {
    ERROR(e.what());
  }

  return 0;
}
