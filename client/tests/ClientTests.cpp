#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ZmqClient.h>
using namespace net;

TEST(ClientTest, InitializeInstance)
{
  ConnectionSettings connectionSettings;
  connectionSettings.id = "test-1";
  connectionSettings.host = "127.0.0.1";
  connectionSettings.port = 5555;
  EXPECT_EQ(connectionSettings.id.value(), "test-1");
  EXPECT_EQ(connectionSettings.host, "127.0.0.1");
  EXPECT_EQ(connectionSettings.port, 5555);

  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  EXPECT_NO_THROW([&]() {
    ClientUnPtr client = std::make_unique<ZmqClient>(context, connectionSettings);
    EXPECT_TRUE(client);
  });
}

TEST(ClientTest, InitializeInstanceWithDefaultSettings)
{
  ConnectionSettings connectionSettings;
  connectionSettings.port = 5555;
  EXPECT_FALSE(connectionSettings.id.has_value());
  EXPECT_EQ(connectionSettings.host, "localhost");
  EXPECT_EQ(connectionSettings.port, 5555);

  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  EXPECT_NO_THROW([&]() {
    ClientUnPtr client = std::make_unique<ZmqClient>(context, connectionSettings);
    EXPECT_TRUE(client);
  });
}
