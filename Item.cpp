#include "item.h"
#include <iostream>

Item::Item(std::string name, std::string description, std::string type,int level, int buyValue, int sellValue, int rarity):name(name),description(description),type(type),level(level),buyValue(buyValue),sellValue(sellValue),rarity(rarity) {
    
}

Item::~Item() {

}

void Item::showAtribute(){
	std::cout << "== 物品表 ==" << std::endl;
	std::cout << "||名字: " << name << std::endl;
	std::cout << "||类别: " << type << std::endl;
	std::cout << "||等级: " << level << std::endl;
	std::cout << "||稀有度: " << rarity << std::endl;
    cout << description << endl;
    cout << "-----------------" << endl;
}