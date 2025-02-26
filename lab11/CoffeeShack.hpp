// Drink.hpp
#ifndef DRINK_HPP
#define DRINK_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Shack;

enum class DrinkType {small, medium, large};

class Drink {
public:
    Drink(DrinkType type=DrinkType::small, int price=0) : type_(type), price_(price) {}
    virtual int getPrice() const { return price_; }
    virtual std::string getName() const {
        switch (type_) {
            case DrinkType::small: return "small coffee";
            case DrinkType::medium: return "medium coffee";
            case DrinkType::large: return "large coffee";
            default: return "";
        }
    }
    virtual ~Drink() = default;
protected:
    int price_;
    DrinkType type_;
};

class SmallDrink : public Drink {
public:
    SmallDrink() : Drink(DrinkType::small, 5) {}
};

class MedDrink : public Drink {
public:
    MedDrink() : Drink(DrinkType::medium, 7) {}
};

class LargeDrink : public Drink {
public:
    LargeDrink() : Drink(DrinkType::large, 10) {}
};


/*
Pointer is initilaly pointing to the drink size (which returns just coffes size), when u decorarte it, the pointer is then changed to 
a new object which takes the previous object string and adds on to it, this previous is then repeated.
*/

class Ingredient : public Drink {
public:
    Ingredient(Drink* baseDrink) : baseDrink_(baseDrink) {}
    virtual int getPrice() const override {
        return baseDrink_->getPrice() + price_; 
    }
    virtual std::string getName() const override {
        return baseDrink_->getName(); 
    }
protected:
    Drink* baseDrink_;
};

class Sugar : public Ingredient {
public:
    Sugar(Drink* baseDrink) : Ingredient(baseDrink) { price_ = 1; }
    std::string getName() const override {
        return baseDrink_->getName() + ", sugar"; 
    }
};

class Cream : public Ingredient {
public:
    Cream(Drink* baseDrink) : Ingredient(baseDrink) { price_ = 2; }
    std::string getName() const override {
        return baseDrink_->getName() + ", cream"; 
    }
};

class Honey : public Ingredient {
public:
    Honey(Drink* baseDrink) : Ingredient(baseDrink) { price_ = 3; }
    std::string getName() const override {
        return baseDrink_->getName() + ", honey"; 
    }
};


class Shack{
public:
    void order(class ConcreteCustomer*); // subscribe
    void leave(class ConcreteCustomer*); 
    void prepared();
private:
    std::vector<class ConcreteCustomer*> orders_;
};

class Customer{
public:
    Customer(Shack*,Drink*,std::string);
    virtual bool notify(std::string) = 0;
    void setName(std::string obj){name_ = obj;}
    std::string getName(){return name_;}
protected:
    Drink* Drink_;
    std::string name_;
    Shack * shack_;
};




Customer::Customer(Shack* shack, Drink*obj,std::string name){
    Drink_ = obj;
    name_ = name;
    shack_ = shack;
}

class ConcreteCustomer: public Customer{
public:
    ConcreteCustomer(Shack*shack,Drink*obj,std::string name):Customer(shack,obj,name){};
    virtual bool notify(std::string name) override{
        if(name == name_){
            std::cout << "This is " << name_ << " I got my coffee, thank you!" << std::endl;
            return true;
        }
        return false;
    }
};


void Shack::order(ConcreteCustomer*obj){
    orders_.push_back(obj);
}

void Shack::prepared(){
    ConcreteCustomer* random = orders_[rand()%orders_.size()];
    for(auto&i:orders_){
        if (i->notify(random->getName())) {
            orders_.erase(std::remove(orders_.begin(),orders_.end(),random),orders_.end());
        }
    }
}

#endif
