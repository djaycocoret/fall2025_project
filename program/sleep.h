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


//i asked mistral ai how i would make a random int
// not used in final project, only for testing
int random_int(int min, int max) {
    // Use random_device to seed the random number generator
    std::random_device rd;
    // Use the Mersenne Twister engine for better randomness
    std::mt19937 gen(rd());
    // Define the range [min, max]
    std::uniform_int_distribution<> distrib(min, max);
    // Generate and return a random number in the range
    return distrib(gen);
}

double random_double(double min, double max) {
    // Use random_device to seed the random number generator
    std::random_device rd;
    // Use the Mersenne Twister engine for better randomness
    std::mt19937 gen(rd());
    // Define the range [min, max]
    std::uniform_real_distribution<> distrib(min, max);
    // Generate and return a random number in the range
    return distrib(gen);
}

#endif
