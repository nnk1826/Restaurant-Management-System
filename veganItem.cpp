#include "veganItem.h"
#include <iostream>

veganItem::veganItem(std::string name, int id, double price, std::string spice)
    : foodItem(name, id, price, "Vegan", spice) {}

void veganItem::getDescription() const {
    std::cout << "ID: " << itemID<<" Vegan Item: " << itemName << ", Spice Level: " << spiceLevel 
              << ", Price: " << itemPrice << std::endl;
}