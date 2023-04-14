#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"
#include <iostream>
#include <vector>
class Weapon : public Item
{
private:
    int damageMax;
    int damageMin;

    // 电刃 连击
    // 吸血 增加自身血量 伤害25%
    // 震慑 30%对手无法还击
    // 毒 增加伤害25%
    vector<int> special;

public:
    Weapon(vector<int> speciel , int damageMax = 0, int damageMin = 0, std::string name = "NONE", std::string description = "NONE", std::string type = "Weapon", int level = 0, int buyValue = 0, int sellValue = 0, int rarity = 0);
    virtual ~Weapon();

    //Functions
    std::string toString();

    void interact();

    // set = 0 对手无法攻击， 1 吸血, 2 连击
    int getDamage(vector<int>&set) const {
        int sum = 0;
        int d1 = rand() % (damageMax - damageMin + 1) + damageMin;
        sum += d1;
        // 暴击 20% 造成两倍伤害
        int ratio = rand() % 10;
        if(ratio < 2){
            cout << "造成暴击伤害！:" << d1 << "\n";
            sum += d1;
        }
        for (int i = 0; i < special.size(); i++){
            int tmp = special[i];
            if(tmp){
                if(i == 0){
                    // 毒 1-5 -> 20% - 40%
                    int tmp1 = d1 * (float)(rand() % 10 + 10 + tmp * 5) / 100;
                    cout << "刀上的淬毒悄悄渗入, 伤害: " << tmp1 << endl;
                }else if(i == 1){
                    // 震慑 1-5 -> 15% - 35%
                    ratio = rand() % 100;
                    if(ratio < tmp * 5 + 10){
                        cout << "势大力沉, 震慑住敌人了！其本回合不能攻击。\n";
                        set[0] = 1;
                    }
                }else if(i == 2){
                    // 吸血 1-5 -> 15% - 35%
                    // 吸取伤害的60%
                    ratio = rand() % 100;
                    if(ratio < tmp * 5 + 10){
                        cout << "对手的鲜血正被吸收！\n";
                        set[1] = 1;
                    }
                }else if(i == 3){
                    // 电刃 1-5 -> 15% - 35%
                    ratio = rand() % 100;
                    if(ratio < tmp * 5 + 10){
                        cout << "电刃的连击！再次攻击。\n";
                        set[2] = 1;
                    }
                }
            }
        }
        return sum;
    }

    int getSpecial(int ind){
        return special[ind];
    }

    void showAtribute();
    //void equip(Character &player);

    //friend void Character::equip(Weapon &w);
    //friend class Game;
};

#endif