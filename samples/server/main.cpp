#include <ZmqServer.h>

#include <Log.h>

#include <zmq.hpp>

#include <CLI/CLI.hpp>

int main(int argc, char* argv[])
{
  utils::Log::initialize();

  try {
    CLI::App app{ "Server sample" };

    uint32_t port{ 0 };
    app.add_option("-p,--port", port)->check(CLI::PositiveNumber);

    CLI11_PARSE(app, argc, argv);

    zmq::context_t context{ 1 };
    net::ServerUnPtr server = std::make_unique<net::ZmqServer>(context, "127.0.0.1", port);
    while (true) {
      server->run();
    }
  } catch (const std::exception& e) {
    utils::Log::error(e.what());
  }

  return 0;
}
