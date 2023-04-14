#include "Trader.h"

int Trader::insertSell(Item *item, int num){
    // std::cout << "上架商品:" << item->getName() << " 数量为:" << num << std::endl;
    return sell.addItem(item, num);
}

void Trader::showSell(){
    std::cout << "展示上架的商品\n";
    sell.showItem();
}

int Trader::removeSell(Item *item, int num){
    // std::cout << "下架商品:" << item->getName() << " 数量为:" << num << std::endl;
    return sell.removeItem(item, num);
}

void Trader::renewSell(){
    sell.clear();
    for (int j = 0; j < getFoodNum(); j++){
        Food tmp_food = createFood();
        // cout << tmp_food.getName() << "更新成功\n";
        food_vec.push_back(tmp_food);
        insertSell(&food_vec.back(), 1);
    }
    for (int j = 0; j< getArmorNum(); j++){
        Armor tmp_armor = createArmor();
        armor_vec.push_back(tmp_armor);
        insertSell(&armor_vec.back(), 1);
    }
    for (int j = 0; j< getWeaponNum(); j++){
        Weapon tmp_weapon = createWeapon();
        weapon_vec.push_back(tmp_weapon);
        insertSell(&weapon_vec.back(), 1);
    }
}

void Trader::goBuy(){
    int ind;
    player.showItem();
    cout << "选择你想要卖出的物品序号:(-1退出)" << std::endl;
    cout << "--------------------\n";
    while(std::cin >> ind){
        cout << "\n\n\n";
        if(ind == -1)
            break;
        if(ind >= player.getIndex() || ind < 0){
            std::cout << "请输入正确的序号" << std::endl;
        }else{
            Item *sellObj = player.selectItem(ind);
            assert(player.getNum(sellObj) != -1);
            std::cout << "想要卖出的是:" << sellObj->getName() << std::endl;
            std::cout << "单价为:" << sellObj->getSellValue() << std::endl;
            std::cout << "请输入卖出数量(-1退出):" << std::endl;
            cout << "--------------------\n";
            int num;
            while(std::cin >> num){
                cout << "\n\n\n";
                if(num == -1)
                    break;
                if(num <= player.getNum(sellObj) && num > 0){
                    player.changeMoney(sellObj->getSellValue() * num);
                    player.removeItem(sellObj, num);
                    cout << "--------------------\n";
                    player.showItem();
                    cout << "--------------------\n";
                    std::cout << "成功卖出" << num << "件商品" << std::endl;
                    cout << "还剩下" << player.getMoney() << "元\n";
                    cout << "--------------------\n";
                    break;
                }else{
                    std::cout << "请输入正确数量" << std::endl;
                    continue;
                }
                std::cout << "想要卖出的是:" << sellObj->getName() << std::endl;
                std::cout << "单价为:" << sellObj->getSellValue() << std::endl;
                std::cout << "请输入卖出数量(-1退出):" << std::endl;
                cout << "--------------------\n";
            }
        }
        player.showItem();
        cout << "选择你想要的卖出物品序号:(-1退出)" << std::endl;
        cout << "--------------------\n";
    }
    cout << "-----------------------\n";
}

void Trader::goSell(){
    int ind;
    showSell();
    cout << "选择你想要购买的物品序号:(-1退出)" << std::endl;
    cout << "--------------------\n";
    while(std::cin >> ind){
        cout << "\n\n\n";
        if(ind == -1)
            break;
        if(ind >= sell.getIndex() || ind < 0){
            std::cout << "请输入正确的序号" << std::endl;
        }else{
            Item *sellObj = sell.selectItem(ind);
            assert(sell.getNum(sellObj) != -1);
            std::cout << "想要购买的是:" << sellObj->getName() << std::endl;
            std::cout << "单价为:" << sellObj->getBuyValue() << std::endl;
            std::cout << "请输入购买数量(-1退出):" << std::endl;
            cout << "--------------------\n";
            int num;
            while(std::cin >> num){
                cout << "\n\n\n";
                if(num == -1)
                    break;
                if(num <= sell.getNum(sellObj) && num > 0){
                    int playermoney = player.getMoney();
                    int totalmoney = sellObj->getBuyValue() * num;
                    if(playermoney < totalmoney){
                        std::cout << "玩家金钱为:" << playermoney << std::endl;
                        std::cout << "所需金钱为:" << totalmoney << std::endl;
                        std::cout << "余额不足" << std::endl;
                        cout << "---------------------\n";
                        break;
                    }
                    int cap = player.getCapacity();
                    int size = player.getSize();
                    if(cap - size < num){
                        std::cout << "包容量为:" << cap << std::endl;
                        std::cout << "包内物品量为:" << size << std::endl;
                        std::cout << "包内容量不足" << std::endl;
                        cout << "---------------------\n";
                        break;
                    }
                    sell.removeItem(sellObj, num);
                    player.changeMoney(-sellObj->getBuyValue() * num);
                    player.addItem(sellObj, num);
                    cout << "--------------------\n";
                    player.showItem();
                    cout << "--------------------\n";
                    std::cout << "成功购买" << num << "件商品" << std::endl;
                    cout << "还剩下" << player.getMoney() << "元\n";
                    cout << "--------------------\n";
                    break;
                }else{
                    std::cout << "请输入正确数量" << std::endl;
                }
                std::cout << "想要购买的是:" << sellObj->getName() << std::endl;
                std::cout << "单价为:" << sellObj->getBuyValue() << std::endl;
                std::cout << "请输入购买数量(-1退出):" << std::endl;
                cout << "--------------------\n";
            }
        }
        showSell();
        cout << "选择你想要购买的物品序号:(-1退出)" << std::endl;
        cout << "--------------------\n";
    }
    cout << "-----------------------\n";
}

void Trader::interact(){
    cout << "TA是" << name << "。\n";
    cout << prompt << endl;
    if (hp <= 0){
        cout << "TA已经在天堂了。还是不要打扰TA为好。\n";
        return;
    }
    std::cout << "你可以输入想做的操作。" << std::endl;
    std::cout << "-1: 退出 0: 攻击 1: 买入物品 2: 卖出物品 3:查看自身"<< std::endl;
    if(name == "旅店老板娘"){
        cout << "当然你也可以睡一晚。4: 睡觉\n";
    }
    cout << "--------------------\n";
    int cho;
    int flag = 1;
    while(std::cin >> cho){
        cout << "\n\n\n";
        if(cho == -1){
            break;
        }else if(cho == 0){
            cout << "忘了说了，最好别攻击商人，谁知道他们有多强XD\n";
            flag = fight();
            if(flag == 0){
                cout << "你干掉了" << name << endl;
                break;
            }
        }else if(cho == 1){
            goSell();
        }else if(cho == 2){
            goBuy();
        }else if(cho == 3){
            player.interact();
        }else if(cho == 4){
            if(name == "旅店老板娘"){
                cout << "你度过了甜美的一晚。\n" << endl;
                cout << "你支付了30元，获得了充足的睡眠。\n";
                player.changeMoney(-30);
                player.changeHp(player.getmaxhp() / 5);
            }
        }
        std::cout << "你可以输入想做的操作。"<< std::endl;
        std::cout << "-1: 退出 0: 攻击 1: 买入物品 2: 卖出物品 3:查看自身"<< std::endl;
        cout << "--------------------\n";
    }
    if(flag == 0){
        // help();
    }
    cout << "-----------------\n";
}

#ifdef _TEST_TRADER_
// g++ 'Trader.cpp' 'Character.cpp' 'Item.cpp' 'NPC.cpp' 'Inventory.cpp' -o 'Trader.exe' -Wall -O2 -m64 -static-libgcc -fexec-charset=GBK ; if ($?) { &'./Trader.exe' }
int main(){
    Character p1;
    p1.initialize("Tom");
    // name, hp, damage, defence, exp
    Trader t1("邱总", 100, 10, 6, 60);
    Trader t2("小刘", 120, 10, 7, 70);
	// name, description, type, level, buyValue, sellValue, rarity
    Item cookie("饼干", "感觉已经变质了。", "食物", 1, 10, 5, 1);
    Item water("纯净水", "谁知道纯不纯净。", "食物", 1, 10, 5, 1);
    t1.insertSell(&cookie, 5);
    t2.insertSell(&water, 5);
    t1.goSell(p1);
    t2.goSell(p1);
    p1.showItem();
}

#endif