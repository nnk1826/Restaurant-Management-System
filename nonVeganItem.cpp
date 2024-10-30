#include "nonVeganItem.h"
#include <iostream>

nonVeganItem::nonVeganItem(std::string name, int id, double price, std::string spice)
    : foodItem(name, id, price, "Non-Vegan", spice) {}

void nonVeganItem::getDescription() const {
    std::cout <<"ID: "<< itemID << " Non-vegan Item: " << itemName << ", Spice Level: " << spiceLevel 
              << ", Price: " << itemPrice << std::endl;
}