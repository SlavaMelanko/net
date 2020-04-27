#include "ZmqServer.h"

#include <Log.h>

#include <zhelpers.hpp>

#include <signal.h>

namespace net {

namespace {

static int s_interrupted = 0;

void HandleSignal(int signal)
{
  s_interrupted = 1;
}

void SetUpCatchSignals()
{
#ifdef _WIN32
  signal(SIGINT, HandleSignal);
  signal(SIGTERM, HandleSignal);
#else
  struct sigaction action;
  action.sa_handler = HandleSignal;
  action.sa_flags = 0;
  sigemptyset(&action.sa_mask);
  sigaction(SIGINT, &action, NULL);
  sigaction(SIGTERM, &action, NULL);
#endif
}

} // namespace

ZmqServer::ZmqServer(zmq::context_t& context, std::string_view host, const uint16_t port)
  : m_socket{ context, ZMQ_ROUTER }
{
  const std::string address = fmt::format("tcp://{}:{}", host, port);
  Log::info("Binding to {}", address);
  m_socket.bind(address);
  Log::info("OK, listening for incoming connection requests");
}

void ZmqServer::run()
{
  SetUpCatchSignals();

  while (true) {
    try {
      handle();
    } catch (zmq::error_t& e) {
      Log::error(e.what());
    }
    if (s_interrupted) {
      break;
    }
  }
}

void ZmqServer::handle()
{
  const std::string identity = s_recv(m_socket);
  const std::string delimiter = s_recv(m_socket);
  const std::string message = s_recv(m_socket);

  Log::info("Client #{}: \"{}\"", identity, message);

  s_sendmore(m_socket, identity);
  s_sendmore(m_socket, delimiter);
  s_send(m_socket, message);
}

} // namespace net
