#include <chrono>
#include <thread>

void sleep(int seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(2));
}
