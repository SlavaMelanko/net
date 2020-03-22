#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ZmqSubscriber.h>
using namespace net;

#include <memory>

TEST(Subscriber, InitializeInstance)
{
  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  std::unique_ptr<Subscriber> subscriber =
    std::make_unique<ZmqSubscriber>(context, "localhost", 5555);
  EXPECT_TRUE(true);
}

TEST(Subscriber, SubscribeToTopic)
{
  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  std::unique_ptr<Subscriber> subscriber =
    std::make_unique<ZmqSubscriber>(context, "localhost", 5555);
  subscriber->subscribeTo("notification");
  EXPECT_TRUE(true);
}

TEST(Subscriber, SubscribeToAllTopic)
{
  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  std::unique_ptr<Subscriber> subscriber =
    std::make_unique<ZmqSubscriber>(context, "localhost", 5555);
  subscriber->subscribeToAllTopics();
  EXPECT_TRUE(true);
}
