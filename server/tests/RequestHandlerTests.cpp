#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <HeartbeatRequestHandler.h>

TEST(HeartbeatRequestHandlerTest, CheckResponse)
{
  net::HeartbeatRequestHandler heartbeat;
  const auto response = heartbeat.process({});
  EXPECT_EQ(response.getString("srv_v"), "0.0.1");
  EXPECT_EQ(response.getString("zmq_v"), "4.3.2");
}