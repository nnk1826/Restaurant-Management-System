#include "alcFreeDrink.h"
#include <iostream>

alcFreeDrink::alcFreeDrink(std::string name, int id, double price, float alcohol, const std::vector<std::string>& components)
    : drinkItem(name, id, price, "Alcohol-free"), materialList(components) {}

void alcFreeDrink::getDescription() const {
    std::cout << "ID: " << itemID << " Drink name: " << itemName << ", Price: " << itemPrice 
              << ", Components: ";
    for (const auto& component : materialList) {
        std::cout << component << " ";
    }
    std::cout << std::endl;
}