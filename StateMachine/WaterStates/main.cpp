/*
	In this demo, I have applied the state machine design pattern to simulate the
	transition between the several states water can exist in ( liquid, vapor, solid, and plasma ).
	I used the UML state machine diagram, that was uploaded with this code, to create the transition rules.

	Updated: 2022-06-05
	Author: Jonathan Helsing
*/

#include <iostream>
#include <vector>
#include <unordered_map>

// The states water can exist in.
enum class EState
{
	Liquid,
	Vapor,
	Ice,
	Plasma,
	Exit,
};

// Transitions, Actions, Triggers...
enum class ETrigger
{
	Melting,
	Freezing,
	Sublimation,
	Deposition,
	Vaporiaztion,
	Condensation,
	Ionization,
	Deionization,
	Exit
};

inline std::ostream& operator<<(std::ostream &os, const ETrigger &trigger)
{
	switch (trigger)
	{
		case ETrigger::Melting:			os << "Melting";		break;	
		case ETrigger::Freezing:		os << "Freezing";		break;
		case ETrigger::Sublimation:		os << "Sublimation";	break;
		case ETrigger::Deposition:		os << "Deposition";		break;
		case ETrigger::Vaporiaztion:	os << "Vaporiaztion";	break;
		case ETrigger::Condensation:	os << "Condensation";	break;
		case ETrigger::Ionization:		os << "Ionization";		break;
		case ETrigger::Deionization:	os << "Deionization";	break;
		case ETrigger::Exit:			os << "Exit";			break;
		default: break;
	}
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const EState& state)
{
	switch (state)
	{
		case EState::Liquid:	os << "Liquid";	break;
		case EState::Vapor:		os << "Vapor";	break;
		case EState::Ice:		os << "Ice";	break;
		case EState::Plasma:	os << "Plasma";	break;
		default: break;
	}
	return os;
}


int main()
{
	typedef std::unordered_map<EState, std::vector<std::pair<ETrigger, EState>>> TransitionTable;
	TransitionTable rules{ };

	// Define the transitions rules: 
	// [main state]{ available triggers & resulting states }
	rules[EState::Liquid] = {
		{ ETrigger::Freezing, EState::Ice },
		{ ETrigger::Vaporiaztion, EState::Vapor },
		{ ETrigger::Exit, EState::Exit }
	};
	rules[EState::Ice] = {
		{ ETrigger::Melting, EState::Liquid },
		{ ETrigger::Sublimation, EState::Vapor },
		{ ETrigger::Exit, EState::Exit }
	};
	rules[EState::Vapor] = {
		{ ETrigger::Deposition, EState::Ice },
		{ ETrigger::Ionization, EState::Plasma },
		{ ETrigger::Condensation, EState::Liquid },
		{ ETrigger::Exit, EState::Exit }
	};
	rules[EState::Plasma] = {
		{ ETrigger::Deionization, EState::Vapor },
		{ ETrigger::Exit, EState::Exit }
	};

	EState currentState{ EState::Liquid };
	EState exitState{ EState::Exit };

	bool isRunning{ true };
	while (isRunning)
	{
		std::cout << "The water is currently in '" << currentState << "' state\n";

	select_trigger: // It's just a demo, and my teacher will not see this, I hope...

		int index{ 0 };
		for (const auto& item : rules[currentState])
		{
			std::cout << index++ << ". " << item.first << "\n";
		}

		int input{ };
		std::cin >> input;
		if (input < 0 || (input + 1) > rules[currentState].size())
		{
			std::cout << "Invalid option. Please try again.\n";
			goto select_trigger;
		}

		currentState = rules[currentState][input].second;
		if (currentState == exitState) break;
	}

	std::cout << "Thank you for trying out my StateMachine!\n";

	return 0;
}
