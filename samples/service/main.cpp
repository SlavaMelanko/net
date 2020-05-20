#include "App.h"

#include <thread>

int main(int argc, char* argv[])
{
  try {
    App app{ argc, argv };
    app.run();
    std::this_thread::sleep_for(std::chrono::seconds{ 1 });
  } catch (...) {
  }

  return 0;
}
