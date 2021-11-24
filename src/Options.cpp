#include "Options.hpp"	// Options.hpp
#include <iostream>		// std::cout
#include <string>		// std::string
#include <cctype>		// std::toupper
#include <algorithm>	// std::transform

// Default constructor.
Options::Options()
{
}

// Default destructor.
Options::~Options()
{
}

// This function will read the user's input and transform the string to uppercase.
std::string		Options::readInput()
{
	std::string		input;

	std::cin >> input;
	std::transform(input.begin(), input.end(), input.begin(), toupper);
	return input;
}

// This function will show the user the rules about the game.
void			Options::inputRules() const
{
	std::cout << "--------------------------------------------------------------------" << std::endl << std::endl;
	std::cout << "This ancient Peruvian dice game is played with 2 to 6 players. It is a skillful game of guesswork, bluff and luck." << std::endl << std::endl;

	std::cout << "The goal of the game is to be the last player with dice." << std::endl << std::endl;

	std::cout << "Simultaneously, all players shake their 5 dice in their cups and turn them over on the table, using the cup to conceal their dice from the other players. Having looked at his or her own dice the first player makes a call based on an estimate of how many dice of a particular number there are under all	the cups on the table. Two factors should be considered when making a call:" << std::endl << std::endl;

	std::cout << "1. The total number of dice on the table: If there are six players, for example, then there will be a total of thirty dice in play. The probability therefore is that there will be five dice of any given value: five twos, five threes, etc." << std::endl << std::endl;
	
	std::cout << "2. All ones - known as “aces” - are wild and are counted as the value of whichever bid is made. Thus a call of “seven fours” is based on a prediction that there will be a total of seven dice with a value of either four or ace." << std::endl << std::endl;
	
	std::cout << "• The player to the opener’s left then makes a call and the bidding proceeds around the table. Each bid must be higher than the last. So a call of “seven fours” can be followed by, say, “seven fives” or by “eight twos”, but not by “six sixes” or by “seven twos”. Jump bids (“nine threes” for example) can also be made, with the intention of raising the stakes for the next player." << std::endl << std::endl;

	std::cout << "• If a player feels unable to raise the bidding any further, the call of “dudo”(meaning “I doubt” in Spanish) is made. This halts the bidding process and the last call made is accepted." << std::endl << std::endl;
	
	std::cout << "• All players then uncover their dice (the player who called dudo first, the player who made the final bid last). Dice of the relevant value are counted and added to the number of aces revealed. If the call was, say, “seven twos” and there are fewer than seven dice showing either two or ace, then the player who made the bid loses one die. If there are seven (or more) twos and aces showing, then the player who called dudo loses one die. All dice that are removed from the game should be placed in the pouch so that the total number of dice in play is hidden." << std::endl << std::endl;
	
	std::cout << "• The player who loses a die starts the bidding process in the next round." << std::endl << std::endl;
	std::cout << "--------------------------------------------------------------------" << std::endl << std::endl;
}

// This function will show the user a list of options they van use as a command.
void			Options::inputHelp() const
{
	std::cout << "The following options are availabe:" << std::endl;
	std::cout << "- help" << std::endl;
	std::cout << "- rules" << std::endl;
	std::cout << "- list_players" << std::endl;
	std::cout << "- delete_players" << std::endl;
	std::cout << "- add" << std::endl;
	std::cout << "- start" << std::endl;
	std::cout << "- exit" << std::endl;
}
