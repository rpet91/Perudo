#ifndef GAME_HPP
# define GAME_HPP

# include "Player.hpp"	// Player.hpp
# include <vector>		// Vector.hpp
# include <string>		// std::string

class Game
{
	public:
		Game();
		virtual ~Game();

		void	listPlayers() const;
		void	addPlayer(std::string const &name);
		void	runGame();
		void	exitGame();

	private:
		Game(Game const &src);
		Game	&operator=(Game const &src);

		void	_setupGame();

		std::vector<Player>		_players;
};

#endif
