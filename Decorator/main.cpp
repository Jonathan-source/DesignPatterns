/*
	In this demo, I have applied the functional decorator design pattern to add 
	new functionality to an existing function without altering its structure. 
	The functionality I decided to add was the ability to clock/record the 
	functions' execution time and save it in a vector. Any new functionality 
	can easily be added in the future, such as exporting the data to a file or 
	perform any statistical analysis on it. I also took the liberty of using the 
	C++ generic template feature to allow decoration of any function, regardless
	of its return-type or arguments.

	Updated: 2022-06-06
	Author: Jonathan Helsing
*/

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <functional>
#include <algorithm>
#include <numeric>

/**
 * The object/decorator in which the function will be wrapped into.  
 */
template<typename R, typename... Args>
class FuncLogger {
public:
	FuncLogger(const std::function<R(Args...)>& func, const char* funcName)
		: m_func(func)
		, m_funcName(funcName)
		, m_start()
		, m_stop()
		, m_duration()
		, m_records()
	{
	}

	R operator() (Args... args) {
		m_start = std::chrono::steady_clock::now();

		R result = m_func(args...);

		m_duration = std::chrono::steady_clock::now() - m_start;
		m_records.emplace_back(m_duration);

		return result;
	}

	std::vector<std::chrono::nanoseconds> GetRecords() const {
		return m_records;
	}

private:
	std::function<R(Args...)> m_func;
	const char* m_funcName;
	std::chrono::steady_clock::time_point m_start;
	std::chrono::steady_clock::time_point m_stop;
	std::chrono::nanoseconds m_duration;
	std::vector<std::chrono::nanoseconds> m_records;
};

// Utility function for creating the 'FuncLogger' class.
template<typename R, typename... Args>
auto CreateFuncLogger(R(*func)(Args...), const char* name) {
	return FuncLogger< R, Args... >(
		std::function<R(Args...)>(func),
		name
	);
}

/**
 * The function that will be decorated.  
 */
int Add(int a, int b, int c) {
	return a + b + c;
}


int main()
{
	auto logged_Add{ CreateFuncLogger(Add, "Add") };

	int sum{ 0 };
	for (int i = 0; i < 100; i++)	{
		sum = logged_Add(sum, i, (i * i));
	}

	std::cout << "\n --- Results ---\n" << std::endl;

	int index{ 0 };
	const auto records = logged_Add.GetRecords();
	for (const auto& rec : records)	{
		std::cout << index++ 
		<< ". " 
		<< rec.count() // nanoseconds.
		// << std::chrono::duration_cast<std::chrono::microseconds>(rec).count() // microseconds.
		<< " us\n";
	}

	return 0;
}
