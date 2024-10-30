#include "order.h"
#include <iostream>

bool order::addToOrder(int itemID, int quantity, const std::vector<menuItem*>& menu) {
    for (const auto& item : menu) {
        if (item->getItemID() == itemID) {
            orderItems[itemID] += quantity;
            return true;
        }
    }
    return false; // Return false if the item is not found in the menu
}

bool order::removeFromOrder(int itemID, int removeQuantity) {
    auto it = orderItems.find(itemID);
    if (it != orderItems.end()) {
        if (removeQuantity >= it->second) {
            orderItems.erase(it);
        } else {
            it->second -= removeQuantity;
        }
        return true;
    }
    return false;
}

void order::displayOrder(const std::vector<menuItem*>& menu) const {
    std::cout << "Items:\n";
    for (const auto& [itemID, quantity] : orderItems) {
        bool itemFound = false;
        for (const auto& item : menu) {
            if (item->getItemID() == itemID) {
                std::cout << "- " << item->getItemName() << ": " << quantity << "\n";
                itemFound = true;
                break;
            } 
        }

        //Checking if the item is found
        if(!itemFound){
            std::cout << "Item ID: " << itemID << " Quantity: " << quantity <<" isn't found in the menu\n";
        }
    }
} 

double order::returnTotalAmount(const std::vector<menuItem*>& menu) const{ //Return every order individual amount
    double totalAmount = 0;
    for (const auto& [itemID, quantity] : orderItems){
        bool itemFound = false;
        for (const auto& item : menu){
            if(item->getItemID() == itemID){
                totalAmount += item->getItemPrice()*quantity;
                itemFound = true;
                break;
            } 
        }

        //Checking if the item is found
        if (!itemFound) {
            std::cerr << "Item ID: " << itemID << " Quantity: " << quantity <<" isn't found in the menu\n";
        }
    }
    return totalAmount;
}

const std::unordered_map<int,int>& order::getOrderItems() const{ //Return the orderItem map for the any class to work with.
    return orderItems;
};
