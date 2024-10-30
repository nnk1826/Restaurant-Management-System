#ifndef ALCFREEDRINK_H
#define ALCFREEDRINK_H

#include "drinkItem.h"
#include <string>
#include <vector>

class alcFreeDrink : public drinkItem {
private:
    std::vector<std::string> materialList; 

public:
    alcFreeDrink(std::string name, int id, double price, float alcohol, const std::vector<std::string>& components);
    void getDescription() const override;
}; 

#endif