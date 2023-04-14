#include "Armor.h"
#include <string>
#include <iostream>
Armor::Armor(int defenceAtt, int defenceDef, std::string name, std::string description, std::string type, int level, int buyValue, int sellValue, int rarity)
    :Item(name, description, type, level, buyValue, sellValue , rarity),defenceAtt(defenceAtt), defenceDef(defenceDef)
{} 

Armor::~Armor(){}

std::string Armor::toString(){
    std::string ret = std::to_string(this->defenceAtt) + " " + to_string(defenceDef);
    return ret;
}

void Armor::showAtribute(){
	std::cout << "== 物品表 ==" << std::endl;
	std::cout << "||名字: " << name << std::endl;
	std::cout << "||类别: " << type << std::endl;
	std::cout << "||防御: " << toString() << std::endl;
	std::cout << "||等级: " << level << std::endl;
	std::cout << "||稀有度: " << rarity << std::endl;
    cout << description << endl;
    cout << "-----------------" << endl;
}

void Armor::interact(){
    // 好像没什么必要
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
    