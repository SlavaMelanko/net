#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Publisher.h>

#include <memory>

class PublisherTest : public testing::Test
{
protected:
  void SetUp()
  {
    publisher = std::make_unique<net::Publisher>(context, "127.0.0.1", 5555);
    publisher->run();
  }
  void TearDown() { publisher->stop(); }

  zmq::context_t context{ 1 };
  std::unique_ptr<net::Publisher> publisher;
};

TEST_F(PublisherTest, InitializeInstance)
{
  EXPECT_TRUE(context);
  EXPECT_TRUE(publisher != nullptr);
}

TEST_F(PublisherTest, PublishMessageToSpecificTopic)
{
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(publisher->push("hey there", "greeting"));
}

TEST_F(PublisherTest, BroadcastMessage)
{
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(publisher->push("hey there"));
}
