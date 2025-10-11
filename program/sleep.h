#ifndef SLEEP_H_
#define SLEEP_H_

#include <chrono>
#include <thread>
#include <random>

void sleep(int seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

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

#endif
