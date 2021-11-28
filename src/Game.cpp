#include "Game.hpp"		// Game.hpp
#include "Player.hpp"	// Player.hpp
#include <iostream>		// std::cout
#include <string>		// std::string
#include <sstream>		// std::stringstream
#include <cstdlib>		// system
#include <unistd.h>		// usleep
#include <vector>		// vector
#include <map>			// map

// Defines for readability
#define JOKER 7

// Default constructor.
Game::Game() : _totalAmountOfDiceInGame(0), _amountOfDice(1), _valueOfDice(1), _roundNumber(1), _indexPlayer(0), _palafico(false)
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

	std::vector<Player>::iterator it = this->_players.begin();

	while (it != this->_players.end())
	{
		if (it->getName() == name)
		{
			std::cout << "Invalid name! The player's name is already in the game." << std::endl;
			return ;
		}
		it++;
	}
	
	Player	newPlayer(name);

	this->_players.push_back(newPlayer);
	this->_totalAmountOfDiceInGame += newPlayer.getAmountDice();
	std::cout << "Player " << name << " is successfully added!" << std::endl;
}

// This function will delete all added players.
void	Game::deletePlayers()
{
	this->_players.clear();
	this->_playOrder.clear();
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
		this->_showPreviousBid();
		std::cout << "Turn " << this->_roundNumber << "! It is \033[1;32m";
		std::cout << currentPlayer->second << "'s\033[0m turn. Press enter to continue..." << std::endl;
		// This loop will wait for the current player to be ready for their turn.
		while (this->_options.readInput()[0] != '\0') {}
		// This loop will continue until the current player performed an action.
		std::cout << "Your dice rolls are:" << std::endl;
		this->_players[currentPlayer->first].showDice();
		this->_indexPlayer = (int)currentPlayer->first;
		while (true)
		{
			std::cout << "What would you like to call (bid/bluff/perudo)?: ";
			playerInput = this->_options.readInput();
			if (playerInput == "BID")
				this->_bid(currentPlayer->second);
			else if (playerInput == "BLUFF")
			{
				if (this->_roundNumber == 1)
				{
					std::cout << "You can't call bluff when nobody did a bid yet!" << std::endl;
					continue ;
				}
				this->_bluff(currentPlayer->second);
			}
			else if (playerInput == "PERUDO")
			{
				if (this->_roundNumber == 1)
				{
					std::cout << "You can't call perudo when nobody did a bid yet!" << std::endl;
					continue ;
				}
				this->_perudo(currentPlayer->second);
			}
			else
			{
				std::cout << "Invalid command, please try again." << std::endl;
				continue ;
			}
			std::cout << std::endl;
			break ;
		}
		// If the current player did a bid we go the next player.
		if (playerInput == "BID")
		{
			currentPlayer++;
			this->_roundNumber++;
		}
		else
		{
			currentPlayer = this->_playOrder.begin();
			for (int i = 0; i < this->_indexPlayer; i++)
				currentPlayer++;
			if (this->_playOrder.size() == 1)
			{
				std::cout << "\033[1;32m" << currentPlayer->second;
				std::cout << "\033[0m is the only player left and ";
				std::cout << "\033[1;33mWINS\033[0m te game! Congratulations." << std::endl;
				break ;
			}
			std::cout << "\033[1;32m" << currentPlayer->second;
			std::cout << "\033[0m will start the new round!" << std::endl;
			this->_waitForPlayers();
		}

		// If we reached the last player of a round we go back to the first player.
		if (currentPlayer == this->_playOrder.end())
			currentPlayer = this->_playOrder.begin();
		usleep(2000000);
	}
	this->deletePlayers();
}

// This function will free all the memory and exits the game after.
void		Game::exitGame()
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
	this->_waitForPlayers();
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
void	Game::_showPreviousBid()
{
	if (this->_roundNumber > 1)
	{
		std::cout << "The previous bid by \033[1;32m" << this->_previousPlayer;
		std::cout << "\033[0m was \033[1;31m[" << this->_amountOfDice << "] [";
		if (this->_valueOfDice == JOKER)
			std::cout << "J's]\033[0m" << std::endl << std::endl;
		else
			std::cout << this->_valueOfDice << "'s]\033[0m" << std::endl << std::endl;
	}
}

// This function is called when the current player wants to call a bid.
void	Game::_bid(std::string const &currentPlayer)
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
		if (this->_palafico == true)
			this->_valueOfDice = JOKER;
		else
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

		// Checks if the user bids more than the total amount of dice.
		if (newAmount > this->_totalAmountOfDiceInGame)
		{
			std::cout << "You really shouldn't bid more dice than there are actually in the game. Please, try again." << std::endl;
			continue ;
		}

		// Checks if the user wants to start a round with a Joker bid without palafico.
		if (joker == true && this->_palafico == false && this->_roundNumber == 1)
		{
			std::cout << "The first bid of a round can't be Jokers." << std::endl;
			continue ;
		}
		// Checks if the given values are valid (2-6 and jokers).
		if ((newValue >= 2 && newValue <= 6) || joker == true)
		{
			// If palafico is true, then the players can't change the value they are bidding.
			if (this->_palafico == true)
			{
				if (this->_roundNumber > 1 && newValue != this->_valueOfDice)
				{
					std::cout << "During palafico you can't change the value of the dice." << std::endl;
					continue ;
				}
			}
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
	this->_previousPlayer = currentPlayer;
}

// This function will count all the dice and summarizes who loses a die.
void	Game::_bluff(std::string const &currentPlayer)
{
	std::string	losingPlayer;
	bool		previousPlayer = false;
	size_t		totalValues = this->_countAllTheValues(currentPlayer, "bluff");

	// If there are less dice of the value in the game than the previous player bid,
	// the player who called bluff is correct.
	if (totalValues < this->_amountOfDice)
	{
		std::cout << "\033[1;32m" << currentPlayer << "\033[0m is correct and \033[1;32m";
		std::cout << this->_previousPlayer << "\033[0m will lose a die!" << std::endl;
		losingPlayer = this->_previousPlayer;
		previousPlayer = true;
	}
	else
	{
		std::cout << "\033[1;32m" << currentPlayer;
		std::cout << "\033[0m is not correct and they will lose a die!" << std::endl;
		losingPlayer = currentPlayer;
	}
	this->_adjustDice(losingPlayer, previousPlayer, false);
	this->_resetAndStartNewRound();
}

// This function will check if the perudo call is correct and give/remove a die accordingly.
void	Game::_perudo(std::string const &currentPlayer)
{
	size_t	totalValues = this->_countAllTheValues(currentPlayer, "perudo");
	bool	gainDie;

	// If there are exactly as many dice of the value in the game as the previous bid,
	// the player who called perudo will get one die back.
	if (totalValues == this->_amountOfDice)
	{
		std::cout << "\033[1;32m" << currentPlayer;
		std::cout << "\033[0m is correct and they will gain a die back!" << std::endl;
		gainDie = true;
	}
	else
	{
		std::cout << "\033[1;32m" << currentPlayer;
		std::cout << "\033[0m is not correct and they will lose a die!" << std::endl;
		gainDie = false;
	}
	this->_adjustDice(currentPlayer, false, gainDie);
	this->_resetAndStartNewRound();
}

// This function will check if the user's input has digits only.
bool	Game::_isAllDigits(std::string const &input)
{
	return input.find_first_not_of("0123456789") == std::string::npos;
}

// This function will remove a die from the losing player and checks if the player is game over.
void	Game::_adjustDice(std::string const &playerName, bool previousPlayer, bool addDie)
{
	std::vector<Player>::iterator	it = this->_players.begin();
	size_t							playerIndex = 0;

	this->_palafico = false;
	// This loop will find the player who has to gain or remove a die.
	while (it->getName() != playerName)
	{
		it++;
		playerIndex++;
	}
	// Check if someone loses a die or not.
	if (addDie == false)
	{
		this->_players[playerIndex].removeDieFromPlayer();
		this->_totalAmountOfDiceInGame--;
		// This will check if the losing player has any dice left.
		if (this->_players[playerIndex].getAmountDice() == 0)
		{
			std::cout << "\033[1;32m" << playerName;
			std::cout << "\033[0m has no dice left and is game over!" << std::endl;
			this->_decideStartPlayerNewRound(true, previousPlayer);
			this->_playOrder.erase(playerIndex);
			this->_players.erase(it);
		}
		else
			this->_decideStartPlayerNewRound(false, previousPlayer);
		// Check if the player who lost a die has only one die left for palafico.
		if (this->_players[playerIndex].getAmountDice() == 1)
		{
			this->_palafico = true;
			std::cout << "\033[1;32m" << playerName << "\033[0m has one die left. ";
			std::cout << "palafico will start next round." << std::endl;
		}
	}
	else
	{
		// Check if the player already has the maximum amount of dice.
		if (this->_players[playerIndex].getAmountDice() < 5)
		{
			this->_players[playerIndex].addDieToPlayer();
			this->_totalAmountOfDiceInGame++;
		}
		else
		{
			std::cout << "\033[1;32m" << playerName;
			std::cout << "\033[0m already has the maximum amount of dice. ";
			std::cout << "They can't gain another die." << std::endl;
		}
	}
}

// This function will reset the round to the default starting settings.
void	Game::_resetAndStartNewRound()
{
	for (size_t i = 0; i < this->_players.size(); i++)
		this->_players[i].rollDice();
	this->_previousPlayer.clear();
	this->_amountOfDice = 1;
	this->_valueOfDice = 1;
	this->_roundNumber = 1;
}

// This function will decide who has to start the new round.
void	Game::_decideStartPlayerNewRound(bool gameOver, bool previousPlayer)
{
	if (previousPlayer == true)
		this->_indexPlayer--;
	if (this->_indexPlayer == (int)this->_players.size() && gameOver == true)
		this->_indexPlayer = 0;
	else if (this->_indexPlayer == -1)
	{
		this->_indexPlayer = this->_players.size() - 1;
		if (gameOver == true)
			this->_indexPlayer = 0;
	}
}

// This function will count all the values of all the the player's dice
size_t	Game::_countAllTheValues(std::string const &currentPlayer, std::string const &call)
{
	std::vector<Player>::iterator	it = this->_players.begin();
	size_t							totalValues = 0;

	std::cout << "\033[1;32m" << currentPlayer << "\033[0m called \033[1;35m";
	std::cout << call << "\033[0m! Lets count the dice..." << std::endl << std::endl;
	// This loop will count from all the players how many dice of the last bid are in the game.
	while (it != this->_players.end())
	{
		totalValues += it->getAmountOfRolledValues(this->_valueOfDice, this->_palafico);
		it++;
	}
	usleep(1500000);
	std::cout << "There is a total of \033[1;36m[" << totalValues;
	std::cout << "]\033[0m die/dice of value \033[1;36m[";
	if (this->_valueOfDice == JOKER)
		std::cout << "J";
	else
		std::cout << this->_valueOfDice;
	std::cout << "]\033[0m in the game!" << std::endl << std::endl;
	return totalValues;
}

// This function will called when the game is waiting for everyone to be ready.
void	Game::_waitForPlayers()
{
	std::cout << "Press enter when everyone is ready..." << std::endl;
	while (this->_options.readInput()[0] != '\0') {}
}
