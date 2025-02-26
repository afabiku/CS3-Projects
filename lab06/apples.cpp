// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 09/26/2022


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};



int main(){
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

   // assign random weight and color to apples in the crate
   // replace with generate()
    std::generate(crate.begin(),crate.end(),[&](){
        Apples obj;
        obj.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
        obj.color = rand() % 2 == 1 ? "green" : "red";
        return obj;
    });

    // for_each() possibly
   cout << "all appleas"<< endl;
   std::for_each(crate.begin(),crate.end(),[](auto it){
    it.print();
   });


   
   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;

   // count_if()
   int cnt = std::count_if(crate.begin(),crate.end(),[&](auto it){
        return (it.weight > toFind);
   });

   cout << "There are " << cnt << " apples heavier than " 
	<< toFind << " oz" <<  endl;

   // find_if()
    cout << "at positions ";
    auto start = crate.begin();
    auto pos = crate.end();
    while(true){
        pos = std::find_if(start,crate.end(),[&](auto input){
            return (input.weight > toFind);
        });

        if(pos != crate.end()){
            std::cout << (pos - crate.begin()) << " ";
            start = pos + 1;
        }else{
            break;
        }
    }

    std::cout << std::endl;





   // max_element()
   // max_element()
   auto element = std::max_element(crate.cbegin(),crate.cend(),[](const auto&lhs, const auto&rhs){
        return (rhs.weight > lhs.weight);
   });
   std::cout << "Heaviest apple weighs: " << element->weight  << " oz" << std::endl;


   // for_each() or accumulate()
   double sum = std::accumulate(crate.begin(),crate.end(),0.0,[&](double lhs, const auto&rhs){
        return (lhs + rhs.weight);
   });
   cout << "Total apple weight is: " << sum << " oz" << endl;



   // transform();
   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;
   std::transform(crate.begin(),crate.end(),crate.begin(),[&toGrow](auto& input){
        input.weight += toGrow;
        return input;
   });


//    // remove_if()
   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;


//    // removing small apples
//    // nested loops, replace with a single loop modification idiom
   std::remove_if(crate.begin(),crate.end(),[&minAccept](auto &i){
        return (i.weight < minAccept);
   });




//    // bubble sort, replace with sort()
   std::sort(crate.begin(),crate.end(),[](auto&lhs, auto&rhs){
        return(lhs.weight > rhs.weight);
   });


//    // for_each() possibly
//    cout << "sorted remaining apples"<< endl;
    std::for_each(crate.begin(),crate.end(),[](auto & input){
        input.print();
    });

}
