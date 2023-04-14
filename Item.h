#ifndef _ITEM_HEAD_
#define _ITEM_HEAD_

#include <iomanip>
#include <iostream>
#include <ctime>
#include <assert.h>
// #define NDEBUG
#define MAXN 999
using namespace std;

// 不加num的原因是Item与Item间不应该有区别
class Item{
public:
	Item(std::string name = "NONE", std::string description = "NONE", std::string type = "NONE", int level = 0, int buyValue = 0, int sellValue = 0, int rarity = 0);
	virtual ~Item();

	//Accessor
	inline const std::string& getName() const {
		return this->name;
	}
	inline const std::string& getDescription() const {
		return this->description;
	}
	inline const std::string& getType() const {
		return this->type;
	}
	inline const int& getBuyValue() const {
		return this->buyValue;
	}
	inline const int& getSellValue() const {
		return this->sellValue;
	}
	inline const int& getLevel() const {
		return this->level;
	}
	inline const int& getRarity() const {
		return this->rarity;
	}

    virtual void showAtribute();

protected:
	std::string name;
	std::string description;
	std::string type;

	int level;
	// 物品被购买的价值
	int buyValue;
	// 物品被出售的价值
	int sellValue;
	int rarity;
};

#endif