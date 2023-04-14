#ifndef _CHARACTER_HEAD_
#define _CHARACTER_HEAD_
#include <string>
#include <vector>
#include "Inventory.h"
#include "Armor.h"
#include "Weapon.h"
#include "Food.h"
#include "Skill.h"

using namespace std;

class Character: public Inventory{
public:
	Character();
	virtual ~Character();

	void initialize(const std::string name);

	void setLevel(int i){
		level = i;
	}

	inline const int& getMoney() const {
		return money;
	}
	void setMoney(const int num){
		money = num;
	}
	void changeMoney(const int num){
		money += num;
		if(money < 0){
			cout << "你的剩余余额为" << money << endl;
			cout << "你破产了。\n";
			cout << "你的背包被催债人搜刮一空，你也被人打了一顿。\n";
			money = 0;
			clear();
			changeHp(-10);
		}
	}
	/*
	inline const double& getX() const {
		return this->xPos;
	}

	inline const double& getY() const {
		return this->yPos;
	}
	*/

	inline const std::string& getCharacterName() const {
		return this->characterName;
	}

	/*
	inline const std::string& getHonorTitle() const {
		return this->honorTitle;
	}
	*/

	inline const int& getLevel() const {
		return this->level;
	}

	inline const int& getExp() const {
		return this->exp;
	}
	void changeExp(const int num){
		exp += num;
		levelUp();
	}

	inline const int& getExpNext() const {
		return this->expNext;
	}

	inline const int& getHp() const {
		return this->hp;
	}

	void changeHp(const int num){
		hp += num;
		if(hp < 0){
			cout << "你死了。哀悼。\n";
			cout << "你这一生不断与怪物搏杀，你的剑下有" << monsterKilled << "个亡魂\n\n";
			cout << "没有回溯功能，所以只能重新开始了\n";
			system("pause");
			exit(0);
		}else if(hp > maxhp){
			hp = maxhp;
		}
	}

	inline const int& getmaxhp() const {
		return this->maxhp;
	}

	inline const std::string getSkillName(int i) const{
		return skill[i]->getName();
	}

	inline const void setCD(int cd, int i) const{
		if(this->skill[i]->getCD()!=0){
			this->skill[i]->setCD(cd);
		}
	}

	inline void displaySkills() const {
		int cnt = 0;
		for(auto& p: skill){
			cout << cnt << ": ";
			cnt++;
			cout << p->getName() << " ";
		}
	}
	/*
	inline const int& getHunger() const {
		return this->hungerLevel;
	}
	void changeHunger(const int num){
		hungerLevel += num;
	}
	*/

	inline const int& getDamage() const {
		return this->Damage;
	}
	void changeDamage(const int num){
		Damage += num;
	}
	
	inline const int& getDefence() const {
		return this->Defence;
	}


	void changeDefence(const int num){
		Defence += num;
	}

	const Weapon &getWeaponEquip() const{
		return *weaponEquip;
	}

	// Modifier
	// 返回被卸下的武器
	Weapon *equipWeapon(Weapon *w){
		Weapon *tmp = weaponEquip;
		weaponEquip = w;
		return tmp;
	}

	const Armor &getArmorEquip() const{
		return *armorEquip;
	}
	// Modifier
	Armor *equipArmor(Armor *w){
		Armor *tmp = armorEquip;
		armorEquip = w;
		return tmp;
	}

	void showItem();

	std::string getAsString() const;

	void showStats() const;

	// 返回被卸下的物品
	Item *equip(Item *item);

	bool addHP(Item *item){
		if(item->getType() == "食物"){
			Food *food = reinterpret_cast<Food *>(item);
			changeHp(food->getAddhp());
			return 0;
		}
		return 1;
	}

	void levelUp();

	Item *useItem(Item *item);

	void useItemInteract(Item *item);

	void removeItemInteract(Item *item);

	virtual void interact();

	int useSkill(int i);

	inline void displayHP(){
		std::cout << "你的生命值: " << hp << endl;
	}

	inline void addSkillUsed(int i){
		skillUsed.push_back(i);
	}

	inline void eraseSkillUsed(int i){
		int cnt = 0;
		for(std::vector<int>::iterator p = skillUsed.begin();p<skillUsed.end();p++){
			if(cnt==i){
				skillUsed.erase(p);
				break;
			}
			cnt++;
		}
	}
	inline void decreaseCD(){
		for(auto& p: skillUsed){
			skill[p]->setCD(-1);
			if(skill[p]->getCD()==0){
				eraseSkillUsed(p);
			}
			if(p==1&&skill[p]->getCD()==1){
				int tmp = 5 * level + 1;
				tmp = -tmp;
				this->changeDamage(tmp);
			}
		}
	}

	inline void resetCD(){
		for(auto& p:skillUsed){
			skill[p]->setCD(-(skill[p]->getCD()));
		}
	}

	inline void addMonsterKilled(){
		monsterKilled++;
	}

private:


	std::string characterName;

	int level;
	int exp;
	//Exp to next level
	int expNext;
	int hp;
	int maxhp;
	// int hungerLevel;
	int Damage;
	int Defence;
	//Equipment
	Weapon *weaponEquip;
	Armor *armorEquip;

	int money;

	std::vector<Skill *> skill;
	std::vector<int> skillUsed;

	int monsterKilled;
};

#endif