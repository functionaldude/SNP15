#include "aWindow.h"
#include "A7.h"
#include "assert.h"

// Display the kitchen in an X-Windows environment

aWindow::aWindow(std::string name, int xpos, int ypos) :
    Log(name)
{
  log(" creation ");
  Screen_ = DefaultScreen(display);
  XLockDisplay(display);
  myWindow_ = XCreateSimpleWindow(display, mainWindow, 30 + 500 * xpos, ypos * 50, 450, 60, 1,
                                  BlackPixel(display, Screen_), WhitePixel(display, Screen_));
  XSelectInput(display, myWindow_, ExposureMask | KeyPressMask);
  XMapWindow(display, myWindow_);
  name_ = name;
  XStoreName(display, myWindow_, name_.c_str());
  myMessage_ = "started";
  myInfo_ = "";
  XUnlockDisplay(display);
  log(" created ");

}

void aWindow::showMessage(std::string _message)
{
  myMessage_ = _message;
  log(_message);
  refresh();
}

void aWindow::addInfo(std::string _addInfo)
{
  myInfo_ = _addInfo;
  log(_addInfo);
  refresh();
}

void aWindow::refresh()
{
  log("Refreshing");
  assert(myWindow_ != 0);
  XLockDisplay(display);
  XClearArea(display, myWindow_, 0, 0, 450, 60, false);
  XDrawString(display, myWindow_, DefaultGC(display, Screen_), 10, 12, name_.c_str(), name_.length());
  XDrawString(display, myWindow_, DefaultGC(display, Screen_), 10, 25, myMessage_.c_str(), myMessage_.length());
  XDrawString(display, myWindow_, DefaultGC(display, Screen_), 10, 37, myInfo_.c_str(), myInfo_.length());
  XUnlockDisplay(display);
  XFlush(display);
}
aWindow::~aWindow()

{

}

void aWindow::checkRedrawEvent()
{
  assert(myWindow_ != 0);
  XEvent e;
  if (XCheckWindowEvent(display, myWindow_, ExposureMask, &e))
  {
    log(" redraw ");
    refresh();
  };

}
