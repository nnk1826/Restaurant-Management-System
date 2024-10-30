#ifndef ORDER_H
#define ORDER_H

#include "menuItem.h"
#include <unordered_map>

class order {
private:
    std::unordered_map<int, int> orderItems;

public:
    bool addToOrder(int itemID, int quantity, const std::vector<menuItem*>& menu);
    bool removeFromOrder(int itemID, int removeQuantity);
    void displayOrder(const std::vector<menuItem*>& menu) const;
    double returnTotalAmount(const std::vector<menuItem*>& menu) const;
    const std::unordered_map<int,int>& getOrderItems() const;
};

#endif