#include "drinkItem.h"
#include <iostream>

drinkItem::drinkItem(std::string name, int id, double price, std::string type)
    : menuItem(name, id, price), typeOfDrink(type) {}

void drinkItem::getDescription() const {
    std::cout << "Drink Item: " << itemName << ", Type: " << typeOfDrink 
              << ", Price: " << itemPrice << std::endl;
}