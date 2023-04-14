#include "Scene.h"

/* vector<string> Scene::monsterNames;
bool Scene::init_ = Scene::init(); */

vector<string> Scene::monsterNames = init();

void Scene::insertPlace(Scene *place){
    go.push_back(place);
    place->go.push_back(this);
}

void Scene::showPlace(){
    std::cout << "可以去的地方:\n";
    for (int i = 0; i < go.size(); i++){
        std::cout << i << ": " << go[i]->place << std::endl;
    }
}

// 为了不产生进程重叠，所以引出指针
Scene *Scene::leavePlace(){
    showPlace();
    std::cout << "选个想去的方向吧。\n";
    std::cout << "请输入序号,-1退出\n";
    cout << "--------------------\n";
    int cho;
    while(std::cin >> cho){
        cout << "\n\n\n";
        if(cho == -1){
            return nullptr;
        }else if(cho >= 0 && cho < go.size()){
            return go[cho];
        }else{
            std::cout << "请输入正确的序号\n";
        }
    }
    return nullptr;
}

int Scene::insertContain(Item *item, int num){
    // std::cout << "向场景中添加物品:" << item->getName() << " 数量为:" << num << std::endl;
    return contain.addItem(item, num);
}

void Scene::showContain(){
    std::cout << "展示场景里的物品\n";
    contain.showItem();
}

void Scene::insertNPC(NPC npc){
    npc_vec.push_back(npc);
}

void Scene::insertTrader(Trader npc){
    trader_vec.push_back(npc);
}

void Scene::showNPC(){
    std::cout << "场景里的NPC:\n";
    for (int i = 0; i < npc_vec.size(); i++){
        cout << i << ": " << npc_vec[i].getName() << std::endl;
    }
    for (int i = 0; i < trader_vec.size(); i++){
        cout << i + npc_vec.size() << ": " << trader_vec[i].getName() << std::endl;
    }
}

/*
NPC Scene::getNPC(int index){
        return nullptr;
        cout << "最大数量是" << npc_vec.size() + trader_vec.size() << "\n";
        cout << "请输入正确数量\n";
        cout << "-------------\n";
    }
    }else {
    }
}
*/

NPC Scene::createNPC(Character &p, string name, string prompt){
	static int NPCnum = 0;
	NPCnum++;
	float level = p.getLevel();
	float ratio = level / 14 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (level * 3 / 14 - level / 14)));
	// cout << ratio << endl;
	ratio = sqrt(ratio);
	// ratio^2 = level / 7
    //srand(time(0));
    int random = rand() % 8;
    /* if(name == ""){
		name = "NPC" + to_string(NPCnum);
	} */
    name = monsterNames[random];
    int damage = (int)(p.getDamage() * ratio);
	int defence = (int)(p.getDefence() * ratio);
	int hp = (int)(p.getmaxhp() * ratio);
	// 15 level - 5 level
	int money = rand() % (p.getLevel() * 10) + 5 * p.getLevel();
	// 1 / 3 - 2 / 3
	int exp = (float)(rand() % 10 + 10) / 30 * p.getExpNext();
	return NPC(&p, name, hp, damage, defence, exp, money, prompt);
}	

Scene *Scene::interact(){
    std::cout << "你来到了" << place << std::endl;
    std::cout << prompt << std::endl;
    std::cout << "选择你的操作\n";
    std::cout << "-1: 退出游戏 0: 离开此地 1: 查看NPC 2. 更新NPC\n";
    cout << "------------------\n";
    int cho;
    while(std::cin >> cho){
        cout << "\n\n\n";
        if(cho == -1){
            exit(0);
        }else if(cho == 0){
            Scene *tmp = leavePlace();
            if(tmp){
                return tmp;
            }
        }else if(cho == 1){
            showNPC();
            cout << "选择要交互的NPC的序号, -1:退出\n";
            cout << "-----------------\n";
            int cho1;
            while(cin >> cho1){
                cout << "\n\n\n";
                if(cho1 == -1){
                    break;
                }
                else if(cho1 < 0 || cho1 >= npc_vec.size() + trader_vec.size()){
                    cout << "最大是" << npc_vec.size() + trader_vec.size() - 1 << "\n";
                    cout << "请输入正确的序号\n";
                }else if(cho1 < npc_vec.size()){
                    NPC &npc = getNPC(cho1);
                    npc.interact();
                    break;
                }else{
                    Trader &npc = getTrader(cho1 - npc_vec.size());
                    npc.interact();
                    break;
                }
                showNPC();
                cout << "选择要交互的NPC的序号, -1:退出\n";
                cout << "--------------------\n";
            }
        }else if(cho == 2){
            if(getPlace() == "试炼"){
                // 试炼怪物更新
                int Nnum = (float)(rand() % 10 + 10) / 30;
                if(Nnum <= 0)
                    Nnum = 2;
                // uncomplete
                for (int i = 0; i < Nnum; i++){
                    // getNPC(0) 需要存在
                    NPC tmp_npc = createNPC(getNPC(0).getPlayer());
                    tmp_npc.renew();
                    insertNPC(tmp_npc);
                }
                deleteNPC();
                cout << "试炼怪物更新成功\n";
            }
            for(auto &i: trader_vec){
                i.renewSell();
            }
            cout << "货品更新成功\n";
            cout << "-------------\n";
        }else if(cho > 2 || cho < 0){
            cout << "请输入正确的序号\n";
            cout << "--------------------\n";
            continue;
        }
        std::cout << "你来到了" << place << std::endl;
        std::cout << "-1: 退出游戏 0: 离开此地 1: 查看NPC 2. 更新NPC\n";
        cout << "------------------\n";
    }
}

#ifdef _TEST_SCENE_

int main(){
    Character p1;
    p1.initialize("Tom");

    Scene mainCity("主城", "这里是玩家主城，人来人往，车水马龙。");
    Scene weaponStore("武器店", "武器店里，大胡子老板正盯着你。");
    Scene supermarket("超市", "进入超市，里面的商品屈指可数。");
    Scene hotel("汽车旅馆", "破旧的汽车旅馆，但终于可以睡一觉了。");
    mainCity.insertPlace(&weaponStore);
    mainCity.insertPlace(&supermarket);
    mainCity.insertPlace(&hotel);
    // name, hp, damage, defence, exp
    Trader t1("邱总", 100, 10, 6, 60, p1);
    Trader t2("小刘", 120, 10, 7, 70, p1);
    Trader t3("小刘", 120, 10, 7, 70, p1);
    supermarket.insertNPC(&t1);
    supermarket.showNPC();

	// name, description, type, level, buyValue, sellValue, rarity
    Item cookie("饼干", "感觉已经变质了。", "食物", 1, 10, 5, 1);
    Item water("纯净水", "谁知道纯不纯净。", "食物", 1, 10, 5, 1);
    t1.insertSell(&cookie, 5);
    t1.insertSell(&water, 5);
    t1.goSell();
    p1.showItem();
}

#endif