#include <iostream>
#include <functional>
#include <vector>
#include <cassert>

//
// BaseEvent.h
//
template <typename... TArgs>
class BaseEvent {
public:
    using EventCallback = std::function<void(TArgs...)>;

    void operator+=(EventCallback func) {
        m_subsribers.emplace_back(func);
    }

    void operator()(TArgs... args) {
        Broadcast(args...);
    }

    void Broadcast(TArgs... args) {
        for (const auto& subscriber : m_subsribers) {
            assert(subscriber != nullptr);
            subscriber(args...);
        }
    }

private:
    std::vector<EventCallback> m_subsribers;
};

#define DECLARE_EVENT(EventType, EventDispatcherType, ...)  \
    class EventType : public BaseEvent<__VA_ARGS__>         \
    {                                                       \
        friend class EventDispatcherType;                   \
    };                                                      \


//
// Events.h
//
enum class Direction { None, Up, Down, Left, Right, Count };
struct PlayerMoveEvent
{
    Direction direction;

    PlayerMoveEvent(Direction dir = Direction::None) 
        : direction(dir) 
    {
    }
};


//
// PlayerController.h
//
class PlayerController {
public:
    //using OnPlayerMoveEvent = BaseEvent<float, float>;
    DECLARE_EVENT(OnPlayerMoveEvent, PlayerController, const PlayerMoveEvent&)
    OnPlayerMoveEvent OnMove;

    void SimulateMovement(Direction direction)
    {
        PlayerMoveEvent Event(direction);
        OnMove.Broadcast(Event);
    }
};


//
// Player.h
//
class Player {
public:
    Player(PlayerController& controller) {
        // Subscribe to the movement event
        controller.OnMove += [this](const PlayerMoveEvent& Event) {
            switch (Event.direction) {
            case Direction::None:   break;
            case Direction::Up:     break;
            case Direction::Down:   break;
            case Direction::Left:   break;
            case Direction::Right:  break;
            default:
                break;
            }
        };
    }
};


//
// main.cpp
//
int main() {
    PlayerController playerController;
    Player player(playerController);

    playerController.SimulateMovement(Direction::Left);

    return 0;
}