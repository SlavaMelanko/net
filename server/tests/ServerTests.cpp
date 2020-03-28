#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ZmqServer.h>
using namespace net;

TEST(ServerTest, InitializeInstance)
{
  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(std::make_unique<ZmqServer>(context, "127.0.0.1", 5555));
}
