/*
    In this demo, I have applied the observer design pattern to allow
    one-to many dependency between objects. This pattern is modeled on
    the event-driven programming paradigm and lets us define loosely 
    coupled systems. Whenever an observable object changes its state, 
    its corresponding observer classes are notified and, only then,
    executes their behaviours. In this particular example, whenever the
    player has killed a critter, all the player's subscribers is notified
    by the event (CRITTER_KILLED), upon which a sound effect is played 
    and the scoreboard is updated. 

    Updated: 2022-06-07
    Author: Jonathan Helsing [github.com/Jonathan-source]
*/

#include <iostream>
#include <string>
#include <memory>

// TODO: make a safer version using mutex and smart pointers
//#include <windows.h>
//#include <mmsystem.h>

#include "IObserver.h"
#include "ISubject.h"
#include "Events.h"


// Player is the subject of observation.
class Player : public ISubject<Player> {

public:

    Player() : m_experience(0) {}
    virtual ~Player() = default;

    void KillCritter(int amount = 1)
    {
        for (int i = 0; i < amount; ++i)
        {
            std::cout << "Player: I've killed a critter!" << std::endl;
            m_experience += 10;
            NotifyObservers(*this, Event::CRITTER_KILLED);
        }
    }

    int m_experience;

};


// ScoreBoard observes the Player.
class ScoreBoard : public IObserver<Player> {

public:

    ScoreBoard() : m_crittersKilled(0) {}
    virtual ~ScoreBoard() = default;

    NotifyAction OnNotify(Player& subject, const Event& event) override
    {
        if (event == Event::CRITTER_KILLED)
        {
            std::cout << "ScoreBoard: A total of " + std::to_string(++m_crittersKilled) +
                " have been killed by the player, who has a total of " + std::to_string(subject.m_experience) +
                " experience" << std::endl;
        }
            
        return NotifyAction::Done;
    }

    int m_crittersKilled;

};


// AudioManager observes the Player.
class AudioManager : public IObserver<Player> {

public:

    AudioManager() = default;
    virtual ~AudioManager() = default;

    NotifyAction OnNotify(Player& subject, const Event& event) override
    {
        if (event == Event::CRITTER_KILLED)
        {       
            std::cout << R"(PlaySoundW(TEXT("critter_killed.wav"), NULL, SND_FILENAME | SND_ASYNC);)" << std::endl;
        }

        return NotifyAction::Done;
    }
};


int main()
{   
    Player player;
    ScoreBoard scoreBoard;
    AudioManager audioManager;

    player.RegisterObserver(scoreBoard);
    player.RegisterObserver(audioManager);

    player.KillCritter(5);

    return 0;
}
