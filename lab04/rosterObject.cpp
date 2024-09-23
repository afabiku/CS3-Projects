// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org) noexcept:
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_)),
      courses(std::move(org.courses))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
   void print() const {
      cout << firstName_ + " " + lastName_ +":";
      for(auto course: courses){
         cout << course << " ";
      }
      cout << endl;
   }

   const string getFirst() const {return firstName_;}
   const string getLast() const{return lastName_;}
   list<string> getCourses(){return courses;}

   void addCourse(std::string input){courses.push_back(input);}

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }
private:
   string firstName_;
   string lastName_;
   std::list<string> courses;
};



list<Student>::iterator located(list<Student>&, const string& first, const string& last);

// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // vector of courses of students
   list<list<Student>> courseStudents; 

   for(int i=1; i < argc-1; ++i){
      list<Student> roster;
      readRoster(roster, argv[i]);  
      cout << "\n\n" << argv[i] << "\n";  
      printRoster(roster);
      courseStudents.push_back(move(roster)); 
   }


   // reading in dropouts
   list<Student> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
   cout << "\n\n dropouts \n"; printRoster(dropouts);

   list<Student> allStudents;  // Change to list<Student> to match your Student class

   for (auto& course : courseStudents) {
      for (auto student = course.begin(); student != course.end(); ++student) {
         list<Student>::iterator location = located(allStudents, student->getFirst(), student->getLast());
         if (location != allStudents.end()) {
               location->addCourse(student->getCourses().front());  
         } else {
               allStudents.push_back(move(*student));
         }
      }
   }


   cout << "\n\n all students unsorted \n"; 
           printRoster(allStudents);

   allStudents.sort(); // sorting master list
   cout << "\n\n all students sorted \n"; printRoster(allStudents);

   allStudents.unique(); // eliminating duplicates
   cout << "\n\n all students, duplicates removed \n"; printRoster(allStudents);
   
   for (const auto& dropout : dropouts) {
      auto location = located(allStudents, dropout.getFirst(), dropout.getLast());
      if (location != allStudents.end()) {
         allStudents.erase(location); 
      }
   }
   cout << "\n\n all students, dropouts removed \n"; 
   printRoster(allStudents);
}

list<Student>::iterator located(list<Student>& masterList, const string& first, const string& last) {
   for (auto student = masterList.begin(); student != masterList.end(); ++student) {
      if (student->getFirst() == first && student->getLast() == last) {
         return student;
      }
   }
   return masterList.end();  
}


void readRoster(list<Student>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   string courseName = fileName.substr(0,fileName.find('.'));

   while(course >> first >> last){
      Student student(first, last);
      student.addCourse(courseName);
      roster.push_back(student);

   }
   course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
   for(const auto& student : roster)
      student.print();
}