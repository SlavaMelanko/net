#include "TcpServer.h"

#include "ZmqPublisher.h"

#include <thread>

namespace net {

TcpServer::TcpServer()
    : m_context{1}
    , m_publisher{std::make_unique<ZmqPublisher>(m_context, "127.0.0.1", 5555)}
{
}

void TcpServer::run()
{
    int i = 0;
    while (true) {
        const std::string message{"Message #" + std::to_string(++i)};
        m_publisher->broadcast(message);
        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
}

} // namespace net
