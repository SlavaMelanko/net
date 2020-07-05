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

  using Type = net::RequestHandlerFactory;

  Type requestHandlerFactory;
};

TEST_F(RequestHandlerFactoryTest, CheckTypeTraits)
{
  // Primary type categories.
  EXPECT_TRUE(std::is_class_v<Type>);

  // Type properties.
  EXPECT_FALSE(std::is_trivially_copyable_v<Type>);
  EXPECT_FALSE(std::is_abstract_v<Type>);
  EXPECT_TRUE(std::is_polymorphic_v<Type>);
  EXPECT_FALSE(std::is_final_v<Type>);

  // Supported operations.
  EXPECT_TRUE(std::is_default_constructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_default_constructible_v<Type>);
  EXPECT_TRUE(std::is_nothrow_default_constructible_v<Type>);

  EXPECT_TRUE(std::is_copy_constructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_copy_constructible_v<Type>);
  EXPECT_TRUE(std::is_nothrow_copy_constructible_v<Type>);

  EXPECT_TRUE(std::is_move_constructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_move_constructible_v<Type>);
  EXPECT_TRUE(std::is_nothrow_move_constructible_v<Type>);

  EXPECT_TRUE(std::is_copy_assignable_v<Type>);
  EXPECT_FALSE(std::is_trivially_copy_assignable_v<Type>);
  EXPECT_TRUE(std::is_nothrow_copy_assignable_v<Type>);

  EXPECT_TRUE(std::is_move_assignable_v<Type>);
  EXPECT_FALSE(std::is_trivially_move_assignable_v<Type>);
  EXPECT_TRUE(std::is_nothrow_move_assignable_v<Type>);

  EXPECT_TRUE(std::is_destructible_v<Type>);
  EXPECT_TRUE(std::is_nothrow_destructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_destructible_v<Type>);

  EXPECT_TRUE(std::has_virtual_destructor_v<Type>);
}

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
