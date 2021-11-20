#include "Player.hpp"	// Player.hpp
#include <iostream>		// std::cout
#include <string>		// std::string
#include <vector>		// std::vector

Player::Player(std::string const &name) : _name(name)
{
	for (int i = 0; i < 5; i++)
		this->_dice.push_back(0);
}

Player::~Player()
{
}

Player::Player(Player const &src)
{
	this->_name = src._name;
	this->_dice = src._dice;
}

std::string const	&Player::getName() const
{
	return this->_name;
}
