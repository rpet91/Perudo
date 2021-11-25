#include "Game.hpp"		// Game.hpp
#include "Player.hpp"	// Player.hpp
#include <iostream>		// std::cout
#include <string>		// std::string
#include <sstream>		// std::stringstream
#include <cstdlib>		// system
#include <unistd.h>		// usleep
#include <vector>		// vector
#include <map>			// map

#define JOKER 7			// define for readability

// Default constructor.
Game::Game() : _amountOfDice(1), _valueOfDice(1), _roundNumber(1), _palifico(false)
{
}

// Default destructor.
Game::~Game()
{
}


// This function will show a list of current players added to the game.
void	Game::listPlayers() const
{
	if (this->_players.size() == 0)
		std::cout << "There are no players added to the game. Please add a player first." << std::endl;
	else
	{
		std::cout << "The current added players in the game are:" << std::endl;
		for (size_t i = 0; i < this->_players.size(); i++)
			std::cout << "- " << this->_players[i].getName() << std::endl;
	}
}

// This function will add a player to the game if possible.
void	Game::addPlayer(std::string const &name)
{
	if (this->_players.size() == 5)
	{
		std::cout << "Maximum player count reached!" << std::endl;
		return ;
	}
	
	Player	newPlayer(name);

	this->_players.push_back(newPlayer);
	std::cout << "Player " << name << " is successfully added!" << std::endl;
}

// This function will delete all added players.
void	Game::deletePlayers()
{
	this->_players.clear();
	std::cout << "Player list has been clear!" << std::endl;
}

// This function will run the game.
void	Game::runGame()
{
	if (this->_players.size() <= 1)
	{
		std::cout << "There are not enough players to start the game! You need at least two players." << std::endl;
		return ;
	}
	this->_setupGame();
	// debug show dice
	for (size_t i = 0; i < this->_players.size(); i++)
		this->_players[i].showDice();
   	// end debug

	std::map<size_t, std::string>::iterator currentPlayer = this->_playOrder.begin();
	std::string								playerInput;

	// This loop will continue until the game is finished.
	while (true)
	{
		system("clear");
		system("clear");
		this->_showPreviousBid(currentPlayer->second);
		std::cout << "Turn " << this->_roundNumber << "! It is \033[1;32m";
		std::cout << currentPlayer->second << "'s\033[0m turn. Press enter to continue..." << std::endl;
		// This loop will wait for the current player to be ready for their turn.
		while (this->_options.readInput()[0] != '\0') {}
		// This loop will continue until the current player performed an action.
		std::cout << "Your dice rolls are:" << std::endl;
		this->_players[currentPlayer->first].showDice();
		while (true)
		{
			std::cout << "What would you like to call (bid/bluff/perudo)?: ";
			playerInput = this->_options.readInput();
			if (playerInput == "BID")
				this->_bid();
			else if (playerInput == "BLUFF")
				std::cout << "you chose bluff" << std::endl;
			else if (playerInput == "PERUDO")
				std::cout << "you chose perudo" << std::endl;
			else
			{
				std::cout << "Invalid command, please try again." << std::endl;
				continue ;
			}
			std::cout << std::endl;
			break ;
		}
		currentPlayer++;
		this->_roundNumber++;

		// If t
		if (currentPlayer == this->_playOrder.end())
			currentPlayer = this->_playOrder.begin();
		usleep(2000000);
	//	break;
	}
}

// This function will free all the memory and exits the game after.
void	Game::exitGame()
{
	this->_players.clear();
	std::cout << "Thanks for playing Perudo. Hope to see you next time!" << std::endl;
}


// This function will simply create the game for us. The dice will be rolled and a random order is decided.
void	Game::_setupGame()
{
	system("clear");
	for (size_t i = 0; i < this->_players.size(); i++)
		this->_players[i].rollDice();
	this->_decidePlayOrder();
	std::cout << "Setup complete! Game is starting now..." << std::endl;
	usleep(1000000);
	std::cout << "Press enter whenever everyone is ready..." << std::endl;
	while (this->_options.readInput()[0] != '\0') {}
}

//	This function will decide randomly what the order of the game is.
void	Game::_decidePlayOrder()
{
	std::map<size_t, std::string>::iterator it;
	std::vector<Player>						newPlayerOrder;
	size_t									i = 0;
	int										randomPlayer = 0;

	this->_playOrder.clear();
	while (i < this->_players.size())
	{
		randomPlayer = rand() % this->_players.size();
		// In the for loop we are checking if we got a duplicate name in the randomizer.
		for (it = this->_playOrder.begin(); it != this->_playOrder.end(); it++)
		{
			if (this->_players[randomPlayer].getName() == it->second)
				break ;
		}
		// If we iterated to the end, it means the name has not been added yet.
		if (it == this->_playOrder.end())
		{
			this->_playOrder[i] = this->_players[randomPlayer].getName();
			newPlayerOrder.push_back(this->_players[randomPlayer]);
			i++;
		}
	}
	this->_players = newPlayerOrder;
	std::cout << "The play order during the game is:" << std::endl;
	for (std::vector<Player>::iterator it = this->_players.begin(); it != this->_players.end(); it++)
		std::cout << "- " << it->getName() << std::endl;
}

// This function shows what the previous player has bid.
void	Game::_showPreviousBid(std::string const &currentPlayer) const
{
	static std::string	previousPlayer;

	if (this->_roundNumber == 1)
	{
		previousPlayer = currentPlayer;
		return ;
	}
	std::cout << "The previous bid by \033[1;32m" << previousPlayer;
	std::cout << "\033[0m was \033[1;31m[" << this->_amountOfDice << "] [";
	if (this->_valueOfDice == JOKER)
		std::cout << "J's]\033[0m" << std::endl << std::endl;
	else
		std::cout << this->_valueOfDice << "'s]\033[0m" << std::endl << std::endl;
	previousPlayer = currentPlayer;
}

// This function is called when the current player wants to call a bid.
void	Game::_bid()
{
	std::string			input;
	size_t				newAmount;
	size_t				newValue;
	size_t				jokerValue;
	bool				joker;

	// Checks if the previous round had a joker as bid.
	// Sets the correct minimum requirement for the current player.
	if (this->_valueOfDice == JOKER)
	{
		this->_amountOfDice = (2 * this->_amountOfDice) + 1;
		this->_valueOfDice = 1;
	}
	// This loop will continue until the current player gives a valid bid.
	while (true)
	{
		std::stringstream	conversionStringAmount;
		std::stringstream	conversionStringValue;
	
		jokerValue = 0;
		joker = false;
		std::cout << "How many dice would you like to bid?: ";
		input = this->_options.readInput();
		if (this->_isAllDigits(input) == false)
			newAmount = 0;
		else
		{
			conversionStringAmount << input;
			conversionStringAmount >> newAmount;
		}
		std::cout << "And with what value?: ";
		input = this->_options.readInput();
		if (input == "J")
		{
			jokerValue = 2 * newAmount;
			newValue = JOKER;
			joker = true;
		}
		else if (this->_isAllDigits(input) == true)
		{
			conversionStringValue << input;
			conversionStringValue >> newValue;
		}
		else
			newAmount = 0;

		// Checks if the user wants to start a round with a Joker bid without Palifico.
		if (joker == true && this->_palifico == false && this->_roundNumber == 1)
		{
			std::cout << "The first bid of a round can't be Jokers." << std::endl;
			continue ;
		}
		// Checks if the given values are valid (2-6 and jokers).
		if ((newValue >= 2 && newValue <= 6) || joker == true)
		{
			// The bid is valid if the new amount is higher than the previous one.
			if (newAmount > this->_amountOfDice || jokerValue >= this->_amountOfDice)
				break ;
			else if (newAmount == this->_amountOfDice)
			{
				// The bid could also be valid if the amount is the same but the value is higher.
				if (newValue > this->_valueOfDice)
					break ;
			}
		}
		std::cout << "Invalid input! Please try again." << std::endl << std::endl;
	}
	this->_amountOfDice = newAmount;
	this->_valueOfDice = newValue;
}

// This function will check if the user's input has digits only.
bool	Game::_isAllDigits(std::string const &input)
{
	return input.find_first_not_of("0123456789") == std::string::npos;
}
