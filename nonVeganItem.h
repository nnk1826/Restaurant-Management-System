#ifndef NONVEGANITEM_H
#define NONVEGANITEM_H

#include "foodItem.h"

class nonVeganItem : public foodItem {
public:
    nonVeganItem(std::string name, int id, double price, std::string spice);
    void getDescription() const override;
};

#endif