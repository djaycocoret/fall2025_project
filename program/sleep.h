#ifndef SLEEP_H_
#define SLEEP_H_

#include <chrono>
#include <thread>

void sleep(int seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

#endif
