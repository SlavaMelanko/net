#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ZmqBroker.h>
using namespace net;

TEST(BrokerTest, InitializeInstance)
{
  constexpr uint32_t frontendPort = 5559;
  constexpr uint32_t backendPort = 5560;
  EXPECT_NO_THROW(std::make_unique<ZmqBroker>(frontendPort, backendPort));
}
