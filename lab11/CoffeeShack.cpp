#include "CoffeeShack.hpp"


int main(){
    Shack* Shop = new Shack();
    for(;;){
        Drink* coffee;

        char anwser;
        std::string name;
        std::cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee?: ";
        std::cin >> anwser;

        switch(anwser){
            case 'l':
                coffee = new LargeDrink();
                break;
            case 'm':
                coffee = new MedDrink();
                break;
            case 's':
                coffee = new SmallDrink();
                break;
        }

        do{
            std::cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one?: ";
            std::cin >> anwser;
            switch(anwser){
                case 's':
                    coffee = new Sugar(coffee);
                    break;
                case 'c':
                    coffee = new Cream(coffee);
                    break;
                case 'h':
                    coffee = new Honey(coffee);
                    break;
                case 'd':
                    break;
            }
        }while(anwser != 'd');
        std::cout << "Can I get your name?: ";
        std::cin >> name;
        ConcreteCustomer * customer = new ConcreteCustomer(Shop,coffee,name);
        Shop->order(customer);
        std::cout << "Please wait " << name << std::endl;  

        bool serve = (rand() % 3 == 1);  
        std::cout << serve << std::endl;
        if (serve) {
            Shop->prepared();
        }

    }
}
