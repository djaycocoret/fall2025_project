#include "enemy.h"
#include "grid.h"
#include "grid_object.h"
#include "tower.h"
#include "owner.h"
#include "ai.h"
#include "playerIO.h"
#include "game.h"

int main() {
    AI ai;
    Player player(&ai);
    Game game(10,10, &player);
    ai.set_opponent(&player);

    game.place_object<Enemy>(1,5, &ai);
    game.place_object<Tower>(4,4,&player);

    for (int i = 0; i <5; i++) {
        game.update();
    }



    return 0;
}
