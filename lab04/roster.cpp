// vector and list algorithms
// Mikhail Nesterenko
// 3/11/2014

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


list<list<string>>::iterator located(list<list<string>>&,string&first,string&last);

// reading a list from a fileName
void readRoster(list<list<string>>&,string fileName);  

// printing a list out
void printRoster(const list<list<string>>&); 
void printRoster(const list<list<list<string>>>&); 

int main(int argc, char* argv[]){

   if (argc <= 1){ 
      cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << endl;
      exit(1);
   }

   list<list<list<string>>> allCourses; 
   for(int i=1; i < argc-1; ++i){
      list<list<string>> roster; 
      readRoster(roster, argv[i]);  
      cout << "\n\n" << argv[i] << "\n";  
      printRoster(roster);
      allCourses.push_back(move(roster));
   }

  
   // // reading in dropouts
   list<list<string>> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
   cout << "\n\n dropouts \n";
   printRoster(dropouts);

   // master list of students
   list<list<string>> allStudents; 
   std::string firstName;
   std::string lastName; 



   for(auto&course:allCourses){
      for(auto student = course.begin(); student != course.end(); ++student){
         auto studentIter = student->begin();
         if(studentIter != student->end()){
            firstName = *studentIter;
            ++studentIter;
            if(studentIter != student->end()){
               lastName = *studentIter;
               list<list<string>>::iterator location = located(allStudents, firstName,lastName);
               if(location != allStudents.end()){
                  ++studentIter;
                  for(;studentIter != student->end();++studentIter){
                     location->push_back(" ");
                     location->push_back(*studentIter);
                  }
               }
               else{
                  allStudents.push_back(*student);
               }
            }
         }
      }
   }


   cout << "\n\n all students unsorted \n"; 
   printRoster(allStudents);

   // sorting master list
   allStudents.sort();
   
   cout << "\n\n all students sorted \n"; 
   printRoster(allStudents);

   
   // // eliminating duplicates
   allStudents.unique(); 
   cout << "\n\n all students, duplicates removed \n"; 
   printRoster(allStudents);

   cout << "\n\n dropouts found: \n"; 
   // removing individual dropouts
   for (const auto& str : dropouts){
      auto studentIter = str.begin();
      if(studentIter != str.end()){
         string firstName = *studentIter;
         ++studentIter;
         if(studentIter != str.end()){
            string lastName = *studentIter;
            list<list<string>>::iterator location = located(allStudents, firstName,lastName);
            if(location != allStudents.end()){
               std::cout << firstName << " " << lastName << endl;
               allStudents.erase(location);
            }
         }
      }
   }
   cout << "\n\n all students, dropouts removed \n"; 
   printRoster(allStudents);
}

// reading in a file of names into a list of strings
void readRoster(list<list<string>>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   string courseName = fileName.substr(0,fileName.find('.'));

   while(course >> first >> last){
      list<std::string> object;

      object.push_back(first);
      object.push_back(last);
      object.push_back(courseName);
      roster.push_back(move(object));
   }
   course.close();
}


list<list<string>>::iterator located(list<list<string>>& masterList, std::string& first, std::string& last) {
   for(auto student = masterList.begin(); student != masterList.end(); ++student){
      auto studentIter = student->begin();
      if(studentIter != student->end() && *studentIter == first){
         ++studentIter;
         if(studentIter != student->end() && *studentIter == last){
            return student;
         }
      }
   }
   return masterList.end();
}



// printing a list out
void printRoster(const list<list<string>>& roster){
   for(auto students: roster){
      auto studentInfo = students.begin();
      auto firstName = studentInfo;
      auto lastName = ++studentInfo;

      cout << *firstName << " "<< *lastName<<":";
      for(;studentInfo != students.end(); ++studentInfo){
         if(studentInfo != firstName && studentInfo != lastName){
            cout << *(studentInfo);
         }
      }
      cout << endl;
   }
}


void printRoster(const list<list<list<string>>>& masterRoster) {
    for (const auto& course : masterRoster) {
        printRoster(course);  
    }
}



