#include "Server.h"

#include <Log.h>

#include <zmq.hpp>

int main()
{
  utils::InitLogging();

  try {
    zmq::context_t context{ 1 };
    std::unique_ptr<net::Server> server{ std::make_unique<net::Server>(context) };
    while (true) {
      server->run();
    }
  } catch (const std::exception& e) {
    ERROR(e.what());
  }

  return 0;
}
