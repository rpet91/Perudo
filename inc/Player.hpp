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
		Player	&operator=(Player const &src);

		std::string const	&getName() const;
		size_t				getAmountDice() const;
		size_t				getAmountOfRolledValues(int value, bool palifico);
		void				rollDice();
		void				showDice() const;
		void				removeDieFromPlayer();
		void				addDieToPlayer();

	private:
		Player();

		void	_printDice(int diceNumber) const;

		std::string			_name;
		std::vector<int>	_dice;

};

#endif
