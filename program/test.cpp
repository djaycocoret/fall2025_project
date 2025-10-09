#include "enemy.h"
#include "game.h"
#include "tower.h"

int main() {
    Game game(10, 10);

    game.place_object<Tower>(5,5);

    game.place_object<Enemy>(1,9);

    for (int i = 0; i < 5; i++) {
        game.update();
    }


    return 0;
}
