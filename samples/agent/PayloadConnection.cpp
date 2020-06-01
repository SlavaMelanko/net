#include "PayloadConnection.h"

#include <Log.h>
#include <ZmqClient.h>

PayloadConnection::PayloadConnection(zmq::context_t& context,
                                     const std::string& id,
                                     const uint32_t port)
  : m_client{ std::make_unique<net::ZmqClient>(context, net::MakeConnectionSettings(id, port)) }
{}

PayloadConnection::~PayloadConnection() noexcept
{
  if (m_thread.joinable())
    m_thread.join();
}

void PayloadConnection::run()
{
  m_thread = std::thread{ &PayloadConnection::process, this };
}

void PayloadConnection::process()
{
  try {
    while (true) {
      std::this_thread::sleep_for(std::chrono::seconds{ 1 });
      const auto response = m_client->send("request");
    }
  } catch (const std::exception& e) {
    net::Log::error(e.what());
  }
}
