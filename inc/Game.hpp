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
		void	_showPreviousBid(std::string const &currentPlayer) const;
		void	_bid();
		bool	_isAllDigits(std::string const &input);

		Options							_options;
		std::vector<Player>				_players;
		std::map<size_t, std::string>	_playOrder;
		size_t							_amountOfDice;
		size_t							_valueOfDice;
		size_t							_roundNumber;
		bool							_palifico;
};

#endif
