#include "Inventory.h"
#include <iostream>
#include <vector>

extern vector<Armor> armor_vec;
extern vector<Food> food_vec;
extern vector<Weapon> weapon_vec;

Inventory::~Inventory() {
}

// 返回未装入物品的数量
int Inventory::addItem(Item *item, int num) {
    std::map<Item* , int>::iterator p;
    Item *t;
    int in = 0;
    int left = 0;
    if(size == capacity){
        in = 0;
        left = num;
        // std::cout << "包已满" << std::endl;
    }else if(size + num <= capacity){
        in = num;
        left = 0;
        // std::cout << "已全部装入" << std::endl;
    }else{
        in = capacity - size;
        left = num - in;
        // std::cout << "有" << left << "数量的物品未装入\n";
    }
    bool flag = 0;
    // 可以直接用find函数
    for (p = bag.begin(); p != bag.end(); p++){
        t = p->first;
        if(t->getName() == item->getName()){
            flag = 1;
            p->second += in;
        }
    }
    if(!flag){
        bag[item] = in;
    }
    size += in;
    return left;
}

// 返回丢弃数量
// 必须要item在背包里有
int Inventory::removeItem(Item *item, int num)
{
    // std::map<Item*, int>::iterator p;
    assert(getNum(item) != -1);
    int remove = 0;
    if(bag[item] <= num){
        remove = bag[item];
        bag.erase(item);
    }else{
        remove = num;
        bag[item] -= remove;
    }
    // std::cout << "已去除数量为" << remove << "的物品: " << item->getName() << std::endl;
    size -= remove;
    return remove;
}

void Inventory::itemShow(Item *item){
    if(item->getType() == "武器"){
        Weapon *tmp = reinterpret_cast<Weapon *>(item);
        tmp->showAtribute();
    }else if(item->getType() == "防具"){
        Armor *tmp = reinterpret_cast<Armor *>(item);
        tmp->showAtribute();
    }else if(item->getType() == "食物"){
        Food *tmp = reinterpret_cast<Food *>(item);
        tmp->showAtribute();
    }
}

void Inventory::showItem() {
    std::cout << "展示物品\n";
    if (size == 0){
        std::cout << std::endl;
        std::cout << "可惜了，没东西"<< std::endl;
        return;
    }
    int index = 0;
    std::map<Item *, int>::iterator p;
    for (p = bag.begin(); p != bag.end(); p++) {
        std::cout << "序号:" << index++ << " 名称:" 
            << p->first->getName() << " 数量:" << p->second << std::endl;
    }
    std::cout << "--------------" << std::endl;
}


Item *Inventory::selectItem(int choice){
    /*
    showItem();
    std::cout << "--------------" << std::endl;
    std::cout << std::endl
                << "输入序号查看相应物品或-1来退出" << std::endl;
    int choice;
    std::cout << "Choice: ";
    std::cin >> choice;
    */

    std::map<Item *, int>::iterator p;
    if (choice >= 0 && choice < bag.size()) {
        for (p = bag.begin(); p != bag.end(); p++) {
            if(!choice){
                // p->first->interact();
                return p->first;
            }
            choice--;
        }
    }else{
        std::cout << "无相关序号" << std::endl;
    }
    return nullptr;
}

void Inventory::interact(){}