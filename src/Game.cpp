#include "Game.hpp"		// Game.hpp
#include "Player.hpp"	// Player.hpp
#include "Options.hpp"	// Options.hpp
#include <iostream>		// std::cout
#include <string>		// std::string
#include <cstdlib>		// system
#include <unistd.h>		// usleep
#include <vector>		// vector
#include <map>			// map

// Default constructor.
Game::Game()
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
	Options									options;

	// This loop will continue until the game is finished.
	while (true)
	{
		//system("clear");
		std::cout << "It is " << currentPlayer->second << "'s turn! Press enter to continue..." << std::endl;
		// This loop will wait for the current player to press enter.
		while (true)
		{
			if (options.readInput() == "ENTER")
				break ;
		}
		// This loop will continue until the current player performed an action.
		std::cout << "Your dice rolls are:" << std::endl;
		this->_players[currentPlayer->first].showDice();
		while (true)
		{
			std::cout << "What would you like to call (bid, bluff, perudo)?:";
			playerInput = options.readInput();
			if (playerInput == "BID")
				std::cout << "you chose bid" << std::endl;
			else if (playerInput == "BLUFF")
				std::cout << "you chose bluff" << std::endl;
			else if (playerInput == "PERUDO")
				std::cout << "you chose perudo" << std::endl;
			else if (std::cin.eof())
				return ;
			else
				std::cout << "Invalid command, please try again." << std::endl;
			std::cout << std::endl;
			break ;
		}
		currentPlayer++;

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

void	Game::_setupGame()
{
	for (size_t i = 0; i < this->_players.size(); i++)
		this->_players[i].rollDice();
	this->_decidePlayOrder();
	std::cout << "Setup complete! Game is starting now..." << std::endl << std::endl;
	//usleep(2000000);
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
	{
		std::cout << "- " << it->getName() << std::endl;
	}
}
