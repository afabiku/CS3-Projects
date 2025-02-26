// hashmap test file
// Mikhail Nesterenko,  Tsung-Heng Wu
// 3/6/2024

#include "hashmap.hpp"
#include <iostream>
#include <string>
#include <cassert>

using std::string;

int main() {

   //
   // <int, int> hashmap test
   //
   hashmap<int, int> myHash;
   
   // test inserts
   pair<const pair<const int, int>*, bool> result;

   result = myHash.insert(make_pair(4, 40));
   assert(result.second);
   assert(result.first->first == 4);
   assert(result.first->second == 40);

   result = myHash.insert(make_pair(105, 1050));
   assert(result.second);
   assert(result.first->first == 105);
   assert(result.first->second == 1050);

   result = myHash.insert(make_pair(6, 60));
   assert(result.second);
   assert(result.first->first == 6);
   assert(result.first->second == 60);

   result = myHash.insert(make_pair(107, 1070));
   assert(result.second);
   assert(result.first->first == 107);
   assert(result.first->second == 1070);

   result = myHash.insert(make_pair(90, 900));
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.insert(make_pair(95, 950));
   assert(result.second);
   assert(result.first->first == 95);
   assert(result.first->second == 950);

   result = myHash.insert(make_pair(6, 70)); // insert with a duplicate key
   assert(!result.second);
   assert(result.first->first == 6);
   assert(result.first->second == 60);


   // searching map
   // x will have type hashmap<int, int>::value_type*
   auto x = myHash.find(4);
   assert(x != nullptr);
   assert(x->second == 40);

   x = myHash.find(5);
   assert(x == nullptr);


   // test deletes
   result = myHash.erase(4); // delete with next element in same bucket
   assert(result.second);
   assert(result.first->first == 105);
   assert(result.first->second == 1050);

   result = myHash.erase(107); // delete the last element in a bucket
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.erase(6);
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.erase(105);
   assert(result.second);
   assert(result.first->first == 90);
   assert(result.first->second == 900);

   result = myHash.erase(95); // erase the last element in the container
   assert(result.second);
   assert(result.first== nullptr);

   result = myHash.erase(90); // erased all elements in container
   assert(result.second);
   assert(result.first == nullptr);

   result = myHash.erase(5); // erase key not in container
   assert(!result.second);
   // first is unspecified


   //
   // <integer, string> hashmap test
   //
    hashmap<int, string> employees;

    // test inserts
    pair<const pair<const int, string>*, bool> empResult;

    empResult = employees.insert(make_pair(101, "Alice"));
    assert(empResult.second);
    assert(empResult.first->first == 101);
    assert(empResult.first->second == "Alice");

    empResult = employees.insert(make_pair(202, "Bob"));
    assert(empResult.second);
    assert(empResult.first->first == 202);
    assert(empResult.first->second == "Bob");

    empResult = employees.insert(make_pair(303, "Charlie"));
    assert(empResult.second);
    assert(empResult.first->first == 303);
    assert(empResult.first->second == "Charlie");

    empResult = employees.insert(make_pair(101, "Alicia")); 
    assert(!empResult.second); 
    assert(empResult.first->second == "Alice"); 

    // test find
    auto empPtr = employees.find(202);
    assert(empPtr != nullptr);
    assert(empPtr->second == "Bob");

    empPtr = employees.find(404); 
    assert(empPtr == nullptr);

    // test erase
    empResult = employees.erase(101); 
    assert(empResult.second);
    assert(empResult.first->first == 202);

    empResult = employees.erase(404); 
    assert(!empResult.second);
    assert(empResult.first == nullptr); 

    // test operator[]
    employees[404] = "David";
    assert(employees.find(404)->second == "David");

    employees[202] = "Robert"; 
    assert(employees.find(202)->second == "Robert");

    // test rehash
    employees.rehash(200); 
    assert(employees.find(303) != nullptr); 
    assert(employees.find(303)->second == "Charlie");

    employees.rehash(2); 
    assert(employees.find(303) != nullptr); 


    std::cout << "Tests passed" << std::endl;
}