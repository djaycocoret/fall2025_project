#include "grid new.h"
#include "tower.h"
#include "enemy.h"
#include "castle.h"
#include "sleep.h"

template<typename T>
void place_object(Grid*& grid, int row, int column) {
    grid->place(row, column, new T(row, column, grid));
}

int main() {
    const int t_max = 20;

    Grid* grid = new Grid(20,20);
    GO* Towers[5];
    for (int i = 0; i < 5; i++){
        Towers[i] = nullptr;
    }

    place_object<Tower>(grid, 5, 5);

    place_object<Tower>(grid, 6, 6);

    place_object<Enemy>(grid, 1, 4);
    place_object<Enemy>(grid, 1, 16);
    place_object<Enemy>(grid, 1, 12);

    grid->place(20, 10, new Castle(20, 10, grid));


    for (int t = 0; t < t_max; t++) {
        grid->update();
        grid->print_grid();
        sleep(1);
    }

    delete grid;
    return 0;
}
