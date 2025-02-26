


#include "drink.hpp"

int main() {
    char sizeChoice, ingredientChoice;
    Drink* coffee = nullptr;

    std::cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
    std::cin >> sizeChoice;

    switch (sizeChoice) {
        case 'l': coffee = new LargeDrink(); break;
        case 'm': coffee = new MedDrink(); break;
        case 's': coffee = new SmallDrink(); break;
        default:
            std::cout << "Invalid size selection.\n";
            return 1;
    }

    while (true) {
        std::cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
        std::cin >> ingredientChoice;

        if (ingredientChoice == 'd') break;

        switch (ingredientChoice) {
            case 's':
                coffee = new Sugar(coffee); 
                break;
            case 'c':
                coffee = new Cream(coffee); 
                break;
            case 'h':
                coffee = new Honey(coffee); 
                break;
            default:
                std::cout << "Invalid ingredient selection.\n";
                continue;  
        }
    }

    std::string name;
    std::cout << "Can I get your name? ";
    std::cin >> name;

    std::cout << name << ", your " << coffee->getName() << " is ready. It will be $" << coffee->getPrice() << ", please.\n";

}
