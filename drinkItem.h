#ifndef DRINKITEM_H
#define DRINKITEM_H

#include "menuItem.h"

class drinkItem : public menuItem {
protected:
    std::string typeOfDrink;

public:
    drinkItem(std::string name, int id, double price, std::string type);
    void getDescription() const override;
};

#endif