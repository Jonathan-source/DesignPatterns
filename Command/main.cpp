/*
	In this demo, I have applied the command design pattern to decouple 
	the invoker from the action performed by the receiver.
	In this example an 'Invoker' is given a number of 'MoveCommands', that
	commands the movement of the receiver ('Player'), which can be ivoked by
	the Invoker without knowing the details of the action that is performed.
	All the information required for executing the action is stored in the concrete
	command	object. 

	Updated: 2022-06-06
	Author: Jonathan Helsing
*/

#include <iostream>
#include <vector>

/**
 * Receiver.
 */
class Player {
public:
	int x;
	int y;

	friend std::ostream& operator<<(std::ostream& os, const Player& player) {
		os << "(" << player.x << ", " << player.y << ")";
		return os;
	}
};

/**
 * Command interface.
 */
class ICommand {
public:
	virtual ~ICommand() = default;
	virtual void Execute() = 0;
	virtual void Undo() = 0;
};

/**
 * Concrete Command.
 */
class MovePlayerCommand : public ICommand {
public:
	enum class EAction { Up, Down, Left, Right };
	MovePlayerCommand(Player& player, EAction action)
		: m_player(player)
		, m_action(action)
	{
	}

	virtual ~MovePlayerCommand() = default;

	void Execute() override {
		switch (m_action) 
		{
			case EAction::Up:		m_player.y -= 1; break;
			case EAction::Down:		m_player.y += 1; break;
			case EAction::Left:		m_player.x -= 1; break;
			case EAction::Right:	m_player.x += 1; break;
			default: break;
		}
	}

	void Undo() override {
		switch (m_action)
		{
		case EAction::Up:		m_player.y += 1; break;
		case EAction::Down:		m_player.y -= 1; break;
		case EAction::Left:		m_player.x += 1; break;
		case EAction::Right:	m_player.x -= 1; break;
		default: break;
		}
	}

private:
	Player& m_player;
	EAction m_action;
};

/**
 * Invoker.
 */
class Invoker {
public:
	void Execute() {
		for (auto cmd = m_commands.begin(); 
			cmd != m_commands.end();
			++cmd) { cmd->Execute(); }
	}

	void Undo() {
		for (auto cmd = m_commands.rbegin();
			cmd != m_commands.rend();
			++cmd) { cmd->Undo(); }
	}

	void AddCommand(const MovePlayerCommand& command) {
		m_commands.emplace_back(command);
	}

private:
	std::vector<MovePlayerCommand> m_commands;
};


int main()
{
	Player player{ 0,0 };
	Invoker invoker{ };

	std::vector<MovePlayerCommand> commands {
		MovePlayerCommand{ player, MovePlayerCommand::EAction::Up},
		MovePlayerCommand{ player, MovePlayerCommand::EAction::Left },
		MovePlayerCommand{ player, MovePlayerCommand::EAction::Up },
		MovePlayerCommand{ player, MovePlayerCommand::EAction::Right },
		MovePlayerCommand{ player, MovePlayerCommand::EAction::Right },
		MovePlayerCommand{ player, MovePlayerCommand::EAction::Down }
	};

	for (const auto& cmd : commands) {
		invoker.AddCommand(cmd);
	}
		
	std::cout << "Player is starting at " << player << "\n\n";

	std::cout << "Execute commands:\n";
	invoker.Execute();

	std::cout << "Player is currently at " << player << "\n\n";

	std::cout << "\nUndo commands:\n";
	invoker.Undo();

	std::cout << "Player is currently at " << player << "\n\n";

	return 0;
}
