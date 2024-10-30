#ifndef VEGANITEM_H
#define VEGANITEM_H

#include "foodItem.h"

class veganItem : public foodItem {
public:
    veganItem(std::string name, int id, double price, std::string spice);
    void getDescription() const override;
};

#endif