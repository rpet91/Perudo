#ifndef GAME_HPP
# define GAME_HPP

# include "Player.hpp"	// Player.hpp
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

		std::vector<Player>				_players;
		std::map<size_t, std::string>	_playOrder;
};

#endif
