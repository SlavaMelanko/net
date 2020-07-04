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
  EXPECT_THROW(
    {
      try {
        requestHandlerFactory.create("none");
      } catch (const std::invalid_argument& e) {
        EXPECT_STREQ("Unhandled action", e.what());
        throw;
      } catch (...) {
        EXPECT_TRUE(false);
      }
    },
    std::invalid_argument);
}

TEST_F(RequestHandlerFactoryTest, CreateHeartbeatHandler)
{
  const auto heartbeatRequestHandler = requestHandlerFactory.create("heartbeat");
  EXPECT_TRUE(heartbeatRequestHandler);

  using HandlerType = std::remove_reference_t<decltype(*heartbeatRequestHandler)>;

  EXPECT_TRUE(std::has_virtual_destructor_v<HandlerType>);
  EXPECT_TRUE((std::is_base_of_v<net::IRequestHandler, HandlerType>));
  EXPECT_TRUE((std::is_same_v<net::IRequestHandler, HandlerType>));
  EXPECT_TRUE(dynamic_cast<net::HeartbeatRequestHandler*>(heartbeatRequestHandler.get()) !=
              nullptr);
}
