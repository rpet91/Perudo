#include "Player.hpp"	// Player.hpp
#include <iostream>		// std::cout
#include <string>		// std::string
#include <vector>		// std::vector
#include <cstdlib>		// rand

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
	this->_name = src._name;
	this->_dice = src._dice;
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

// This function will roll all the dice.
void				Player::rollDice()
{
	for (size_t i = 0; i < this->getAmountDice(); i++)
		this->_dice[i] = rand() % 6 + 1;
}

void				Player::showDice() const
{
	std::cout << this->_name << " rolled:" << std::endl << std::endl;
	for (size_t i = 0; i < this->getAmountDice(); i++)
		this->_printDice(this->_dice[i]);
}

void				Player::_printDice(int diceNumber) const
{
	if (diceNumber == 1)
	{
		std::cout << ".---------." << std::endl;
		std::cout << "|   ----  |" << std::endl;
		std::cout << "|      |  |" << std::endl;
		std::cout << "|      |  |" << std::endl;
		std::cout << "|      |  |" << std::endl;
		std::cout << "|   \\__/  |" << std::endl;
		std::cout << "'---------'" << std::endl;
	}
	else if (diceNumber == 2)
	{
		std::cout << ".---------." << std::endl;
		std::cout << "|       O |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "| O       |" << std::endl;
		std::cout << "'---------'" << std::endl;
	}
	else if (diceNumber == 3)
	{
		std::cout << ".---------." << std::endl;
		std::cout << "|       O |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "|    O    |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "| O       |" << std::endl;
		std::cout << "'---------'" << std::endl;
	}
	else if (diceNumber == 4)
	{
		std::cout << ".---------." << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "'---------'" << std::endl;
	}
	else if (diceNumber == 5)
	{
		std::cout << ".---------." << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "|    O    |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "'---------'" << std::endl;
	}
	else if (diceNumber == 6)
	{
		std::cout << ".---------." << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "|         |" << std::endl;
		std::cout << "| O     O |" << std::endl;
		std::cout << "'---------'" << std::endl;
	}
	std::cout << std::endl;
}
