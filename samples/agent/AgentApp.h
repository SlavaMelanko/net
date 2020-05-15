#pragma once

#include <zmq.hpp>

class NotificationConnection;
class PayloadConnection;

class AgentApp
{
public:
  AgentApp(int argc, char* argv[]);
  ~AgentApp() noexcept;

  void run();

private:
  void initializeLogging();
  bool parseArguments(int argc, char* argv[]);
  void initializeConnections();

  std::string m_id;
  uint32_t m_servicePort;
  uint32_t m_publisherPort;

  zmq::context_t m_context{ 1 };
  std::unique_ptr<PayloadConnection> m_payloadConnection;
  std::unique_ptr<NotificationConnection> m_notificationConnection;
};
