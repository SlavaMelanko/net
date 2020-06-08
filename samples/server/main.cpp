#include <Log.h>
#include <ZmqServer.h>

#include <zmq.hpp>

#include <CLI/CLI.hpp>

int main(int argc, char* argv[])
{
  net::Log::initialize();

  try {
    CLI::App app{ "Server sample" };

    std::string host{ "127.0.0.1" };
    app.add_option("-o,--host", host)->check(CLI::ValidIPV4);
    uint32_t port{ 0 };
    app.add_option("-p,--port", port)->check(CLI::PositiveNumber);

    CLI11_PARSE(app, argc, argv);

    zmq::context_t context{ 1 };
    std::unique_ptr<net::IServer> server = std::make_unique<net::ZmqServer>(context, host, port);
    server->run();
  } catch (const std::exception& e) {
    net::Log::error(e.what());
  }

  return 0;
}
