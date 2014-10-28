#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>

class Student
{
public:
  /**
   * constructor
   *
   * @param first_name
   * @param last_name
   * @param m_n
   */
  Student(const char* first_name, const char* last_name, unsigned long m_n);
  Student(const class Student &s);

  virtual ~Student();

  friend std::ostream& operator<<(std::ostream& out, const Student& student);

private:

  static void copyString(char** dest, const char* source);

  char* first_name_;
  char* last_name_;

  unsigned long matriculation_number_;

};

std::ostream& operator<<(std::ostream& out, const Student& student);

#endif /* STUDENT_H_ */
