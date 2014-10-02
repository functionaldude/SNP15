#include "Lecture.h"
#include "Student.h"
#include "Assignment.h"

void createAssignments(Lecture& lecture)
{
  Assignment a1 = Assignment("Introduction to GIT and Compiler Errors and Warnings", 10);
  Assignment a2 = Assignment("Fun with Pointers in C", 20);

  lecture.addAssignment(1, &a1);
  lecture.addAssignment(2, &a2);
}

void addStudents(Lecture& lecture)
{
  lecture.addStudent(Student("Max", "Mustermann", 1099111));
  lecture.addStudent(Student("Jon", "Doe", 1099222));
}

int main(void)
{
  Lecture lecture("Systemnahe Programmierung");

  createAssignments(lecture);
  addStudents(lecture);

  std::cout << lecture << std::endl;

  return 0;
}
