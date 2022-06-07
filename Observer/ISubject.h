#pragma once

#include "IObserver.h"

#include <vector>
#include <stdexcept>

enum class Event;


template<typename T>
class ISubject {

public:

  virtual ~ISubject() = default;

  void RegisterObserver(IObserver<T>& observer) 
	{
		//if (std::find(m_observers.begin(), m_observers.end(), &observer) == m_observers.end()) 
		//{
		//	throw std::runtime_error("Observer already registered");
		//}

	  m_observers.emplace_back(&observer);
	}

	void UnregisterObserver(IObserver<T>& observer)
	{
		m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), &observer), m_observers.end());	
	}

  void NotifyObservers(T& subject, const Event& event)
  {
    std::vector<IObserver<T>*> deadObservers;
    for (auto& observer : m_observers)
    {
        if (observer->OnNotify(subject, event) == NotifyAction::Unregister)
        {
            deadObservers.emplace_back(observer);
        }
    }

    // Remove the dead observers.
    auto newEnd = m_observers.end();
    for (auto& dead : deadObservers)
    {
        newEnd = std::remove(m_observers.begin(), newEnd, dead);
    }

    m_observers.erase(newEnd, m_observers.end());

  }

private:

    std::vector<IObserver<T>*> m_observers;

};
