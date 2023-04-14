#include "NPC.h"

// 存储随机生成事物
vector<Armor> armor_vec;
vector<Food> food_vec;
vector<Weapon> weapon_vec;

int NPC::insertDrop(Item *item, int num){
    return drop.addItem(item, num);
}

void NPC::showDrop(){
    cout << "展示掉落物品\n";
    drop.showItem();
}

int NPC::removeDrop(Item *item, int num){
    return drop.removeItem(item, num);
}

void NPC::showStats(){
	std::cout << "== NPC 表 ==" << std::endl;
	std::cout << "||名字: " << name << std::endl;
	std::cout << "||经验: " << exp << std::endl;
	std::cout << "||HP: " << hp << std::endl;
	std::cout << "||攻击: " << damage << std::endl;
	std::cout << "||防御: " << defence << std::endl;
	cout << "-----------------" << endl;
}

Weapon NPC::createWeapon(string name, string prompt){
	static int Weaponnum = 0;
	Weaponnum++;
	float level = player.getLevel();
	if(level < 2)
		level = 2;
	float ratio = 1.0 / 6 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (level / 7 - 1.0 / 6)));
    int random = rand()%10;
	name = weaponNames[random];
    int level1;
    for(level1 = 1; level1 < 99; level1++){
		if (ratio < (float)level1 / 3){
			break;
		}
	}
	int buyValue = 10 * level * pow(level1, 1.5);
	int newdamage = (int)(player.getDamage() * ratio);
    if(newdamage < 1)
        newdamage = 1;
    int maxDamage = (float)(rand() % 20 + 20) / 20 * newdamage;
	int minDamage = (float)(rand() % 10 + 10) / 20 * newdamage;
    vector<int> special(4);
    for (int i = 0; i < special.size(); i++){
        random = rand() % 100;
        if(random < 1){
            special[i] = 5;
            buyValue += 5 * level;
        }else if (random < 3){
            special[i] = 4;
            buyValue += 10 * level;
        }else if (random < 6){
            special[i] = 3;
            buyValue += 15 * level;
        }else if (random < 10){
            special[i] = 2;
            buyValue += 20 * level;
        }else if (random < 15){
            special[i] = 1;
            buyValue += 25 * level;
        }
    }
	int sellValue = buyValue / 2;
    return Weapon(special, maxDamage, minDamage, name, prompt, string("武器"), level1, buyValue, sellValue, 1);
}

Armor NPC::createArmor(string name, string prompt){
	static int Armornum = 0;
	Armornum++;
	float level = player.getLevel();
	if(level < 2)
		level = 2;
	float ratio = 1.0 / 6 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (level / 7 - 1.0 / 6)));
    int random = rand()%8;
    name = armorNames[random];
    int level1;
    for(level1 = 1; level1 < 99; level1++){
		if (ratio < (float)level1 / 3){
			break;
		}
	}
	int buyValue = 10 * level * pow(level1, 1.5);
	int sellValue = buyValue / 2;
	int defence = (int)(player.getDefence() * ratio);
    if(defence < 1)
        defence = 1;
    int defenceAtt = (float)(rand() % 20 + 20) / 20 * defence;
	int defenceDef = (float)(rand() % 10 + 10) / 20 * defence;
	return Armor(defenceAtt, defenceDef, name, prompt, string("防具"), level1, buyValue, sellValue, 1);
}
vector<string> NPC::foodNames = initFoodName();
vector<string> NPC::weaponNames = initWeaponName();
vector<string> NPC::armorNames = initArmorName();

Food NPC::createFood(string name, string prompt){
	static int Foodnum = 0;
	Foodnum++;
    float level = player.getLevel();
	float ratio = 1.0 / 6 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.0/2 - 1.0 / 6)));
    int random = rand() % 8;
    name = foodNames[random];
    /* if(name == ""){
		name = "Food" + to_string(Foodnum);
	} */
    int level1;
	for(level1 = 1; level1 < 99; level1++){
		if (ratio < (float)level1 / 6){
			break;
		}
	}
	int buyValue = 2 * level * pow(level1, 1.5);
	int sellValue = buyValue / 2;
	int addhp = (int)(player.getmaxhp() * ratio);
	return Food(addhp, name, prompt, string("食物") , level1, buyValue, sellValue, 1);
}

void NPC::renew(){
    for (int j = 0; j < getFoodNum(); j++){
        Food tmp_food = createFood();
        food_vec.push_back(tmp_food);
        insertDrop(&food_vec.back(), 1);
    }
    for (int j = 0; j < getArmorNum(); j++){
        Armor tmp_armor = createArmor();
        armor_vec.push_back(tmp_armor);
        insertDrop(&armor_vec.back(), 1);
    }
    for (int j = 0; j < getWeaponNum(); j++){
        Weapon tmp_weapon = createWeapon();
        weapon_vec.push_back(tmp_weapon);
        insertDrop(&weapon_vec.back(), 1);
    }
}

void NPC::attack(){
    vector<int> set(3);
    int sumdamage = 0;
    cout << "你进行了攻击\n";
    cout << "你的初始攻击力是" << player.getDamage() << endl;
    if(player.getWeaponEquip().getName() == "NONE"){
        cout << "未装备武器，武器伤害为0\n";
    }else{
        int weaponDamage = player.getWeaponEquip().getDamage(set);
        sumdamage += weaponDamage;
        while(set[2] == 1){
            set[2] = 0;
            if(set[1] == 1){
                player.changeHp(weaponDamage * 0.6);
            }
            sumdamage += player.getWeaponEquip().getDamage(set);
        }
        if(set[1] == 1){
            player.changeHp(weaponDamage * 0.6);
        }
        cout << "使用武器造成的攻击伤害为" << sumdamage << endl;
    }
    cout << "对手的防御力是" << defence << endl;
    int NPCSub = player.getDamage() + sumdamage - defence;
    if(NPCSub <= 0){
        cout << "你没有破开" << name << "的防御\n";
    }else{
        cout << "你对" << name << "造成" << NPCSub << "伤害\n";
        hp -= NPCSub;
    }
    if(hp < 0)
        return;
    if(set[0]){
        player.decreaseCD();
        cout << "--------------------\n";
        return;
    }

    cout << "\n\n";
    cout << "你的初始防御力是" << player.getDefence() << endl;
    int defenceAtt = player.getArmorEquip().getDefenceAtt();
    cout << "攻击时你的防具防御为" << defenceAtt << endl;
    cout << "对手的攻击力是" << damage << endl;
    int playerSub = damage - player.getDefence() - player.getArmorEquip().getDefenceAtt();
    if(playerSub <= 0){
        cout << name <<  "没有破开你的防御\n";
    }else{
        player.changeHp(-playerSub);
        cout << name <<  "对你造成" << playerSub << "伤害\n";
    }
    player.decreaseCD();
    cout << "--------------------\n";
}

void NPC::useSkill(){
    cout << "\n\n";
    cout << "你要使用哪个技能？\n";
    player.displaySkills();
    int choice;
    while(cin >> choice){
        if(choice<2){
            player.useSkill(choice);
            break;
        }
        else{
            cout << "你只有两个技能，请重新输入\n";
        }
    }
}

void NPC::defend(){
    cout << "你摆出了防御姿态\n";
    cout << "你的初始防御力是" << player.getDefence() << endl;
    int defenceDef = player.getArmorEquip().getDefenceDef();
    cout << "防御时你的防具防御为" << defenceDef << endl;
    cout << "对手的攻击力是" << damage << endl;
    int playerSub = damage - player.getDefence() - player.getArmorEquip().getDefenceDef();
    if(playerSub < 0){
        cout << name <<  "没有破开你的防御\n";
    }else{
        player.changeHp(-playerSub);
        cout << name <<  "对你造成" << playerSub << "伤害\n";
    }

    vector<int> set(3);
    int sumdamage = 0;
    cout << "--------------------\n\n\n";
    cout << "你对其进行了反击\n";
    cout << "你的初始攻击力是" << player.getDamage() << endl;
    if(player.getWeaponEquip().getName() == "NONE"){
        cout << "未装备武器，武器伤害为0\n";
    }else{
        int weaponDamage = player.getWeaponEquip().getDamage(set) / 2;
        sumdamage += weaponDamage;
        while(set[2] == 1){
            set[2] = 0;
            if(set[1] == 1){
                player.changeHp(weaponDamage * 0.6);
            }
            sumdamage += player.getWeaponEquip().getDamage(set) / 2;
        }
        if(set[1] == 1){
            player.changeHp(weaponDamage * 0.6);
        }
        cout << "使用武器造成的反击伤害为" << sumdamage << endl;
    }
    cout << "对手的防御力是" << defence << endl;
    int NPCSub = player.getDamage() + sumdamage - defence;
    if(NPCSub <= 0){
        cout << "你没有破开" << name << "的防御\n";
    }else{
        cout << "你对" << name << "造成" << NPCSub << "伤害\n";
        hp -= NPCSub;
    }
    player.decreaseCD();
}

int NPC::fight(int set){
    cout << "开始战斗!\n";
    int choice;
    int is_run = 0;
    while(hp > 0){
        cout << "你打算怎么做？\n";
        cout << "0.看看自己 1.攻击 2.防御 3.技能 4.逃跑\n";
        cout << "--------------------\n";
        while(cin >> choice){
            cout << "\n\n\n";
            if(choice < 0 || choice > 4){
                cout << "请输入正确的数字\n";
            }else if(choice == 4){
                if(set == 1){
                    cout << "你没有逃跑的时机\n";
                    break;
                }
                cout << "虽然逃跑不可耻，但你还是跑了。\n";
                cout << "--------------------\n";
                is_run = 1;
                player.resetCD();
                break;
            }else if(choice == 0){
                player.interact();
                break;
            }else if(choice == 1){
                attack();
                break;
            }else if (choice == 2){
                defend();
                break;
            }else if (choice == 3){
                useSkill();
                break;
            }
        }
        if(is_run){
            break;
        }
    }
    if(is_run == 0){
        player.resetCD();
        player.addMonsterKilled();
        cout << "--------------------\n";
        cout << "恭喜，你打败了" << name << endl;
        player.changeMoney(money);
        cout << "你获得了" << money << "元\n";
        cout << "你获得了" << exp << "经验值\n";
        player.changeExp(exp);
        cout << "战利品有以下这些:\n";
        cout << "--------------------\n";
        showDrop();
        cout << "请输入物品序号来选择物品进行操作(-1退出)\n";
        cout << "--------------------\n";
        while(cin >> choice){
            cout << "\n\n\n";
            if(choice == -1 ){
                break;
            }else if(choice >= drop.getIndex() || choice < 0){
                cout << "请输入正确的序号\n";
            }else{
                Item *item = drop.selectItem(choice);
                int choice1;
                cout << "请选择想进行的操作：\n";
                cout << "0.查看 1.使用 2.装入背包(-1退出)\n";
                cout << "--------------------\n";
                while(cin >> choice1){
                    cout << "\n\n\n";
                    if(choice1 == -1 ){
                        break;
                    }else if(choice1 < 0 || choice1 > 2){
                        cout << "请输入正确的序号\n";
                        continue;
                    }else if(choice1 == 0){
                        player.itemShow(item);
                    }else if(choice1 == 1){
                        // 这里不用interactItem的原因是其并不在背包中
                        int num;
                        cout << "请输入数量，最多为" << drop.getNum(item) << "\n";
                        cout << "--------------------\n";
                        while(cin >> num){
                            cout << "\n\n\n";
                            if(num < 0 || num > drop.getNum(item)){
                                cout << "请输入正确的数量\n";
                            }else{
                                for (int i = 0; i < num; i++){
                                    player.useItem(item);
                                }
                                removeDrop(item, num);
                                break;
                            }
                        }
                        break;
                    }else if(choice1 == 2){
                        int num;
                        cout << "请输入数量，最多为" << drop.getNum(item) << "\n";
                        cout << "--------------------\n";
                        while(cin >> num){
                            cout << "\n\n\n";
                            if(num < 0 || num > drop.getNum(item)){
                                cout << "请输入正确的数量\n";
                            }else{
                                int left = player.addItem(item, num);
                                if(left > 0){
                                    cout << "背包容量已满，自动插入最多数量\n";
                                }
                                drop.removeItem(item, num - left);
                                cout << "装入背包成功\n";
                                cout << "------------------------\n";
                                player.showItem();
                                break;
                            }
                        }
                        break;
                    }
                    cout << "0.查看 1.使用 2.装入背包(-1退出)\n";
                    cout << "--------------------\n";
                }
            }
            showDrop();
            cout << "请输入物品序号来选择物品进行操作(-1退出)\n";
            cout << "--------------------\n";
        }
    }
    cout << "-------------------\n";
    return is_run;
}

void NPC::interact(int set){
    cout << name << "。" << endl;
    cout << prompt << endl;
    if(hp < 0){
        cout << "TA已经死了。彻彻底底。\n";
        cout << "----------------\n\n";
        return;
    }
    std::cout << "你打算怎么对TA？" << std::endl;
    std::cout << "不管你怎么想，TA已经冲过来了。" << std::endl;
    // 切入战斗系统
    int flag = fight(set);
    if(flag == 0){
        cout << "你成功打败了TA.\n";
        cout << "--------------------\n";
    }
}