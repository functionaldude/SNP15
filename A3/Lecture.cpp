#include "Lecture.h"
#include "Assignment.h"

Lecture::Lecture(std::string name) : name_(name)
{
}

Lecture::~Lecture()
{
  ass_it iterator_assa = assignments_.begin();
  while (iterator_assa != assignments_.end()) {
    delete iterator_assa->second;
    iterator_assa->~pair();
    iterator_assa++;
  }

  student_it2 iterator_student = students_.begin();
  while (iterator_student != students_.end()) {
    iterator_student->deleteNames();
    iterator_student++;
  }
  
}

void Lecture::addStudent(Student student)
{
  students_.push_back(student);
}

void Lecture::addAssignment(unsigned int number, Assignment* assignment)
{
  assignments_.insert(std::make_pair(number, assignment));
}

std::ostream& operator<<(std::ostream& out, const Lecture& lecture)
{
  out << "Lecture: " << lecture.name_ << std::endl;

  out << "Assignments:" << std::endl;

  for(Lecture::ass_const_it it = lecture.assignments_.begin(); it != lecture.assignments_.end(); it++)
  {
    out << "A" << it->first << ": " << *(it->second);
  }

  out << "Students:" << std::endl;

  for(Lecture::student_it it = lecture.students_.begin(); it != lecture.students_.end(); it++)
  {
    out << *it;
  }

  return out;
}
