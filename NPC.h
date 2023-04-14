#ifndef _NPC_HEAD_
#define _NPC_HEAD_

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include "Character.h"          // 验证是否可以包含
#include "Inventory.h"

using namespace std;


class NPC{
protected:
    std::string name;
    string type;
    int hp;
    int damage;
    int defence;
    int exp;
    int money;

    string prompt;
    Inventory drop;
    Character &player;   // 调整player的位置

    static vector<string> foodNames;
    static vector<string> weaponNames;
    static vector<string> armorNames;

public:
    static vector<string> initFoodName(){
        vector<string> v;
        v.push_back("压缩饼干");
        v.push_back("芝士面包");
        v.push_back("苦涩浆果");
        v.push_back("巧克力");
        v.push_back("盒装牛奶");
        v.push_back("土豆片");
        v.push_back("花生酱");
        v.push_back("棒棒糖");
        v.push_back("垃圾食品");
        return v;
    }
    static vector<string> initArmorName(){
        vector<string> v;
        v.push_back("警用防弹衣");
        v.push_back("军用头盔");
        v.push_back("荆棘铠甲");
        v.push_back("破损的毛衣");
        v.push_back("帅气的冲锋衣");
        v.push_back("比基尼");
        v.push_back("半身甲");
        v.push_back("笨重的皮大衣");
        return v;
    }
    static vector<string> initWeaponName(){
        vector<string> v;
        v.push_back("猎人匕首");
        v.push_back("猎狐者");
        v.push_back("火焰权杖");
        v.push_back("斯塔提克电刃");
        v.push_back("饮血剑");
        v.push_back("无尽之刃");
        v.push_back("死神镰刀");
        v.push_back("合金指虎");
        v.push_back("棒球球棒");
        v.push_back("双刃斧");
        v.push_back("重力枪");
        return v;
    }
    NPC(Character *p = NULL, std::string name = "NULL", int hp = 0, int damage = 0, int defence = 0, int exp = 0, int money = 0, string prompt = "NULL"):
    name(name), type("普通"), hp(hp), damage(damage), defence(defence), exp(exp), money(money), prompt(prompt), drop(MAXN), player(*p)
    {}
    NPC(const NPC &npc): name(npc.name), type(npc.type), hp(npc.hp), damage(npc.damage),
    defence(npc.defence), exp(npc.exp), money(npc.money), prompt(npc.prompt),
    drop(npc.drop), player(npc.player)
     {}
    NPC &operator=(const NPC &npc){
        name = npc.name;
        type = npc.type;
        hp=npc.hp;
        damage=npc.damage;
        defence=npc.defence;
        exp=npc.exp;
        money=npc.money;
        prompt=npc.prompt;
        drop=npc.drop;
        player=npc.player;
        return *this;
     }
    int insertDrop(Item *item, int num);
    void showDrop();
    int removeDrop(Item *item, int num);
    const std::string getName() const{
        return name;
    }
    int getHp(){
        return hp;
    }
    string getType() const {
        return type;
    }
    Character &getPlayer(){
        return player;
    }
    // 包括一轮player和npc的动作
    Weapon createWeapon(string name = "", string prompt = "");
    Armor createArmor(string name = "", string prompt = "");
    Food createFood(string name = "", string prompt = "");
    int getDropNum(){
        int dropnum = (float)(rand() % 10);
        return dropnum;
    }
    int getWeaponNum(){
        int weaponnum = (float)(rand() % 10 + 10) / 100 * getDropNum();
        return weaponnum;
    }
    int getArmorNum(){
        int armornum = (float)(rand() % 10 + 10) / 100 * getDropNum();
        return armornum;
    }
    int getFoodNum(){
        int foodnum = getDropNum() - getWeaponNum() - getArmorNum();
        return foodnum;
    }
    void renew();

    void attack();
    void defend();
    void useSkill();
    void showStats();

    int fight(int set = 0);
    virtual void interact(int set = 0);
};
#endif