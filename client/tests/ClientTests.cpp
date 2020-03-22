#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Client.h>

TEST(ClientTest, InitializeInstance)
{
  net::Settings settings;
  settings.id = "test-1";
  settings.host = "127.0.0.1";
  settings.port = 5555;
  EXPECT_EQ(settings.id.value(), "test-1");
  EXPECT_EQ(settings.host, "127.0.0.1");
  EXPECT_EQ(settings.port, 5555);

  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  net::Client client{ context, settings };
  EXPECT_TRUE(true);
}

TEST(ClientTest, InitializeInstanceWithDefaultSettings)
{
  net::Settings settings;
  EXPECT_FALSE(settings.id.has_value());
  EXPECT_EQ(settings.host, "localhost");
  EXPECT_EQ(settings.port, 5555);

  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  net::Client client{ context, settings };
  EXPECT_TRUE(true);
}
