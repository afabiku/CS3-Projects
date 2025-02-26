// selecting oranges
// converting vectors to multimaps
// Mikhail Nesterenko
// 9/26/2022


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

std::multimap<Variety,string> ntree;

struct Fruit{
   Variety v;
   string color; // red, green or orange
};


int main(){
   srand(time(nullptr));
   int randomAmount = rand()%100+1;

    for(int i = 0; i < randomAmount; ++i){
        Variety var = static_cast<Variety>(rand() % 3);
        string col =  colors[rand()%3];
        ntree.emplace(var,col);
    }

    auto upperIT = ntree.upper_bound(Variety::orange);
    auto lowerIT = ntree.lower_bound(Variety::orange);

    for(auto it = lowerIT;it != upperIT; ++it){
        std::cout << it->second << std::endl;
    }

}
