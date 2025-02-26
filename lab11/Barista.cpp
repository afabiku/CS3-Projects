#include "Barista.hpp"

int main() {
    Barista* seller = new JuniorBarista(new SeniorBarista(new Manager));

    Drink* smallCoffee = new SmallDrink();
    Drink* coffeeWithSugar = new Sugar(new MedDrink());
    Drink* coffeeWithHoney = new Honey(new LargeDrink());
    Drink* coffeeWithSugarAndHoney = new Honey(new Sugar(new LargeDrink()));

    // Orders
    std::cout << "Order 1: " << std::endl;
    seller->prepare(smallCoffee);
    std::cout << std::endl;
    
    std::cout << "Order 2: " << std::endl;
    seller->prepare(coffeeWithSugar);
        std::cout << std::endl;

    std::cout << "Order 3: " << std::endl;
    seller->prepare(coffeeWithHoney);
        std::cout << std::endl;

    std::cout << "Order 4: " << std::endl;
    seller->prepare(coffeeWithSugarAndHoney);
    std::cout << std::endl;


}
