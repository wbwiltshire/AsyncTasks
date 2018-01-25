/*************************************************************************************/
// Elapsed Timer class
/*************************************************************************************/
#include "elapsedTimer.h"

ElapsedTimer::ElapsedTimer() : duration(0) {}
void ElapsedTimer::Start() {
	start = std::chrono::system_clock::now();
}
void ElapsedTimer::Stop() {
	end = std::chrono::system_clock::now();
}
unsigned long long ElapsedTimer::DurationNanos()
{
	// Result in nanoseconds
	duration = (end - start).count();

	return duration;
}
unsigned long long ElapsedTimer::DurationMillis()
{
	// Result in nanoseconds
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	// Convert to milliseconds

	return duration;
}
