#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <HeartbeatRequestHandler.h>

#include <type_traits>

TEST(IRequestHandlerTest, CheckTypeTraits)
{
  using Type = net::IRequestHandler;

  // Primary type categories.
  EXPECT_TRUE(std::is_class_v<Type>);

  // Type properties.
  EXPECT_FALSE(std::is_trivially_copyable_v<Type>);
  EXPECT_TRUE(std::is_abstract_v<Type>);
  EXPECT_TRUE(std::is_polymorphic_v<Type>);

  // Supported operations.
  EXPECT_FALSE(std::is_default_constructible_v<Type>);

  EXPECT_FALSE(std::is_copy_constructible_v<Type>);
  EXPECT_FALSE(std::is_copy_assignable_v<Type>);

  EXPECT_FALSE(std::is_move_constructible_v<Type>);
  EXPECT_TRUE(std::is_move_assignable_v<Type>);

  EXPECT_TRUE(std::is_destructible_v<Type>);
  EXPECT_TRUE(std::is_nothrow_destructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_destructible_v<Type>);

  EXPECT_TRUE(std::has_virtual_destructor_v<Type>);
}

TEST(HeartbeatRequestHandlerTest, CheckTypeTraits)
{
  using Type = net::HeartbeatRequestHandler;

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

  EXPECT_FALSE(std::is_copy_constructible_v<Type>);
  EXPECT_FALSE(std::is_copy_assignable_v<Type>);

  EXPECT_TRUE(std::is_move_constructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_move_constructible_v<Type>);
  EXPECT_TRUE(std::is_nothrow_move_constructible_v<Type>);

  EXPECT_TRUE(std::is_move_assignable_v<Type>);
  EXPECT_FALSE(std::is_trivially_move_assignable_v<Type>);
  EXPECT_TRUE(std::is_nothrow_move_assignable_v<Type>);

  EXPECT_TRUE(std::is_destructible_v<Type>);
  EXPECT_TRUE(std::is_nothrow_destructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_destructible_v<Type>);

  EXPECT_TRUE(std::has_virtual_destructor_v<Type>);

  // Type relationships.
  EXPECT_TRUE((std::is_base_of_v<net::IRequestHandler, Type>));
}

TEST(HeartbeatRequestHandlerTest, CheckResponse)
{
  net::HeartbeatRequestHandler heartbeat;
  const auto response = heartbeat.process({});
  EXPECT_EQ(response.getString("srv_v"), "0.0.1");
  EXPECT_EQ(response.getString("zmq_v"), "4.3.2");
}
