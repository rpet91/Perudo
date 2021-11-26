#ifndef GAME_HPP
# define GAME_HPP

# include "Player.hpp"	// Player.hpp
# include "Options.hpp"	// Options.hpp
# include <vector>		// std::vector
# include <map>			// std::map
# include <string>		// std::string

class Game
{
	public:
		Game();
		virtual ~Game();

		void	listPlayers() const;
		void	addPlayer(std::string const &name);
		void	deletePlayers();
		void	runGame();
		void	exitGame();

	private:
		Game(Game const &src);
		Game	&operator=(Game const &src);

		void	_setupGame();
		void	_decidePlayOrder();
		void	_showPreviousBid();
		void	_bid(std::string const &currentPlayer);
		void	_bluff(std::string const &currentPlayer);
		bool	_isAllDigits(std::string const &input);
		void	_substractDie(std::string const &playerName, bool previousPlayer);
		void	_resetAndStartNewRound();
		void	_decideStartPlayerNewRound(bool gameOver, bool previousPlayer);
		void	_waitForPlayers();

		Options							_options;
		std::vector<Player>				_players;
		std::map<size_t, std::string>	_playOrder;
		std::string						_previousPlayer;
		size_t							_totalAmountOfDiceInGame;
		size_t							_amountOfDice;
		size_t							_valueOfDice;
		size_t							_roundNumber;
		int								_indexPlayer;
		bool							_palifico;
};

#endif
