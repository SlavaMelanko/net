#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Request.h>

#include <type_traits>

TEST(RequestTest, CheckTypeTraits)
{
  using Type = net::Request;

  // Primary type categories.
  EXPECT_TRUE(std::is_class_v<Type>);

  // Composite type categories.
  EXPECT_TRUE(std::is_object_v<Type>);

  // Type properties.
  EXPECT_FALSE(std::is_trivially_copyable_v<Type>);
#if defined(__APPLE__) || defined(__linux__)
  EXPECT_TRUE(std::is_standard_layout_v<Type>);
#elif defined(_WIN32)
  // AppVeyor: true for release, and false for debug?
  //EXPECT_FALSE(std::is_standard_layout_v<Type>);
#endif
  EXPECT_FALSE(std::is_abstract_v<Type>);
  EXPECT_FALSE(std::is_polymorphic_v<Type>);
  EXPECT_FALSE(std::is_final_v<Type>);

  // Supported operations.
  EXPECT_TRUE(std::is_default_constructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_default_constructible_v<Type>);
  EXPECT_FALSE(std::is_nothrow_default_constructible_v<Type>);

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

  EXPECT_FALSE(std::has_virtual_destructor_v<Type>);
}
