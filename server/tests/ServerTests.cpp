#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <RequestHandlerFactory.h>
#include <ZmqServer.h>

TEST(ServerTest, InitializeInstance)
{
  auto requestHandlerFactory = std::make_unique<net::RequestHandlerFactory>();
  EXPECT_TRUE(requestHandlerFactory);
  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(
    std::make_unique<net::ZmqServer>(std::move(requestHandlerFactory), context, "127.0.0.1", 5555));
}
