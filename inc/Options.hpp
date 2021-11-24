#ifndef OPTIONS_HPP
# define OPTIONS_HPP

# include <string>	// std::string

class Options
{
	public:
		Options();
		virtual ~Options();

		std::string	readInput();
		void		inputRules() const;
		void		inputHelp() const;
	
	private:
		Options(Options const &src);
		Options	&operator=(Options const &src);
};

#endif
