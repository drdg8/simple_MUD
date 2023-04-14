#ifndef _ARMOR_HEAD_
#define _ARMOR_HEAD_
#include "Item.h"
class Armor : public Item
{
private:
    int defenceAtt;
    int defenceDef;
    // std::string armorType;

public:
    Armor(int defenceAtt = 0, int defenceDef = 0, std::string name = "NONE", std::string description = "NONE", std::string type = "Armor", int level = 0, int buyValue = 0, int sellValue = 0, int rarity = 0);
    virtual ~Armor();

    int getDefenceAtt() const {
        return defenceAtt;
    }

    int getDefenceDef() const {
        return defenceDef;
    }
    std::string toString();

    void showAtribute();

    void interact();
};




#endif