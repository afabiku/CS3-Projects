#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <fstream>
#include <utility>
#include <algorithm>

using std::string; using std::list; using std::map; using std::make_pair; 
using std::cout; using std::endl;
class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org) noexcept:
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_)) {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
   void print() const {
      cout << firstName_ + " " + lastName_ +":";
   }

   const string getFirst() const {return firstName_;}
   const string getLast() const{return lastName_;}


    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
        return left.firstName_ < right.firstName_ || (left.firstName_ == right.firstName_ && left.lastName_ < right.lastName_);
    //   return left.lastName_ < right.lastName_ || (left.lastName_ == right.lastName_ &&  left.firstName_ < right.firstName_);
   }
private:
   string firstName_;
   string lastName_;
};

#endif