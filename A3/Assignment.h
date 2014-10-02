#ifndef ASSIGNMENT_H_
#define ASSIGNMENT_H_

#include <iostream>

class Assignment
{
public:
  Assignment(std::string name, int points);
  virtual ~Assignment();

  friend std::ostream& operator<<(std::ostream& out, const Assignment& lecture);

private:

  std::string name_;
  int points_;

};

std::ostream& operator<<(std::ostream& out, const Assignment& lecture);

#endif /* ASSIGNMENT_H_ */
