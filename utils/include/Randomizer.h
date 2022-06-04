#pragma once

#include <memory>
#include <string>

namespace net::utils {

class ICharSequence
{
public:
  virtual ~ICharSequence() noexcept = default;

  virtual std::string produce() const = 0;
};

class CharSequenceDecorator : public ICharSequence
{
public:
  std::string produce() const override;

protected:
  explicit CharSequenceDecorator(std::unique_ptr<ICharSequence>&& sequence = nullptr);

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

class AlnumSequence : public CharSequenceDecorator
{
public:
  // clang-format off
  explicit AlnumSequence(std::unique_ptr<ICharSequence>&& sequence = std::make_unique<LowerCaseLetterSequence>(
      std::make_unique<UpperCaseLetterSequence>(
        std::make_unique<DigitSequence>())));
  // clang-format on
};

class Randomizer
{
public:
  explicit Randomizer(
    std::unique_ptr<ICharSequence>&& sequence = std::make_unique<AlnumSequence>());

  std::string generate(const size_t& length) const;

private:
  std::unique_ptr<ICharSequence> m_sequence;
};

} // namespace net::utils
