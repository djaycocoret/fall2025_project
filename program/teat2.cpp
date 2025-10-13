#include "enemy.h"
#include "grid.h"
#include "grid_object.h"
#include "tower.h"
#include "owner.h"
#include "ai.h"
#include "playerIO.h"
#include "game.h"

int main() {
    AI* ai = new AI;
    Player* player = new Player(ai);
    Game game(20,20, player, ai);
    ai->set_opponent(player);

    game.place_object<Tower>(4,7,player);
    game.place_object<Tower>(6,4,player);
    game.place_object<Tower>(5,5,player);

    while (!game.game_over_thing) {
        game.update();
        //sleep(1);
    }

    delete ai;
    delete player;

    return 0;
}
