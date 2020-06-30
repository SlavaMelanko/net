#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <HeartbeatRequestHandler.h>
#include <RequestHandlerFactory.h>

#include <type_traits>

class RequestHandlerFactoryTest : public testing::Test
{
protected:
  void SetUp() {}
  void TearDown() {}

  net::RequestHandlerFactory requestHandlerFactory;
};

TEST_F(RequestHandlerFactoryTest, CreateNull)
{
  const auto nullRequestHandler = requestHandlerFactory.create("none");
  EXPECT_FALSE(nullRequestHandler);
}

TEST_F(RequestHandlerFactoryTest, CreateHeartbeatHandler)
{
  const auto heartbeatRequestHandler = requestHandlerFactory.create("heartbeat");
  EXPECT_TRUE(heartbeatRequestHandler);

  using HandlerType = std::remove_reference_t<decltype(*heartbeatRequestHandler)>;

  EXPECT_TRUE(std::has_virtual_destructor_v<HandlerType>);
  const auto isIRequestHandlerBaseOfHeartbeat =
    std::is_base_of_v<net::IRequestHandler, HandlerType>;
  EXPECT_TRUE(isIRequestHandlerBaseOfHeartbeat);
  const auto isHeartbeatTheSameAsIRequestHandler =
    std::is_same_v<net::IRequestHandler, HandlerType>;
  EXPECT_TRUE(isHeartbeatTheSameAsIRequestHandler);
  EXPECT_TRUE(dynamic_cast<net::HeartbeatRequestHandler*>(heartbeatRequestHandler.get()) !=
              nullptr);
}
