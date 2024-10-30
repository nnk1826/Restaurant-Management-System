#include "foodItem.h"
#include <iostream>

foodItem::foodItem(std::string name, int id, double price, std::string cat, std::string spice)
    : menuItem(name, id, price), category(cat), spiceLevel(spice) {}

void foodItem::getDescription() const {
    std::cout << "Food Item: " << itemName << ", Category: " << category 
              << ", Spice Level: " << spiceLevel << ", Price: " << itemPrice << std::endl;
}