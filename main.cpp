/*******************************************************************************************/
// C++ Async Tasks
// Link: 
/*******************************************************************************************/
#include <future>
#include <iostream>
#include <chrono>
#include "asyncTasks.h"
#include "elapsedTimer.h"

void simpleTaskOne()
{
	printf("\tSimple task 1 started(250ms)!\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(250));
	std::cout << "\tSimple task 1 complete(" << std::this_thread::get_id() << ")!" << std::endl;
}

void simpleTaskTwo()
{
	printf("\tSimple task 2 started(750ms)!\n");
	std::this_thread::sleep_for(std::chrono::milliseconds(750));
	std::cout << "\tSimple task 2 complete(" << std::this_thread::get_id() << ")!" << std::endl;
}

void printComplete() {
	std::cout << "All task factory tasks completed" << std::endl;
}

int main(int argc, char* argv[])
{
	ElapsedTimer timer;						// allocate on the stack
	AsyncTasks tf1;
	AsyncTasks tf2;

	std::cout << "\tMain thread: " << std::this_thread::get_id() << std::endl;;
	std::cout << "Starting async task test #1" << std::endl;
	timer.Start();
	// Start the taskfactory with a lambda as the callback 
	tf1.Add(simpleTaskTwo).Add(simpleTaskOne);
	tf1.Run([]() {
		std::cout << "All async tasks completed" << std::endl;
	});
	timer.Stop();
	std::cout << "Duration test #1: " << timer.DurationMillis() << "ms (milliseconds)" << std::endl;

	// Wrap the AsyncTaskFactory in an async
	std::cout << "\nStarting task test #2" << std::endl;
	timer.Start();
	// Start the taskfactory with a lmbda as the callback
	tf2.Add(simpleTaskTwo).Add(simpleTaskOne);
	std::future<void> lambda(std::async(std::launch::async, [&tf2, &timer]() { 
		tf2.Run([&timer]() {
			std::cout << "All async tasks completed" << std::endl;
			timer.Stop();
			std::cout << "Duration test #2: " << timer.DurationMillis() << "ms (milliseconds)" << std::endl;
		});
	}));
	std::cout << "After test #2 lambda!\n" << std::endl;

	return 0;
}