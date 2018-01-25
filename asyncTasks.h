/****************************************************************************/
// Async Tasks Header file
/****************************************************************************/
#pragma once

#include <iostream>
#include <functional>
#include <future>
#include <vector>

typedef void(*task)();
typedef std::function<void()> Callback;

// Async Task definition
class AsyncTasks {
private:
	std::vector<task> tasks;
	std::vector<std::future<void>> futures;
	Callback callback;

	// Helper method
	template<typename R>
	static bool IsReady(std::future<R> const& f);

public:
	AsyncTasks();
	AsyncTasks& Add(task t);
	void Run(const Callback& callback);
};