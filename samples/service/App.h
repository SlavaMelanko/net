#pragma once

#include <zmq.hpp>

class Publisher;
class Server;

class App
{
public:
  App(int argc, char* argv[]);
  ~App();

  void run();

private:
  void initializeLogging();
  bool parseArguments(int argc, char* argv[]);
  void bind();

  uint32_t m_serverPort;
  uint32_t m_publisherPort;

  zmq::context_t m_context{ 1 };
  std::unique_ptr<Server> m_server;
  std::unique_ptr<Publisher> m_publisher;
};
