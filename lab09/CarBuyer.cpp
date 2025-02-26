// needed for lab
// Mikhail Nesterenko
// 3/18/2022

#include <iostream>
#include <vector>
#include <cstdlib>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot {
public:
    CarLot();
    Car* testDriveCar() { return *current_; }
    
    Car* nextCar() {
        ++current_;
        if (current_ == car4sale_.end()) {
            current_ = car4sale_.begin();
        }
        return *current_;
    }

    Car* buyCar(int i) { 
        Car* bought = car4sale_[i];
        car4sale_[i] = factories_[rand() % factories_.size()]->requestCar();
        return bought;
    }

    int lotSize() const { return car4sale_.size(); }

private:
    std::vector<Car*> car4sale_;
    std::vector<Car*>::iterator current_; 
    vector<CarFactory*> factories_;
};

CarLot::CarLot() {
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());

    int maxStorage = 8;
    for (int i = 0; i < maxStorage; ++i) {
        car4sale_.push_back(factories_[rand() % factories_.size()]->requestCar());
    }

    current_ = car4sale_.begin();
}

CarLot* carLotPtr = nullptr; // global pointer instantiation

// Test-drives a car and buys it if Toyota
void toyotaLover(int id,std::string model) {
    if (carLotPtr == nullptr) { carLotPtr = new CarLot(); }
    for (int i = 0; i < carLotPtr->lotSize(); ++i) {
        Car* toBuy = carLotPtr->nextCar();
        std::cout << "Jill Toyoter " << id << endl;
        std::cout << "Test driving " << toBuy->getMake() << " " << toBuy->getModel();
        if (toBuy->getMake() == "Toyota" && toBuy->getModel() == model) {
            std::cout << " Love it! Buying it!" << endl;
            carLotPtr->buyCar(i);
            break;
        } else {
            std::cout << " Did not like it!" << endl;
        }
    }
}

// Test-drives a car and buys it if Ford
void fordLover(int id,std::string model) {
    if (carLotPtr == nullptr) { carLotPtr = new CarLot(); }
    for (int i = 0; i < carLotPtr->lotSize(); ++i) {
        Car* toBuy = carLotPtr->nextCar();
        std::cout << "Jack Fordman " << id << endl;
        std::cout << "Test driving " << toBuy->getMake() << " " << toBuy->getModel();
        if (toBuy->getMake() == "Ford" && toBuy->getModel() == model) {
            std::cout << " Love it! Buying it!" << endl;
            carLotPtr->buyCar(i);
            break;
        } else {
            std::cout << " Did not like it!" << endl;
        }
    }
}

int main() {
    srand(time(nullptr));
    const int numBuyers = 20;
    for (int i = 0; i < numBuyers; ++i) {
        if (rand() % 2 == 0){
            std::vector<std::string> models = {"Corolla", "Camry", "Prius", "4Runner", "Yaris"};
            std::string want = models[rand()%models.size()];
            toyotaLover(i,want);
        }else{
            std::vector<std::string> models = {"Focus", "Mustang", "Explorer", "F-150"};
            std::string want = models[rand()%models.size()];
            fordLover(i,want);
        }
    }
}
