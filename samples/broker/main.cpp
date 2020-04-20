#include <Broker.h>

#include <Log.h>

#include <zhelpers.hpp>

#include <CLI/CLI.hpp>

int main(int argc, char* argv[])
{
  utils::Log::initialize();

  CLI::App app{ "Broker sample" };

  uint32_t frontendPort{ 0 };
  app.add_option("-f,--frontend-port", frontendPort)->check(CLI::PositiveNumber);
  uint32_t backendPort{ 0 };
  app.add_option("-b,--backend-port", backendPort)->check(CLI::PositiveNumber);

  CLI11_PARSE(app, argc, argv);

  zmq::context_t context{ 1 };

  const auto frontendAddress = fmt::format("tcp://*:{}", frontendPort);
  utils::Log::info("Binding frontend to {}", frontendAddress);
  zmq::socket_t frontend{ context, ZMQ_ROUTER };
  frontend.bind(frontendAddress);

  const auto backendAddress = fmt::format("tcp://*:{}", backendPort);
  utils::Log::info("Binding backend to {}", backendAddress);
  zmq::socket_t backend{ context, ZMQ_DEALER };
  backend.bind(backendAddress);

  // clang-format off
  std::array<zmq::pollitem_t, 2> items = {{
    { static_cast<void*>(frontend), 0, ZMQ_POLLIN, 0 },
    { static_cast<void*>(backend), 0, ZMQ_POLLIN, 0 }
  }};
  // clang-format on

  while (true) {
    zmq::message_t message;
    int more; // multipart detection

    zmq::poll(items.data(), items.size());

    if (items[0].revents & ZMQ_POLLIN) {
      while (true) {
        const auto retval = frontend.recv(message);
#if 0
        if (retval)
            utils::Log::info("front {} {}", retval.value(), message.to_string());
#endif
        size_t moreSize = sizeof(more);
        frontend.getsockopt(ZMQ_RCVMORE, &more, &moreSize);
        const auto flag = more ? zmq::send_flags::sndmore : zmq::send_flags::none;
        backend.send(message, flag);

        if (!more)
          break;
      }
    }
    if (items[1].revents & ZMQ_POLLIN) {
      while (true) {
        const auto retval = backend.recv(message);
#if 0
        if (retval)
            utils::Log::info("back {} {}", retval.value(), message.to_string());
#endif
        size_t moreSize = sizeof(more);
        backend.getsockopt(ZMQ_RCVMORE, &more, &moreSize);
        const auto flag = more ? zmq::send_flags::sndmore : zmq::send_flags::none;
        frontend.send(message, flag);

        if (!more)
          break;
      }
    }
  }

  return 0;
}
