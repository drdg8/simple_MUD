#ifndef _FOOD_HEAD_
#define _FOOD_HEAD_
#include "Item.h"
#include <string>
#include <iostream>

class Food : public Item
{
private:
    int addhp;
    // std::string armorType;

public:
    Food(int addhp = 0, std::string name = "NONE", std::string description = "NONE", std::string type = "食物", int level = 0, int buyValue = 0, int sellValue = 0, int rarity = 0);
    virtual ~Food();

    int getAddhp() const {
        return addhp;
    }

    void showAtribute();

    void interact();
};




#endif