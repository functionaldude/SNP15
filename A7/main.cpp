#include <pthread.h>
#include <assert.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <iostream>

#include "A7.h"
#include "Employee.h"
#include "Boss.h"
#include "CoffeeKitchen.h"

const char* Names[] =
{
"Karl", "Hans", "Maria", "Magdalena", "Peter", "Petra", "Susi", "Strolchi", "NullBock", "Mausi", "Hansi", "Mary",
  "Pezi", "Karli", "Malli", "Josie", NULL
};
const char* BossNames[] =
{
"Boss Reinhard", "Boss Roderick", "Boss Stefan", "Boss Harald", "Boss Gerhard", NULL
};

// global display variabels. These are truely global.
Display* display;
Window mainWindow;
bool all_threads_created;

int main(int argc, char* argv[])
{
  if (argc != 5)
  {
    fprintf(stderr, "Usage: ./A7 <kitchen size> <employees> <cups> <bosses>\n");
    exit(E_WRONGPARAMETERS);
  }

  // ensure that the display stuff is threadsafe
  assert(XInitThreads());

  // open X Display
  display = XOpenDisplay(NULL);
  if (display == NULL)
  {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  // create main window
  int s = DefaultScreen(display);
  std::string wTitle = "A7";
  mainWindow = XCreateSimpleWindow(display, RootWindow(display, s), 0, 0, 1024, 768, 1, BlackPixel(display, s),
                                   WhitePixel(display, s));
  XMapWindow(display, mainWindow);
  XStoreName(display, mainWindow, wTitle.c_str());

  //  lets check the parameters
  unsigned int num_kitchensize = strtoul(argv[1], NULL, 10);
  unsigned int num_employees = strtoul(argv[2], NULL, 10);
  unsigned int num_cups = strtoul(argv[3], NULL, 10);
  unsigned int num_bosses = strtoul(argv[4], NULL, 10);

  std::cout << "A CoffeeKitchen with space for " << num_kitchensize << "  people. " << num_employees
      << " employees are working, " << num_cups << " cups, " << num_bosses << " bosses, " << std::endl;
  if (num_kitchensize <= 0 || num_employees <= 0 || num_cups <= num_bosses || num_bosses <= 0)
  {
    std::cout << "Wrong parameters chosen. Think twice." << std::endl;
    exit(E_WRONGPARAMETERS);
  }
  // we need a kitchen to work with
  CoffeeKitchen* Kitchen = CoffeeKitchen::instance();
  // the standard kitchen comes in a simple size. Upgrade the kitchen to real sizes
  Kitchen->upgrade(num_kitchensize, num_cups);

  // now we have to hire the bosses and the employees
  const char* *nameP;

  nameP = BossNames;
  Boss* newB;
  std::string App = "";
  for (unsigned int i = 0; i < num_bosses; i++)
  {
    newB = new Boss(*nameP, i);
    usleep(WAITINGTIME);
    nameP++;
    if (*nameP == NULL)
      nameP = BossNames;
    Boss::bosses_.push_back(newB);
  }

  nameP = Names;
  Employee* newE;
  for (unsigned int i = 0; i < num_employees; i++)
  {
    newE = new Employee(*nameP, i + Boss::bosses_.size());
    usleep(WAITINGTIME);
    nameP++;
    if (*nameP == NULL)
      nameP = Names;
    Employee::employees_.push_back(newE);
  }

  // Everything thread based object we have created needs to be started
  // this avoids potential race condition during object creation phase
  // now we need to start these beasts

  all_threads_created = true;

  // our employees never go home. But if we leave main, they get killed.
  // so we are joining one of them (the last employee created above)
  newE->join();
  return 0;
}
