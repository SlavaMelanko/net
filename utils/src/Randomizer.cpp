#include "Randomizer.h"

#include <algorithm>
#include <random>

namespace net::utils {

namespace {

std::string GetCharset(const int literals)
{
  std::string charset;

  if (literals & Randomizer::Digits) {
    charset += "0123456789";
  }
  if (literals & Randomizer::UpperCaseLetters) {
    charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  }
  if (literals & Randomizer::LowerCaseLetters) {
    charset += "abcdefghijklmnopqrstuvwxyz";
  }

  return charset;
}

} // namespace

std::string Randomizer::generateString(const size_t& length, const int literals)
{
  if (length == 0)
    return {};

  std::random_device rd{};
  std::mt19937 rng{ rd() };
  const auto charset = GetCharset(literals);
  std::uniform_int_distribution<> distr{ 0, static_cast<int>(charset.size()) - 1 };

  std::string str(length, 0);
  std::generate_n(
    str.begin(), length, [&]() { return charset.at(static_cast<size_t>(distr(rng))); });

  return str;
}

CharSequenceDecorator::CharSequenceDecorator(std::unique_ptr<ICharSequence>&& sequence)
  : m_sequence{ std::move(sequence) }
{}

std::string CharSequenceDecorator::produce() const
{
  return m_sequence ? m_sequence->produce() : "";
}

DigitSequence::DigitSequence(std::unique_ptr<ICharSequence>&& sequence)
  : CharSequenceDecorator{ std::move(sequence) }
{}

std::string DigitSequence::produce() const
{
  return CharSequenceDecorator::produce() + "0123456789";
}

LowerCaseLetterSequence::LowerCaseLetterSequence(std::unique_ptr<ICharSequence>&& sequence)
  : CharSequenceDecorator{ std::move(sequence) }
{}

std::string LowerCaseLetterSequence::produce() const
{
  return CharSequenceDecorator::produce() + "abcdefghijklmnopqrstuvwxyz";
}

UpperCaseLetterSequence::UpperCaseLetterSequence(std::unique_ptr<ICharSequence>&& sequence)
  : CharSequenceDecorator{ std::move(sequence) }
{}

std::string UpperCaseLetterSequence::produce() const
{
  return CharSequenceDecorator::produce() + "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

SymbolSequence::SymbolSequence(std::unique_ptr<ICharSequence>&& sequence)
  : CharSequenceDecorator{ std::move(sequence) }
{}

std::string SymbolSequence::produce() const
{
  return CharSequenceDecorator::produce() + "!@#$%^&*+-={|}";
}

} // namespace net::utils
