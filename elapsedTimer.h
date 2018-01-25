#pragma once
/*************************************************************************************/
// Elapsed Timer class header
/*************************************************************************************/
#include <chrono>
#include <ctime>

class ElapsedTimer {
private:
	std::chrono::system_clock::time_point start, end;
	unsigned long long duration;
public:
	ElapsedTimer();
	void Start();
	void Stop();
	unsigned long long DurationNanos();
	unsigned long long DurationMillis();
};