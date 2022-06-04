#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Randomizer.h>

#include <algorithm>
#include <memory>

using namespace net::utils;

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
  EXPECT_EQ(str.size(), length);
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

TEST(RandomizerTest, ProduceEmptyCharSequnce)
{
  std::unique_ptr<ICharSequence> sequnce = std::make_unique<CharSequenceDecorator>();
  EXPECT_EQ(sequnce->produce(), "");
}

TEST(RandomizerTest, ProduceDigitSequnce)
{
  std::unique_ptr<ICharSequence> sequnce =
    std::make_unique<DigitSequence>(std::make_unique<CharSequenceDecorator>());
  const auto digits = sequnce->produce();
  EXPECT_EQ(digits.size(), DigitSequence{}.produce().size());      // 0 -> 9
  EXPECT_TRUE(std::all_of(digits.begin(), digits.end(), isdigit)); // TODO: ranges?
}

TEST(RandomizerTest, ProduceLettersSequnce)
{
  std::unique_ptr<ICharSequence> sequnce = std::make_unique<LowerCaseLetterSequence>(
    std::make_unique<UpperCaseLetterSequence>(std::make_unique<CharSequenceDecorator>()));
  const auto letters = sequnce->produce();
  EXPECT_EQ(letters.size(), LowerCaseLetterSequence{}.produce().size() * 2); // a -> z + A -> Z
  EXPECT_TRUE(std::all_of(letters.begin(), letters.end(), isalpha));
}

TEST(RandomizerTest, ProduceSymbolSequnce)
{
  std::unique_ptr<ICharSequence> sequnce =
    std::make_unique<SymbolSequence>(std::make_unique<CharSequenceDecorator>());
  const auto symbols = sequnce->produce();
  EXPECT_EQ(symbols.size(), SymbolSequence{}.produce().size());
  EXPECT_TRUE(std::all_of(symbols.begin(), symbols.end(), ispunct));
}
