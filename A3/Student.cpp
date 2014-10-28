#include "Student.h"

#include <string.h>

Student::Student(const char* first_name, const char* last_name,
    unsigned long m_n) : first_name_(0), last_name_(0),
    matriculation_number_(m_n)
{
  copyString(&first_name_, first_name);
  copyString(&last_name_, last_name);
}

Student::Student(const class Student &s)
{
  matriculation_number_=s.matriculation_number_;
  copyString(&first_name_, s.first_name_);
  copyString(&last_name_, s.last_name_);
}


Student::~Student()
{
  delete [] first_name_;
  delete [] last_name_;
}

void Student::copyString(char** dest, const char* source)
{
  unsigned long str_len = strlen(source);
  char* str = new char[str_len+1];
  strncpy(str, source, str_len);
  str[str_len] = '\0';
  
  *dest = str;
}

std::ostream& operator<<(std::ostream& out, const Student& student)
{
  out << student.first_name_ << " " << student.last_name_ << " : "
      << student.matriculation_number_ << std::endl;

  return out;
}
