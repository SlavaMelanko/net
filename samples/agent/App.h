#pragma once

#include <zmq.hpp>

class Connection;

class App
{
public:
  App(int argc, char* argv[]);
  ~App() noexcept;

  void run();

private:
  void initializeLogging();
  bool parseArguments(int argc, char* argv[]);
  void initializeConnections();

  std::string m_id;
  uint32_t m_servicePort;
  uint32_t m_publisherPort;

  zmq::context_t m_context{ 1 };
  std::unique_ptr<Connection> m_payloadConnection;
  std::unique_ptr<Connection> m_notificationConnection;
};
