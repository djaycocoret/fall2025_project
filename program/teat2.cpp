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
    Game game(10,10, player, ai);
    ai->set_opponent(player);

    game.place_object<Enemy>(1,2, ai);
    game.place_object<Tower>(4,7,player);

    game.place_object<Tower>(8,7,player);

    for (int i = 0; i < 15; i++) {
        game.update();
    }

    delete ai;
    delete player;

    return 0;
}
