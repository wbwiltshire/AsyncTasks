/****************************************************************************/
// Async Tasks Class
/****************************************************************************/
#include "asyncTasks.h"

template<typename R>
static bool AsyncTasks::IsReady(std::future<R> const& f)
{
	return  (f.wait_for(std::chrono::seconds(0)) == std::future_status::ready);
}

AsyncTasks::AsyncTasks() {
}
// Add the function to the list of tasks to run
AsyncTasks& AsyncTasks::Add(task t) {
	tasks.push_back(t);		// save the task
	return *this;
}
void AsyncTasks::Run(const Callback& callback) {
	int completed = 0;
	// Save the callback 
	(*this).callback = callback;

	// Start each task in a new thread and add its future to the list of running tasks
	for (std::vector<task>::iterator it = tasks.begin(); it != tasks.end(); it++)
		//std::cout << "\tRunning task." << std::endl;
		futures.push_back(std::async(std::launch::async, *it));

	// Wait till all tasks complete before returning
	while (completed < tasks.size())
	{
		completed = 0;
		for (std::vector<std::future<void>>::iterator it = futures.begin(); it != futures.end(); it++)
		{
			if (IsReady(*it))
				completed++;
			// Check every millisecond
			std::this_thread::yield();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	// We're done so execute the callback
	callback();
}
