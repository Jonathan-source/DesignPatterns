/*
    In this demo, I have applied the strategy design pattern to allow the
    change of behavior at runtime. In this example I have introduced various
    skills that inherits from a common interface, which the player can select 
    from and use.¨In a real world example, I would use an 'UIController' which
    knows about a 'SkillBar' and the 'Player', and when a skill is selected, 
    the SkillBar notify the UIController; which sets the chosen skill as the
    player's current strategy to use.

    Updated: 2022-06-08
    Author: Jonathan Helsing [github.com/Jonathan-source]
*/

#include <iostream>
#include <unordered_map>


class IPlayerSkill {
public:
    virtual ~IPlayerSkill() {}
    virtual void Use(/* Player &player ? */) = 0;
};


class RestoreHP : public IPlayerSkill {
public:
    RestoreHP() = default;
    virtual ~RestoreHP() = default;

    void Use() override {
        std::cout << "Using RestoreHP" << std::endl;
    }
};


class FrostBolt : public IPlayerSkill {
public:
    FrostBolt() = default;
    virtual ~FrostBolt() = default;

    void Use() override {
        std::cout << "Using FrostBolt" << std::endl;
    }
};


class Flamestrike : public IPlayerSkill {
public:
    Flamestrike() = default;
    virtual ~Flamestrike() = default;

    void Use() override {
        std::cout << "Using Flamestrike" << std::endl;
    }
};


class Player {
public:
    Player() : m_pCurrentSkill(nullptr) {}
    virtual ~Player() { m_skillMap.clear(); }

    void UseSkill() {
        if (m_pCurrentSkill) {
            m_pCurrentSkill->Use();
        }
    }

    void ClearSkill() { m_pCurrentSkill = nullptr; }

    void SetSkill(const std::string& name) {
        m_pCurrentSkill = m_skillMap[name];
    }

    void AddSkill(const std::string& name, IPlayerSkill* pSkill) {
        m_skillMap[name] = pSkill;
    }

private:
    std::unordered_map<std::string, IPlayerSkill*> m_skillMap;
    IPlayerSkill* m_pCurrentSkill;
};


int main() 
{
    Player player;

    player.AddSkill("FrostBolt", new FrostBolt());
    player.AddSkill("Flamestrike", new Flamestrike());
    player.AddSkill("RestoreHP", new RestoreHP());

    player.SetSkill("Flamestrike");
    player.UseSkill();
    player.UseSkill();
    player.SetSkill("RestoreHP");
    player.UseSkill();
    player.SetSkill("FrostBolt");
    player.UseSkill();

    player.SetSkill("Heal"); // does not exist.
    player.UseSkill();  // m_pCurrentSkill is a nullptr, nothing happens.

    return 0;
}
