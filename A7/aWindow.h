#ifndef AWINDOW_H
#define AWINDOW_H

#include <string>
#include "myLog.h"
#include "A7.h"

extern Window mainWindow;

class aWindow : public Log
{
  public:
    aWindow(std::string name, int xpos, int ypos);
    ~aWindow();

    Window myWindow_ = 0;
    void showMessage(std::string message);
    void addInfo(std::string message);
    std::string myMessage_;
    std::string myInfo_;
    std::string name_;
    void checkRedrawEvent();

  private:
    int Screen_;
    void refresh();
};
#endif // AWINDOW_H
