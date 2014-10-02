#include "Assignment.h"

Assignment::Assignment(std::string name, int points) : name_(name), points_(points)
{
}

Assignment::~Assignment()
{
}

std::ostream& operator<<(std::ostream& out, const Assignment& ass)
{
  out << ass.name_ << " " << ass.points_ << " points" << std::endl;
  return out;
}
