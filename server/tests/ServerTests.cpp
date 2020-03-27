#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Server.h>
using namespace net;

TEST(ServerTest, InitializeInstanceWithDefaultSettings)
{
  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(Server{ context };);
}
