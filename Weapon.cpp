#include "Weapon.h"
#include "Game.h"
#include "Character.h"
#include <string>

Weapon::Weapon(vector<int> special, int damageMax, int damageMin, std::string name, std::string description, std::string type, int level, int buyValue, int sellValue, int rarity)
    :Item(name, description, type,level, buyValue, sellValue , rarity),damageMax(damageMax),damageMin(damageMin), special(special)
{} 

Weapon::~Weapon(){}

void Weapon::showAtribute(){
	std::cout << "== 物品表 ==" << std::endl;
	std::cout << "||名字: " << name << std::endl;
	std::cout << "||类别: " << type << std::endl;
	std::cout << "||攻击力: " << toString() << std::endl;
	std::cout << "||等级: " << level << std::endl;
	std::cout << "||稀有度: " << rarity << std::endl;
    for (int i = 0; i < special.size(); i++){
        int tmp = special[i];
        if(tmp){
            if(i == 0){
                cout << "||淬毒: " << tmp << endl;
            }else if(i == 1){
                cout << "||震慑: " << tmp << endl;
            }else if(i == 2){
                cout << "||吸血: " << tmp << endl;
            }else if(i == 3){
                cout << "||电刃: " << tmp << endl;
            }
        }
    }
    cout << description << endl;
    cout << "-----------------" << endl;
}

std::string Weapon::toString(){
    std::string ret = std::to_string(this->damageMax) + "-" + std::to_string(this->damageMin);
    return ret;
}


void Weapon::interact(){
    cout << "其名为" << name << ", 是:" << type << endl;
    cout << description << endl;
    cout << "请输入想做的动作:\n";
    std::cout << "-1: 退出 0: 查看"<< std::endl;
    cout << "--------------------\n";
    int cho;
    while(std::cin >> cho){
        cout << "\n\n\n";
        if(cho == -1){
            break;
        }else if(cho == 0){
            showAtribute();
            break;
        }
    }
}    
    
