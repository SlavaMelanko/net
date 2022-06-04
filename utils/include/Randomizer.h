#pragma once

#include <memory>
#include <string>

namespace net::utils {

class Randomizer
{
public:
  enum Literals
  {
    UpperCaseLetters = 0b0001,
    LowerCaseLetters = 0b0010,
    Digits = 0b0100,

    Letters = UpperCaseLetters | LowerCaseLetters,
    Alnum = Letters | Digits
  };

  static std::string generateString(const size_t& length, const int charset = Literals::Alnum);
};

class ICharSequence
{
public:
  virtual ~ICharSequence() noexcept = default;

  virtual std::string produce() const = 0;
};

class CharSequenceDecorator : public ICharSequence
{
public:
  CharSequenceDecorator(std::unique_ptr<ICharSequence>&& sequence = nullptr);

  std::string produce() const override;

private:
  std::unique_ptr<ICharSequence> m_sequence;
};

class DigitSequence : public CharSequenceDecorator
{
public:
  explicit DigitSequence(std::unique_ptr<ICharSequence>&& sequence = nullptr);

  std::string produce() const override;
};

class LowerCaseLetterSequence : public CharSequenceDecorator
{
public:
  explicit LowerCaseLetterSequence(std::unique_ptr<ICharSequence>&& sequence = nullptr);

  std::string produce() const override;
};

class UpperCaseLetterSequence : public CharSequenceDecorator
{
public:
  explicit UpperCaseLetterSequence(std::unique_ptr<ICharSequence>&& sequence = nullptr);

  std::string produce() const override;
};

class SymbolSequence : public CharSequenceDecorator
{
public:
  explicit SymbolSequence(std::unique_ptr<ICharSequence>&& sequence = nullptr);

  std::string produce() const override;
};

} // namespace net::utils
