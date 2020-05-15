#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ZmqSubscriber.h>
using namespace net;

#include <memory>

class SubscriberTest : public testing::Test
{
protected:
  void SetUp() { subscriber = std::make_unique<ZmqSubscriber>(context, 5555); }
  void TearDown() {}

  zmq::context_t context{ 1 };
  std::unique_ptr<Subscriber> subscriber;
};

TEST_F(SubscriberTest, InitializeInstance)
{
  EXPECT_TRUE(context);
}

TEST_F(SubscriberTest, SubscribeToTopic)
{
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(subscriber->subscribeTo("notification"));
}

TEST_F(SubscriberTest, SubscribeToAllTopic)
{
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(subscriber->subscribeToAllTopics());
}
