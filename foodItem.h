#ifndef FOODITEM_H
#define FOODITEM_H

#include "menuItem.h"

class foodItem : public menuItem {
protected:
    std::string category;
    std::string spiceLevel;

public:
    foodItem(std::string name, int id, double price, std::string cat, std::string spice);
    void getDescription() const override;
};

#endif