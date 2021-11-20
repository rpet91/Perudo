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

		void	addPlayer(std::string const &name);
		void	listPlayers() const;
		void	exitGame();

	private:
		Game(Game const &src);
		Game	&operator=(Game const &src);

		size_t					_amountPlayers;
		std::vector<Player>		_players;
};

#endif
