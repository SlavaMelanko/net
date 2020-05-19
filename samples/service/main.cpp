#include "ServiceApp.h"

int main(int argc, char* argv[])
{
  try {
    ServiceApp app{ argc, argv };
    app.run();
  } catch (...) {
  }

  return 0;
}
