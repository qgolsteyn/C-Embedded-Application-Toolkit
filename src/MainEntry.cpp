#include "Application.h"

#include "MainActivity.h"

int main(int argc, char const *argv[]) {

  Application app = Application();
  MainActivity startActivity = MainActivity();

  app.startApplication(&startActivity);

  //We should never be going here...
  return 0;
}
