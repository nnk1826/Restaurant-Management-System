#include "menuItem.h"
#include <iostream>

menuItem::menuItem(std::string name, int id, double price)
    : itemName(name), itemID(id), itemPrice(price) {}

void menuItem::createItem(std::vector<menuItem*>& menu, menuItem* item) {
    menu.push_back(item);
}

void menuItem::deleteItem(std::vector<menuItem*>& menu, int itemID) {
    menu.erase(std::remove_if(menu.begin(), menu.end(),
        [itemID](menuItem* item) { return item->itemID == itemID; }), menu.end());
}

void menuItem::updateItem(std::vector<menuItem*>& menu, int itemID, const std::string& name, double price) {
    auto it = std::find_if(menu.begin(), menu.end(),
        [itemID](menuItem* item) { return item->itemID == itemID; });
    
    if (it != menu.end()) {
        (*it)->setItemName(name);
        (*it)->setItemPrice(price);
    }
}

int menuItem::getItemID() const {
    return itemID;
}

std::string menuItem::getItemName() const {
    return itemName;
} 

double menuItem::getItemPrice() const {
    return itemPrice;
}

void menuItem::setItemName(const std::string& name) {
    itemName = name;
}

void menuItem::setItemPrice(double price) {
    itemPrice = price;
}