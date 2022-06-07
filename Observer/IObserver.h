#pragma once

enum class Event;

enum class NotifyAction { Done, Unregister };

template<typename T> class ISubject;


template<typename T>
class IObserver {

public:

    virtual ~IObserver() = default;

    virtual NotifyAction OnNotify(T& subject, const Event& event) = 0;

};
