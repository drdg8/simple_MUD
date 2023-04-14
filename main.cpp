// g++ main.cpp Character.cpp Armor.cpp Item.cpp Inventory.cpp Game.cpp Weapon.cpp Trader.cpp NPC.cpp Scene.cpp -o 'main.exe' -Wall -O2 -m64 -static-libgcc -fexec-charset=GBK ; if ($?) { &'./main.exe' }
#include "Game.h"

using namespace std;
int main() {
	srand(time(NULL));
	Game game;

	//inv.showInventory();
	game.startMenu();
    int state;
    while (state = game.getPlayingState()) {
        if(state == 1){
            game.mainMenu();
        }else if(state == 2){
            game.play();
        }
	}

}