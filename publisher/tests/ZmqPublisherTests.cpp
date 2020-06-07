#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ZmqPublisher.h>
using namespace net;

#include <memory>

class ZmqPublisher : public testing::Test
{
protected:
  void SetUp() { publisher = std::make_unique<ZmqPublisher>(context, "127.0.0.1", 5555); }
  void TearDown() {}

  zmq::context_t context{ 1 };
  PublisherUnPtr publisher;
};

TEST_F(ZmqPublisher, InitializeInstance)
{
  EXPECT_TRUE(context);
}

TEST_F(ZmqPublisher, SubscribeToTopic)
{
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(publisher->sendOut("notification", "hey there"));
}

TEST_F(ZmqPublisher, SubscribeToAllTopic)
{
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(publisher->broadcast("hey there"));
}
