#include "Game.h"
#include "Character.h"
#include <iostream>
#include <math.h>

Game::Game()
{
	choice = 0;
	isPlaying = true;

}

Game::~Game()
{
}

// Functions
void Game::initGame()
{
	std::string name;



	std::cout << "==============" << std::endl;
	std::cout << "0: 创建角色" << std::endl;
	std::cout << "-1: 退出游戏" << std::endl;

	std::cout << std::endl
			  << "你打算怎么做？ ";
	std::cin >> choice;
	switch (choice)
	{
	case (0):
		createCharacter();

		break;
	case (-1):
		isPlaying = 0;
		std::cout << std::endl
				  << "你可以离开游戏，但你无法逃离末世" << std::endl;
		break;
	default:
		break;
	}
}

void Game::startMenu()
{
	srand(time(0));
	int random = rand() % 3 + 1;
	switch(random){
		case(1): 
			std::cout << "努力活下来，并变得更强!" << std::endl;
			break;
		case(2):
			std::cout << "我猜你活不了多久!" << std::endl;
			break;
		case(3):
			std::cout << "快去冒险吧!" << std::endl;
			break;
		default:
			break;
		}
	
	std::cout << "0: 开始游戏" << std::endl;
	std::cout << "1: 退出游戏" << std::endl;
	std::cout << std::endl
			  << "你打算怎么做？ ";
	std::cin >> choice;
	switch (choice)
	{
	case (0):
		initGame();

		break;
	case (1):
		isPlaying = false;
		std::cout << std::endl
				  << "你可以离开游戏，但你无法逃离末世" << std::endl;
		break;
	default:
		break;
	}
}
void Game::mainMenu()
{
	
	std::cout << "0: 看看自己" << std::endl;
	std::cout << "1: 创建新角色" << std::endl;
	std::cout << "2: 出去走走" << std::endl;
	std::cout << "-1: 退出游戏" << std::endl;
	std::cout << std::endl
			  << "你打算怎么做？ ";
	std::cin >> choice;

	
	switch (choice)
	{
	case (0):
		activeCharacter.showStats();
		break;
	case (-1):
		isPlaying = 0;
		std::cout << std::endl
				  << "你可以离开游戏，但你无法逃离末世" << std::endl;
		break;
	case (1):
		createCharacter();
		break;
	case (2):
		isPlaying = 2;
		cout << "Let's go!\n";
		break;
	default:
		break;
	}
}

void Game::endGame()
{
}

void Game::createCharacter()
{
	std::string name = "";
	Character newcharacter;
	std::cout << "你叫什么名字？ ";
	std::cin.ignore();
	std::getline(std::cin, name);

	newcharacter.initialize(name);
	characters.push_back(newcharacter);
	activeCharacter = characters.back();
	
}

std::vector<std::string> Game::split(std::string &str, char c)
{
	size_t previous = 0;
	size_t current = str.find(c);
	std::vector<std::string> ret;
	while (current != std::string::npos)
	{
		if (current > previous)
		{
			ret.push_back(str.substr(previous, current - previous));
		}
		previous = current + 1;
		current = str.find(c, previous);
	}
	if (previous != str.size())
	{
		ret.push_back(str.substr(previous));
	}
	return ret;
}

void Game::play(){
	// isplaying = 0 for quit

	cout << "初始化中\n";
	cout << "-----------------------------------\n";
	Character p1;
    p1.initialize("Tom");

    Scene mainCity("主城", "这里是玩家主城，人来人往，车水马龙。");
    Scene weaponStore("武器店", "武器店里，大胡子老板正盯着你。");
    Scene supermarket("超市", "进入超市，里面的商品屈指可数。");
    Scene adventure("试炼", "里面的温度令人胆寒。");
	Scene hotel("汽车旅馆", "破旧的汽车旅馆，但终于可以睡一觉了。");
    mainCity.insertPlace(&weaponStore);
    mainCity.insertPlace(&supermarket);
    mainCity.insertPlace(&adventure);
	mainCity.insertPlace(&hotel);

    // name, hp, damage, defence, exp, money, propmt
    Trader t0(&p1, "恺神", 10000, 10000, 10000, 10000, 10000, "听其他人说他是个语言大师，不论从哪个角度来说。");
    Trader t1(&p1, "刘老板", 100, 30, 20, 700, 500, "感觉他英语不太好的样子。");
    Trader t2(&p1, "邱总", 80, 40, 14, 600, 700, "他看上去贼眉鼠眼的，眼神中总有一抹贪婪。");
	Trader t3(&p1, "旅店老板娘", 80, 40, 14, 600, 700, "老板娘，麻烦给我一个好房间。");
	NPC boss(&p1, "首领", 1000, 100, 100, 1000, 2000, "别碰它。");

	// NPC n1("小弟A", 15, 4, 0, 30, 30, "如名字般毫无特点。", p1);
    // NPC n2("小弟B", 15, 3, 1, 30, 30, "如名字般毫无特点。", p1);
    // NPC n3("小弟C", 15, 2, 1, 30, 25, "如名字般毫无特点。", p1);


	weaponStore.insertTrader(t1);
	supermarket.insertTrader(t2);
	hotel.insertTrader(t3);
	mainCity.insertTrader(t0);
	adventure.insertNPC(boss);
	adventure.insertNPC(adventure.createNPC(p1));

	t3.renewSell();
	t3.renewSell();
	t3.renew();
	t0.renewSell();
	t0.renewSell();
	t0.renew();
	t1.renewSell();
	t1.renewSell();
	t1.renew();
	t2.renewSell();
	t2.renewSell();
	t2.renew();
	// supermarket.showNPC();

	// name, description, type, level, buyValue, sellValue, rarity

	// Food cookie(10, "饼干", "感觉已经变质了。", "食物", 1, 10, 5, 1);
	// Food water(5, "纯净水", "谁知道纯不纯净。", "食物", 1, 10, 5, 1);
	// Weapon blade1(5, 2, "破损的匕首", "似乎生锈了。", "武器", 1, 20, 10, 1);
	// Weapon blade2(7, 3, "一般的匕首", "一般。", "武器", 2, 50, 30, 1);
	// Weapon blade3(10, 5, "精良的匕首", "看上去不错。", "武器", 3, 100, 50, 1);
	// Weapon blade4(12, 7, "优异的匕首", "刀尖熠熠闪光。", "武器", 4, 150, 80, 1);
	// Armor jacket1(2, 4, "破损的夹克", "也就凑合吧。", "防具", 1, 20, 10, 1);
	// Armor jacket4(8, 14, "优异的夹克", "真的很硬。", "防具", 4, 150, 80, 1);
	// Armor cottonclothes1(1, 6, "破损的棉大衣", "防御时有点作用，进攻就完全不行了","防具", 1, 20, 10 ,1);
	// Armor cottonclothes4(6, 17, "优异的棉大衣", "好重。","防具", 4, 150, 80 ,1);

	// t0.insertSell(&blade4, 9);
	// t0.insertSell(&cottonclothes4, 9);
	// t1.insertSell(&blade1, 1);
	// t1.insertSell(&blade3, 1);
	// t1.insertSell(&jacket1, 1);
	// t1.insertSell(&cottonclothes1, 1);
	// t1.insertDrop(&blade1, 1);
	// t1.insertDrop(&water, 5);
	// t1.insertDrop(&jacket1, 1);
	// t1.insertHelper(&n1);
	// t1.insertHelper(&n2);
	// t2.insertSell(&water, 3);
	// t2.insertSell(&cookie, 6);
	// t2.insertDrop(&water, 5);
	// t2.insertDrop(&cookie, 6);
	// t2.insertHelper(&n3);

	cout << "初始化完成。\n";
	cout << "-----------------------------------\n\n\n";
	cout << "生存提示: " << endl;
	cout << "0: 千万不要打除了数字以外的字符，不然游戏就炸了。" << endl;
	cout << "1: 试炼是随机生成怪物的地方。如果你发现没有怪物生成，请选择更新NPC。" << endl;
	cout << "1.5: 更新NPC也可以更新商人的物品。\n";
	cout << "2: 食物可以回血。" << endl;
	cout << "开心游玩!\n";
	cout << "-----------------\n\n\n";
	// for (int i = 0; i < 10; i++){
	// 	Armor tmp = createArmor(p1);
	// 	tmp.showAtribute();
	// }

	// p1.changeExp(1000);
	Scene *tmp = mainCity.interact();
	while(tmp){
		tmp = tmp->interact();
	}

	isPlaying = 0;
}
