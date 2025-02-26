// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 9/30/2021


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>



using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using std::placeholders::_1;

struct Peaches{
   double weight; // oz
   bool ripe;  // ripe or not
   void print() const { cout << (ripe?"ripe":"green") << ", " <<  weight << endl; }
};



int main(){
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input basket size: ";
   int size;
   cin >> size;

   vector <Peaches> basket(size);

   // assign random weight and ripeness peaches in the basket
   // replace with generate()
   std::generate(basket.begin(),basket.end(),[&minWeight,&maxWeight](){
      Peaches obj;
      obj.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      obj.ripe = rand() % 2;
      return obj;
   });
   
   // for_each() possibly
   cout << "all peaches"<< endl;
   std::for_each(basket.begin(),basket.end(),[](auto&i){
      i.print();
   });

   // // moving all the ripe peaches from basket to peck
   // // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Peaches> peck;
   std::remove_copy_if(basket.begin(),basket.end(),std::back_inserter(peck),[](auto & input){
      return(input.ripe);
   });

   // // for_each() possibly
   // cout << "peaches remainng in the basket"<< endl;
   std::for_each(basket.begin(),basket.end(),[](auto&i){
      i.print();
   });

   // cout << endl;

   // // for_each() possibly
   // cout << "peaches moved to the peck"<< endl;
   std::for_each(peck.begin(),peck.end(),[](auto&i){
      i.print();
   });


   // // prints every "space" peach in the peck
   const int space=3; 
   cout << "\nevery " << space << "\'d peach in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no explicit iterator arithmetic
   auto it = peck.begin();
   int i = 0;
   while(it != peck.end()){
      if(i%space == 0){
         it->print();
      }
      std::advance(it,1);
      ++i;
   }


   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()


   // TODO

   const double weightToJam = 10.0;
   double jamWeight = 0; 

   jamWeight = std::accumulate(peck.begin(),peck.end(),0.0, std::bind(std::less<>(),_1,weightToJam));



   peck.erase(remove_if(peck.begin(),peck.end(),[&](auto i){
      return (i.weight < weightToJam);
   }), peck.end());



   cout << "Weight of jam is: " << jamWeight << endl;

}
