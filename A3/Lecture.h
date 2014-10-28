#ifndef LECTURE_H_
#define LECTURE_H_

#include <list>
#include <map>
#include <string>

#include "Student.h"

class Assignment;

class Lecture
{
public:
  Lecture(std::string name);
  virtual ~Lecture();

  void addStudent(Student student);

  void addAssignment(unsigned int number, Assignment* assignment);

  friend std::ostream& operator<<(std::ostream& out, const Lecture& lecture);
private:

  std::string name_;

  typedef std::list<Student>::const_iterator student_it;
  std::list<Student> students_;

  // the assignments:
  typedef std::map<unsigned int, Assignment*>::iterator ass_it;
  typedef std::map<unsigned int, Assignment*>::const_iterator ass_const_it;
  std::map<unsigned int, Assignment*> assignments_;

};

std::ostream& operator<<(std::ostream& out, const Lecture& lecture);

#endif /* LECTURE_H_ */
