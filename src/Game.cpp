#include "Game.hpp"		// Game.hpp
#include "Player.hpp"	// Player.hpp
#include <iostream>		// std::cout
#include <string>		// std::string
#include <cstdlib>		// system

#include <map>	// debug

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

/*	for (size_t i = 0; i < this->_players.size(); i++)
	{
		system("clear");
		std::cout << "----------------------------------------------------" << std::endl;
		this->_players[i].showDice();
	}*/
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
	this->_decideStartPlayer();
}

void	Game::_decideStartPlayer()
{
	std::map<size_t, std::string>::iterator it;
	size_t	i = 0;
	int		randomPlayer = 0;

	this->_playOrder.clear();
	while (i < this->_players.size())
	{
		randomPlayer = rand() % this->_players.size();
		for (it = this->_playOrder.begin(); it != this->_playOrder.end(); it++)
		{
			if (this->_players[randomPlayer].getName() == it->second)
				break ;
		}
		if (it == this->_playOrder.end())
		{
			this->_playOrder[i] = this->_players[randomPlayer].getName();
			i++;
		}
	}
/*	for (std::map<size_t, std::string>::iterator it = this->_playOrder.begin(); it != this->_playOrder.end(); it++)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}*/
}
