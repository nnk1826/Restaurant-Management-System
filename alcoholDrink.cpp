#include "alcoholDrink.h"
#include <iostream>

alcoholDrink::alcoholDrink(std::string name, int id, double price, float alcohol, const std::vector<std::string>& components)
    : drinkItem(name, id, price, "Alcoholic"), alcoholContent(alcohol), alcoholList(components) {}

void alcoholDrink::getDescription() const {
    std::cout <<"ID: " << itemID << " Drink name: " << itemName << ", Alcohol Content: "
              << alcoholContent << "% , Price: " << itemPrice 
              << ", Components: ";
    for (const auto& component : alcoholList) {
        std::cout << component << " ";
    }
    std::cout << std::endl;
}
