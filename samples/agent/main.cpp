#include "AgentApp.h"

#include <thread>

int main(int argc, char* argv[])
{
  try {
    AgentApp app{ argc, argv };
    app.run();
    std::this_thread::sleep_for(std::chrono::seconds{ 30 });
  } catch (...) {
    return 1;
  }

  return 0;
}
