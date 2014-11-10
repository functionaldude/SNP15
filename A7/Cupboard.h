#ifndef Cupboard_H
#define Cupboard_H
#include <string>
#include "aWindow.h"
#include "CupStorage.h"

class Cupboard : public CupStorage, public aWindow
{
  public:
    Cupboard(unsigned int counter, std::string name);
    void upgrade(unsigned int counter);
    virtual ~Cupboard();

    bool enoughCups();
    void showCupboardContent();

  private:

};

#endif // Cupboard_H
