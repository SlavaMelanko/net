#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Randomizer.h>
using namespace net::utils;

#include <algorithm>

TEST(RandomizerTest, GenerateUpperCaseString)
{
  constexpr size_t length = 10;
  constexpr int literals = Randomizer::UpperCaseLetters;
  const auto str = Randomizer::generateString(length, literals);
  EXPECT_EQ(str.size(), length);
  EXPECT_TRUE(std::all_of(str.begin(), str.end(), ::isupper));
}

TEST(RandomizerTest, GenerateLowerCaseString)
{
  constexpr size_t length = 10;
  constexpr int literals = Randomizer::LowerCaseLetters;
  const auto str = Randomizer::generateString(length, literals);
  EXPECT_EQ(str.size(), 10);
  EXPECT_TRUE(std::all_of(str.begin(), str.end(), ::islower));
}

TEST(RandomizerTest, GenerateDigitsString)
{
  constexpr size_t length = 10;
  constexpr int literals = Randomizer::Digits;
  const auto str = Randomizer::generateString(length, literals);
  EXPECT_EQ(str.size(), length);
  EXPECT_TRUE(std::all_of(str.begin(), str.end(), ::isdigit));
}

TEST(RandomizerTest, GenerateZeroLengthString)
{
  constexpr size_t length = 0;
  const auto str = Randomizer::generateString(length);
  EXPECT_EQ(str.size(), length);
}

TEST(RandomizerTest, GenerateDifferentStrings)
{
  constexpr size_t length = 10;
  const auto str1 = Randomizer::generateString(length);
  const auto str2 = Randomizer::generateString(length);
  EXPECT_NE(str1, str2);
}
