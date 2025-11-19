#ifndef SLEEP_H_
#define SLEEP_H_

//this started as a header for sleep function
//now it is util.h, but i am to lazy to rename things

#include <chrono>
#include <thread>
#include <random>

struct Coordinate {
    int row;
    int column;

    Coordinate(int row, int column) :row(row), column(column) {}
};

void sleep(double seconds) {
    std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
}

double random_double(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
}

#endif
