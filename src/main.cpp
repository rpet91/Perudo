#include "Options.hpp"	// Options.hpp
#include "Game.hpp"		// Game.hpp
#include <iostream>		// std::cout
#include <string>		// std:string
#include <cctype>		// std::toupper
#include <algorithm>	// std::transform
#include <cstdlib>		// EXIT_SUCCESS, srand
#include <ctime>		// time

std::string	readInput()
{
	std::string		input;

	std::cin >> input;
	std::transform(input.begin(), input.end(), input.begin(), toupper);
	return input;
}

int	main()
{
	std::cout << std::endl << "Welcome to Perudo! A game of dice and bluffing. Are you the best at reading your opponents?" << std::endl;
	std::cout << "Type \"help\" to see a list of options." << std::endl << std::endl;

	std::string		input;
	Options			options;
	Game			game;

	srand(time(0));
	while (true)
	{
		std::cout << "What would like you to do?: ";
		input = readInput();
		if (input == "HELP")
			options.inputHelp();
		else if (input == "RULES")
			options.inputRules();
		else if (input == "LIST_PLAYERS")
			game.listPlayers();
		else if (input == "DELETE_PLAYERS")
			game.deletePlayers();
		else if (input == "ADD")
		{
			std::cout << "Adding a player.." << std::endl;
			std::cout << "What's the player's name?: ";
			input = readInput();
			game.addPlayer(input);
		}
		else if (input == "START")
			game.runGame();
		else if (input == "EXIT" || std::cin.eof())
		{
			if (std::cin.eof())
				std::cout << std::endl;
			game.exitGame();
			break ;
		}
		else
			std::cout << "Invalid command. Type \"help\" for a list of options." << std::endl;
		std::cout << std::endl;
	}
	return (EXIT_SUCCESS);
}
