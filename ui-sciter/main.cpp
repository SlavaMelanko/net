#include "sciter-x-window.hpp"
#include "sciter-x.h"

class MainWindow : public sciter::window
{
public:
  MainWindow()
    : window(SW_MAIN | SW_ENABLE_DEBUG | SW_CONTROLS)
  {
  }

  // passport - lists native functions and properties exposed to script under
  // 'MainWindow' interface name:
  SOM_PASSPORT_BEGIN(MainWindow)
  SOM_FUNCS(SOM_FUNC(getMessage), SOM_FUNC(quite))
  SOM_PASSPORT_END

  // function exposed to script:
  sciter::string getMessage() { return WSTR("Hello, C++ World!"); }
  void quite() { close(); }
};

#include "sciter-resources.cpp" // resources packaged into binary blob.

int uimain(std::function<int()> run)
{
  // Bind resources[] (defined in "sciter-resources.cpp") with the archive.
  sciter::archive::instance().open(aux::elements_of(resources));

  sciter::om::hasset<MainWindow> pwin = new MainWindow();

  // this:://app URL is dedicated to the sciter::archive content
  // associated with the app.
  pwin->load(WSTR("this://app/main.htm"));

  pwin->expand();

  return run();
}
