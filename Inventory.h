#ifndef _INVENTORY_HEAD_
#define _INVENTORY_HEAD_

#include "Item.h"
#include "Weapon.h"
#include "Food.h"
#include "Armor.h"
#include <map>

class Inventory {
public:
	Inventory(int c = 20): size(0), capacity(c) {}
	// Inventory(int s, int c, map<Item *, int> cbag): size(s), capacity(c), bag(cbag) {}
	virtual ~Inventory();

	// index是序号
	int getIndex() const {
		return bag.size();
	}

	int getSize() const {
		return size;
	}

	int getCapacity() const {
		return capacity;
	}

	int changeCapacity(int c){
		capacity += c;
		return capacity;
	}

	// 返回未装入数量
	int addItem(Item *item, int num = 1);

	// 返回丢弃数量
	int removeItem(Item *item, int num = 1);

	// 这是展示item的属性
	void itemShow(Item *item);

	virtual void showItem();

	Item *selectItem(int choice);

	// 如果没有就返回-1
	int getNum(Item *tmp) const {
		if ( bag.find(tmp) != bag.end()){
			return bag.find(tmp)->second;
		}
		return -1;
	}

	void clear(){
		bag.clear();
		size = 0;
	}

	Inventory(const Inventory& a): size(a.size), capacity(a.capacity){ 
		//map<Item *, int>::iterator p;
		//for (p = a.bag.begin(); p != a.bag.end(); p++){
		for( auto p: a.bag ){
			bag.insert(pair<Item *, int>(p.first, p.second));
		}
	}

	virtual void interact();

protected:
	std::map<Item*, int> bag;
	// std::vector<Item*> inventoryVec;
	
	int size;
	int capacity;
};

#endif