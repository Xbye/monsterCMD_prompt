//SET TO C++17

#include <iostream>
#include <limits>
#include <string>
#include <vector>


enum class typemonster		//TYPEMONSTER::---
{
	Slime = 1,
	Orc,
	Dragon,
	Unknown,
};

struct infomonster			//INFOMONSTER.---
{
	typemonster		type{};
	std::string		name{};
	int				health{};
};

bool getYESNO();

inline void clearBuffer();
std::string stringType(const typemonster);
unsigned int getMonsterAMOUNT();
infomonster monstercreate(infomonster&, unsigned const int, unsigned const int);


int main()
{
	std::cout
		<< "Create a monster through command prompt.";

	if ( getYESNO() )
	{ /*Requesting User Input Before Continuing Program*/

		unsigned int totalMonsters{ getMonsterAMOUNT() };

		infomonster* monster{new infomonster[static_cast<std::size_t>(totalMonsters)] };
		/*Creating an array with set-length from user-input*/

		for (unsigned int iii{ 1 }; iii < totalMonsters + 1; ++iii)
		{

			monstercreate(monster[iii - 1], totalMonsters, iii);
			/*Now we make the monster*/

			std::cout
				<< stringType(monster[iii - 1].type) << ' ' << monster[iii - 1].name 
				<< " has joined the array battlefield with " << monster[iii - 1].health
				<< " health.";

			std::cout << std::endl;

			if (!(getYESNO()))
			{
				totalMonsters = iii;
				break;
			}
		}

		std::cout << std::endl;

		for (; totalMonsters > 0; --totalMonsters)
		{
			std::cout << '\n'
				<< stringType(monster[totalMonsters - 1].type)
				<< ' ' << monster[totalMonsters -1].name 
				<< " has perished.";
		}

		delete[] monster;
	}

	std::cout << '\n';
	return 0;
}

bool getYESNO()
{
	static bool continuecreation{ false };
	/*Function is re-used, have local static variable for different paths on second run*/

	while (true)
	{
		std::cout << '\n'
			<< "Create a";
		if(continuecreation == true)
			std::cout << "nother";
		std::cout << " monster? (Y/N): ";

		std::string start;
		//std::getline(std::cin, start, '\n');
		std::ws(std::cin);
		std::getline(std::cin, start);


		switch (start[0])
		{
		case 'Y':
		case 'y':
			continuecreation = true;	/*Guaranteees second path on second run*/
			return true;
		case 'N':
		case 'n':
			return false;
		default:
			std::cout << '\n'
				<< "[WARNING] Input \"" << start << "\" is not a valid input.";
		}
	}
}

inline void clearBuffer()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

unsigned int getMonsterAMOUNT()
{

	unsigned int maxallowed{ 32 };
	unsigned int inputTotal{};
	
	while (true)
	{
		std::cout << '\n'
			<< "How many monsters? (MAX " << maxallowed << "): ";

		std::cin >> inputTotal;

		if (std::cin.fail() || inputTotal > maxallowed)
		{
			clearBuffer();
			std::cout
				<< "[WARNING] Only input integers, below the max of " << maxallowed << ".";
		}
		else
		{
			clearBuffer();
			return inputTotal;
		}

	}
}

infomonster monstercreate(infomonster& monster, unsigned const int max, unsigned const int current)
{
	std::cout << '\n'
		<< "Monster " << current << " of " << max;

	std::cout << '\n'
		<< "Monster Type (Slime/Orc/Dragon)";
	while (true)
	{
		std::cout << '\n'
			<< "TYPE #" << current << ": ";

		std::string input{};
		std::ws(std::cin);
		std::getline(std::cin, input);

		for (auto& letter : input)
		{/*We're going to transform all inputs to upper-case to limit cases*/
			if (isalpha(letter))
			{
				letter = toupper(letter);
			}
		}

		if(input == "SLIME")
			monster.type = typemonster::Slime;
		else if(input == "ORC")
			monster.type = typemonster::Orc;
		else if(input == "DRAGON")
			monster.type = typemonster::Dragon;
		else
		{
			std::cout
				<< "[WARNING] \"" << input << "\" is not a valid type.";
		}

		if (static_cast<bool>(monster.type))
			break; 
		/*Lets us break from the permanent loop if enum-class is not null*/
		/*Without repeating ourselves or adding extra { } for each case.*/
	}

	std::cout << '\n'
		<< "What is the " << stringType(monster.type) << "'s name?";

	while (true)
	{
		std::cout << '\n'
			<< "NAME #" << current << ": ";

		std::string input{};
		std::ws(std::cin);
		std::getline(std::cin, input);

		bool alphab{ true };
		for (auto& letter : input)
		{
			if ( !(isalpha(letter)) && !(isspace(letter)) )
			{
				alphab = false;
				break;
			}
		}

		if (alphab)
		{
			input[0] = toupper(input[0]);
			/*Making the first letter capitalized because OCD*/
			monster.name = input;
			break;
		}
		else
			std::cout 
				<< "[WARNING] Symbols and numbers can't be in names, silly.";
	}

	std::cout << '\n'
		<< "The " << stringType(monster.type) << ", " << monster.name 
		<< ", has how much health? (MAX 99,999)";

	while (true)
	{
		std::cout << '\n'
			<< "HEALTH #" << current << ": ";

		int input{ 0 };
		std::cin >> input;

		if (std::cin.fail() || input > 99'999)
		{
			std::cout
				<< "[WARNING] Integer inputs, and under 99,999 only.";
		}
		else
		{
			monster.health = input;
			clearBuffer();

			break;
		}

		clearBuffer();
	}

	return monster;
}

std::string stringType(const typemonster monster)
{
	switch (monster)
	{
	case typemonster::Slime:
		return "Slime";
	case typemonster::Orc:
		return "Orc";
	case typemonster::Dragon:
		return "Dragon";
	case typemonster::Unknown:
		return "Unknown";
	default:
		return "[???]";
	}
}