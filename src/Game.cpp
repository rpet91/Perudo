#include "Game.hpp"		// Game.hpp
#include "Player.hpp"	// Player.hpp
#include <iostream>		// std::cout
#include <string>		// std::string
#include <cstdlib>		// system

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
		std::cout << "The current added players in this game are:" << std::endl;
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

// This function will run the game.
void	Game::runGame()
{
	if (this->_players.size() <= 1)
	{
		std::cout << "There are not enough players to start the game! Please add more players." << std::endl;
		return ;
	}
	this->_setupGame();

	for (size_t i = 0; i < this->_players.size(); i++)
	{
		system("clear");
		std::cout << "----------------------------------------------------" << std::endl;
		this->_players[i].showDice();
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
}
