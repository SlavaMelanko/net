#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ZmqPublisher.h>

#include <memory>

class ZmqPublisherTest : public testing::Test
{
protected:
  void SetUp() { publisher = std::make_unique<net::ZmqPublisher>(context, "127.0.0.1", 5555); }
  void TearDown() {}

  zmq::context_t context{ 1 };
  std::unique_ptr<net::IPublisher> publisher;
};

TEST_F(ZmqPublisherTest, InitializeInstance)
{
  EXPECT_TRUE(context);
}

TEST_F(ZmqPublisherTest, PublishMessageToSpecificTopic)
{
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(publisher->sendOut("notification", "hey there"));
}

TEST_F(ZmqPublisherTest, BroadcastMessage)
{
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(publisher->broadcast("hey there"));
}
