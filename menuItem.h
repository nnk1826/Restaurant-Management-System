#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <vector>
#include <algorithm>

class menuItem {
protected:
    std::string itemName;
    int itemID;
    double itemPrice;

public:
    menuItem(std::string name, int id, double price);
    virtual ~menuItem() {}
    virtual void getDescription() const = 0;
    static void createItem(std::vector<menuItem*>& menu, menuItem* item);
    static void deleteItem(std::vector<menuItem*>& menu, int itemID);
    static void updateItem(std::vector<menuItem*>& menu, int itemID, const std::string& name, double price);
    int getItemID() const;
    std::string getItemName() const;
    double getItemPrice() const;
    void setItemName(const std::string& name);
    void setItemPrice(double price);
};

#endif