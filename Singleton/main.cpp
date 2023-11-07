/*
    In this demo, I have applied the singleton design pattern; which is used to restrict the instantiation of a class to one object.
    This is useful when exactly one object is needed to coordinate actions across the system, for example a Logger or Database class.
    
    In this particular example I experimented with creating a Singleton template class tailored to use for classes that should be Singleton.

    Note: this implementation is not reliable in a multithreaded environment, however it works generally fine in a single-threaded
    environment, though interrupts can be problematic. Also, Singletons are difficult to mock for testing when necessary and not 
    scaleable. The dependency injection design pattern is preferable in the vast majority of cases.

    Updated: 2023-11-27
    Author: Jonathan Helsing [github.com/Jonathan-source]
*/

#include <iostream>

template <typename T>
struct Singleton
{
	static inline T& Get() noexcept
	{
		static T instance;
		return instance;
	}

protected:
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) noexcept = delete;

	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) noexcept = delete;
};


class Application : public Singleton<Application> {
public:
    // ...
};

int main()
{
    // Eager initialization.
    Application::Get();

    return 0;
}
