#include "enemy.h"
#include "grid.h"
#include "grid_object.h"
#include "owner.h"
#include "ai.h"
#include "game.h"

int main() {
    Game game(10,10);

    AI ai;


    game.place_object<Enemy>(1,5, &ai);


    game.update();



    return 0;
}
