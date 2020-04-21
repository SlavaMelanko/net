#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ZmqWorker.h>
using namespace net;

TEST(WorkerTest, InitializeInstance)
{
  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(std::make_unique<ZmqWorker>(context, 5555));
}
