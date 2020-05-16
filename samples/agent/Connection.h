#pragma once

class Connection
{
public:
  virtual ~Connection() noexcept = default;

  virtual void run() = 0;

protected:
  virtual void process() = 0;
};
