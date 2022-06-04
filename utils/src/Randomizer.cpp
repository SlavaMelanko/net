#include "Randomizer.h"

#include <algorithm>
#include <random>

namespace net::utils {

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

AlnumSequence::AlnumSequence(std::unique_ptr<ICharSequence>&& sequence)
  : CharSequenceDecorator{ std::move(sequence) }
{}

Randomizer::Randomizer(std::unique_ptr<ICharSequence>&& sequence)
  : m_sequence{ std::move(sequence) }
{}

std::string Randomizer::generate(const size_t& length) const
{
  if (length == 0 || !m_sequence) {
    return {};
  }

  std::random_device rd{};
  std::mt19937 rng{ rd() };
  const auto chars = m_sequence->produce();
  std::uniform_int_distribution distr{ 0, static_cast<int>(chars.size()) - 1 };

  std::string str(length, 0);
  std::generate_n(str.begin(), length, [&]() { return chars.at(static_cast<size_t>(distr(rng))); });

  return str;
}

} // namespace net::utils
