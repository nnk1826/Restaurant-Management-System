#ifndef ALCOHOLDRINK_H
#define ALCOHOLDRINK_H

#include "drinkItem.h"
#include <string>
#include <vector>

class alcoholDrink : public drinkItem {
private:
    float alcoholContent;
    std::vector<std::string> alcoholList; 

public:
    alcoholDrink(std::string name, int id, double price, float alcohol, const std::vector<std::string>& components);
    void getDescription() const override;
}; 

#endif
