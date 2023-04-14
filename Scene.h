#ifndef _SCENE_HEAD_
#define _SCENE_HEAD_

#include <iostream>
#include <string>
#include <vector>

#include "Item.h"
#include "Trader.h"

using namespace std;



// buy等操作用NPC类完成
class Scene{
private:
    std::string place;
    std::string prompt;
    std::vector<Scene *> go;
    // contain 没有用上。
    Inventory contain;

    vector<NPC> npc_vec;
    vector<Trader> trader_vec;
    static vector<string> monsterNames;
public:
   
    
    static vector<string> init(){
        vector<string> v;
        v.push_back("丧尸");
        v.push_back("地狱犬");
        v.push_back("舔食者");
        v.push_back("猎杀者");
        v.push_back("追击者");
        v.push_back("吸血鬼");
        v.push_back("狼人");
        v.push_back("行刑者");
        v.push_back("蒂米库雷斯特夫人");
        return v;
    }
    
    Scene(std::string place, std::string prompt):
        place(place), prompt(prompt), contain(MAXN)
        {}
    string getPlace(){
        return place;
    }



    // 这里的insert是双向的,为了简便起见
    void insertPlace(Scene *place);
    void showPlace();
    Scene *leavePlace();

    int insertContain(Item *item, int num);
    void showContain();

    void insertNPC(NPC npc);
    void insertTrader(Trader npc);
    void showNPC();

    // 用于更新时删去死亡者
    void deleteNPC(){
        vector<NPC>::iterator p;
        for (p = npc_vec.begin(); p != npc_vec.end(); ){
            if ( p->getHp() <= 0){
                p = npc_vec.erase(p);
            }else{
                p++;
            }
        }
        vector<Trader>::iterator p1;
        for (p1 = trader_vec.begin(); p1 != trader_vec.end(); ){
            if ( p1->getHp() <= 0){
                p1 = trader_vec.erase(p1);
            }else{
                p1++;
            }
        }
    }

    NPC &getNPC(int index){
        return npc_vec[index];
    }

    Trader &getTrader(int index){
        return trader_vec[index];
    }

    NPC createNPC(Character &p, string name = "", string prompt = "");

    Scene *interact();

    
};
//bool Scene::init_ = Scene::init();
/* #ifndef INIT_SCENE
#define INIT_SCENE
bool Scene::init_ = Scene::init();
#endif */
#endif
