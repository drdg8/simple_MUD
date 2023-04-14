#include "Character.h"
#include <iomanip>
#include <iostream>
#include <math.h>

vector<int> v(4);
Armor noArmor;
Weapon noWeapon(v);
Skill heal("暂时休眠", 0);
Skill rage("怒吼", 1);

Character::Character()
{
	characterName = "";
	hp = 40;
	maxhp = 40;
	// hungerLevel = 100;
	Damage = 5;
	Defence = 1;
	armorEquip = &noArmor;
	weaponEquip = &noWeapon;
}

Character::~Character()
{
}

void Character::initialize(const std::string name)
{
	// xPos = 0;
	// yPos = 0;
	characterName = name;
	// honorTitle = "Rookie";
	level = 1;
	exp = 0;
	expNext = level * 50;
	hp = 40;
	maxhp = 40;
	// hungerLevel = 100;
	Damage = 5;
	Defence = 1;
	money = 100;
	armorEquip = &noArmor;
	weaponEquip = &noWeapon;
	skill.push_back(&heal);
	skill.push_back(&rage);
	monsterKilled = 0;
}

void Character::showStats() const
{
	std::cout << "== 角色表 ==" << std::endl;
	std::cout << "||名字: " << characterName << std::endl;
	std::cout << "||等级: " << level << std::endl;
	std::cout << "||经验: " << exp << std::endl;
	std::cout << "||升级经验: " << expNext << std::endl;
	std::cout << "||HP: " << hp << std::endl;
	cout << "||最大生命值：" << maxhp << endl;
	cout << "||金钱：" << money << endl;
	std::cout << "||攻击: " << Damage << std::endl;
	std::cout << "||防御: " << Defence << std::endl;
	std::cout << "||技能:\n" ;
	
	this->displaySkills();
	std::cout << endl;
	std::cout << "||武器: " << weaponEquip->getName() << std::endl;
	std::cout << "||防具: " << armorEquip->getName() << std::endl;
	cout << "-----------------" << endl;
}

std::string Character::getAsString() const
{
	return characterName + " " + std::to_string(level) + " " + std::to_string(exp) + " " + std::to_string(Damage) + " " + std::to_string(Defence);
}

void Character::levelUp()
{
	while (exp >= expNext)
	{
		exp -= expNext;
		level++;
		expNext = level * 50;
		maxhp += 5 + level * 2;
		hp = maxhp;
		Damage += 2 + level * 3 / 2;
		Defence += 1 + level;
		money += 50 + level * 30;
		changeCapacity(2);
		cout << "恭喜你升级了。\n";
		showStats();
	}
}

void Character::showItem()
{
	std::cout << "你翻了翻背包。\n";
	if (size == 0)
	{
		std::cout << std::endl;
		std::cout << "真不走运，啥都没有。" << std::endl;
		std::cout << "--------------" << std::endl;
		return;
	}
	int index = 0;
	std::map<Item *, int>::iterator p;
	for (p = bag.begin(); p != bag.end(); p++)
	{
		std::cout << "序号:" << index++ << " 名称:"
				  << p->first->getName() << " 数量:" << p->second << std::endl;
	}
	std::cout << "--------------" << std::endl;
}

Item *Character::equip(Item *item)
{
	string type = item->getType();
	if (type == "武器")
	{
		Weapon *weapon = reinterpret_cast<Weapon *>(item);
		Weapon *ret = equipWeapon(weapon);
		// cout << "成功装备" << item->getName() << endl;
		return ret;
	}
	else if (type == "防具")
	{
		Armor *armor = reinterpret_cast<Armor *>(item);
		Armor *ret = equipArmor(armor);
		// cout << "成功装备" << item->getName() << endl;
		return ret;
	}
	else
	{
		// cout << "传入的物品不能装备\n";
		return nullptr;
	}
}

Item *Character::useItem(Item *item)
{
	Item *tmp;
	if (tmp = equip(item))
	{
		cout << "成功装备" << item->getName() << endl;
		return tmp;
	}
	else if (addHP(item) == 0)
	{
		cout << "成功回血，现在血量为:" << hp << endl;
		return nullptr;
	}
	else
	{
		cout << "传入物品无法使用\n";
		return nullptr;
	}
}

// 使用背包中的物品
void Character::useItemInteract(Item *item)
{
	if (item->getType() == "食物")
	{
		int num;
		cout << "请输入所使用的数量, -1退出\n";
		cout << "-------------------\n";
		while (cin >> num){
			cout << "\n\n\n";
			if (num == -1){
				break;
			}
			else if (num < 0 || num > getNum(item)){
				cout << "请输入正确数量\n";
			}
			else
			{
				int leave = removeItem(item, num);
				if (leave < num)
				{
					cout << "数量不够，已将背包内此种物品用完\n";
				}
				for (; leave > 0; leave--)
				{
					useItem(item);
				}
				cout << "-------------\n";
				cout << "你现在血量为" << getHp() << endl;
				break;
			}
		}
	}
	else if (item->getType() == "防具" || item->getType() == "武器")
	{
		Item *tmp = useItem(item);
		removeItem(item, 1);
		if (tmp->getName() != "NONE")
			addItem(tmp, 1);
	}
	cout << "---------------------\n";
}

void Character::removeItemInteract(Item *item)
{
	int num;
	cout << "请输入所丢弃的数量, -1退出\n";
	cout << "-------------------\n";
	while (cin >> num)
	{
		cout << "\n\n\n";
		if (num == -1)
		{
			break;
		}
		else if (num < 0 || num > getNum(item))
		{
			cout << "请输入正确数量\n";
		}
		else
		{
			int leave = removeItem(item, num);
			if (leave < num)
			{
				cout << "数量不够，已将背包内所有此种物品丢弃\n";
			}
			else
			{
				cout << "已丢弃" << num << "个物品\n";
			}
			break;
		}
	}
	cout << "---------------------\n";
}

/*
string type = item->getType();
int choice;
if(type == "武器"){
	Weapon *weapon = reinterpret_cast<Weapon *>(item);
	cout << "请选择你的操作\n";
	cout << "0.查看属性 1.装备 -1.退出\n";
	cout << "-----------------------\n";
	while(cin >> choice){
		cout << "\n\n\n";
		if (choice == -1)
			break;
		else if (choice < 0 || choice > 1){
			cout << "请输入正确的序号\n";
		}else if(choice == 0){
			weapon->showAtribute();
		}else if(choice == 1){
			equipWeapon(*weapon);
		}
	}
}else if(type == "防具"){
	Armor *armor = reinterpret_cast<Armor *>(item);
	cout << "请选择你的操作\n";
	cout << "0.查看属性 1.装备 -1.退出\n";
	cout << "-----------------------\n";
	while(cin >> choice){
		cout << "\n\n\n";
		if (choice == -1)
			break;
		else if (choice < 0 || choice > 1){
			cout << "请输入正确的序号\n";
		}else if(choice == 0){
			armor->showAtribute();
		}else if(choice == 1){
			equipArmor(*armor);
		}
	}
}
*/

void Character::interact()
{
	std::cout << "你看了看自己。\n";
	std::cout << "选择想做的操作。\n";
	std::cout << "0.查看个人面板 1.查看背包 2.查看或使用或丢弃背包物品 -1.退出\n";
	cout << "-------------------------------------\n";
	int cho;
	while (std::cin >> cho)
	{
		cout << "\n\n\n";
		if (cho == -1)
		{
			break;
		}
		else if (cho == 0)
		{
			showStats();
		}
		else if (cho == 1)
		{
			showItem();
		}
		else if (cho == 2)
		{
			showItem();
			cout << "请输入物品所对应的序号。-1:退出。\n";
			cout << "-----------------------\n";
			int cho1;
			while (cin >> cho1)
			{
				cout << "\n\n\n";
				if (cho1 == -1)
				{
					break;
				}
				if (cho1 < 0 || cho1 >= getIndex())
				{
					std::cout << "请输入有效数字。\n";
					continue;
				}
				else
				{
					Item *item = selectItem(cho1);
					int cho2;
					cout << "选择想做的操作。\n";
					cout << "0.查看物品 1.使用物品 2.丢弃物品 -1.退出\n";
					cout << "-------------------------------------\n";
					while (cin >> cho2)
					{
						cout << "\n\n\n";
						if (cho2 == -1)
							break;
						else if (cho2 == 0)
						{
							itemShow(item);
						}
						else if (cho2 == 1)
						{
							useItemInteract(item);
							break;
						}
						else if (cho2 == 2)
						{
							removeItemInteract(item);
							break;
						}
						cout << "选择想做的操作。\n";
						cout << "0.查看物品 1.使用物品 2.丢弃物品 -1.退出\n";
						cout << "-------------------------------------\n";
					}
				}
				showItem();
				cout << "请输入物品序号来选择物品进行操作(-1退出)\n";
				cout << "--------------------\n";
			}
		}
		else
		{
			std::cout << "请输入有效数字。\n";
		}
		std::cout << "0.查看个人面板 1.查看背包 2.查看或使用或丢弃背包物品 -1.退出\n";
		cout << "---------------------------\n";
	}
	cout << "--------------------\n";
}

int Character::useSkill(int i)
{
	if (i == 0)
	{
		if (skill[i]->getCD() == 0)
		{
			std::cout << "你使用了技能: " << skill[i]->getName() << std::endl;
			int hpAdd = 5 * level + 1;
			std::cout << "你的生命值恢复了" << hpAdd << std::endl;
			this->changeHp(hpAdd);
			this->skill[i]->setCD(3);
			this->addSkillUsed(i);
			return hpAdd;
		}
		else
		{
			std::cout << "完了，技能还在冷却中! 还有" << skill[i]->getCD() << "回合才能使用" << endl
					  << endl;
			return 0;
		}
	}
	else if(i==1){
		if (skill[i]->getCD() == 0)
		{
			std::cout << "你使用了技能: " << skill[i]->getName() << std::endl;
			int attackAdd = 5 * level + 1;
			std::cout << "你的攻击力提高了: " << attackAdd << " ,该buff在2回合后消失" << std::endl;
			this->changeDamage(attackAdd);
			this->skill[i]->setCD(3);
			this->addSkillUsed(i);
			return attackAdd;
		}
		else
		{
			std::cout << "完了，技能还在冷却中! 还有" << skill[i]->getCD() << "回合才能使用" << endl
					  << endl;
			return 0;
		}
	}
}