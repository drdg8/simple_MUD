#ifndef _TRADER_HEAD_
#define _TRADER_HEAD_

#include "NPC.h"
using namespace std;

// 存储随机生成事物
extern vector<Armor> armor_vec;
extern vector<Food> food_vec;
extern vector<Weapon> weapon_vec;

class Trader: public NPC{
private:
    // 不能直接在sell后加参数，因为声明时没有内存空间，自然不能初始化
    Inventory sell;
    // 当Trader死了，寻仇者
    vector<NPC *> helper;

public:
    Trader(Character *p, std::string name, int hp, int damage, int defence, int exp, int money, string prompt): 
        NPC(p, name,  hp, damage, defence, exp, money, prompt), sell(MAXN)
    {
        type = "商人";
    }
    void insertHelper(NPC *npc){
        helper.push_back(npc);
    }
    void help(){
        if(helper.size() > 0){
            cout << "真是不幸啊，" << name << "的势力来找你了。自求多福吧。\n";
            cout << "---------------------\n";
            for(auto i: helper){
                i->interact(1);
            }
        }
    }

    void renewSell();

    int insertSell(Item *item, int num);
    void showSell();
    int removeSell(Item *item, int num);
    void goSell();
    void goBuy();
    void interact();
};

#endif