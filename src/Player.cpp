#include "Player.hpp"	// Player.hpp
#include <iostream>		// std::cout
#include <string>		// std::string
#include <vector>		// std::vector
#include <cstdlib>		// rand

#define JOKER 1			// define for readability

// Constructor when a new player is created.
Player::Player(std::string const &name) : _name(name)
{
	for (int i = 0; i < 5; i++)
		this->_dice.push_back(0);
}

// Default constructor.
Player::~Player()
{
}

// Copy constructor.
Player::Player(Player const &src)
{
	*this = src;
}

// Assignment operator.
Player	&Player::operator=(Player const &src)
{
	this->_name = src._name;
	this->_dice = src._dice;
	return *this;
}

// This function will return the name of the player.
std::string const	&Player::getName() const
{
	return this->_name;
}

// This function will return the amount of dice the player has.
size_t				Player::getAmountDice() const
{
	return this->_dice.size();
}

// This function will count how many dice you rolled of the given value.
size_t				Player::getAmountOfRolledValues(int value, bool palifico)
{
	size_t	total = 0;

	this->showDice();
	for (size_t i = 0; i < this->getAmountDice(); i++)
	{
		if (value == this->_dice[i] || (this->_dice[i] == JOKER && palifico == false))
			total++;
	}
	return total;
}

// This function will roll all the dice.
void				Player::rollDice()
{
	for (size_t i = 0; i < this->getAmountDice(); i++)
		this->_dice[i] = rand() % 6 + 1;
}

// This function will print out your dice rolls.
void				Player::showDice() const
{
	std::cout << this->_name << " rolled:" << std::endl;
	for (size_t i = 0; i < this->getAmountDice(); i++)
		this->_printDice(this->_dice[i]);
	std::cout << std::endl << std::endl;
}

// This function will remove a die from the losing player.
void				Player::removeDieFromPlayer()
{
	this->_dice.pop_back();
}

void				Player::addDieToPlayer()
{
	this->_dice.push_back(0);
}

// This function will print all the dice the player rolled.
void				Player::_printDice(int diceNumber) const
{
	if (diceNumber == JOKER)
	{
		std::cout << "[J] ";
	/*	std::cout << ".---------." << std::endl;
		std::cout << "|   ----  |" << std::endl;
		std::cout << "|      |  |" << std::endl;
		std::cout << "|      |  |" << std::endl;
		std::cout << "|      |  |" << std::endl;
		std::cout << "|   \\__/  |" << std::endl;
		std::cout << "'---------'" << std::endl;*/
	}
	else if (diceNumber == 2)
	{
		std::cout << "[2] ";
	/*	std::cout << ".---------." << std::endl;
		std::cout << "|       O |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "| O       |" << std::endl;
		std::cout << "'---------'" << std::endl;*/
	}
	else if (diceNumber == 3)
	{
		std::cout << "[3] ";
	/*	std::cout << ".---------." << std::endl;
		std::cout << "|       O |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "|    O    |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "| O       |" << std::endl;
		std::cout << "'---------'" << std::endl;*/
	}
	else if (diceNumber == 4)
	{
		std::cout << "[4] ";
	/*	std::cout << ".---------." << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "'---------'" << std::endl;*/
	}
	else if (diceNumber == 5)
	{
		std::cout << "[5] ";
	/*	std::cout << ".---------." << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "|    O    |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "'---------'" << std::endl;*/
	}
	else if (diceNumber == 6)
	{
		std::cout << "[6] ";
	/*	std::cout << ".---------." << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "'---------'" << std::endl;*/
	}
}
