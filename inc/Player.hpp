#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <string>	// std::string
# include <vector>	// std::vector

class Player
{
	public:
		Player(std::string const &name);
		virtual ~Player();
		Player(Player const &src);

		std::string const	&getName() const;

	private:
		Player();
		Player	&operator=(Player const &src);

		std::string			_name;
		std::vector<int>	_dice;

};

#endif
