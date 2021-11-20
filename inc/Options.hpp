#ifndef OPTIONS_HPP
# define OPTIONS_HPP

class Options
{
	public:
		Options();
		virtual ~Options();

		void	inputHelp() const;
		void	inputRules() const;
		void	inputExit() const;
	
	private:
		Options(Options const &src);
		Options	&operator=(Options const &src);
};

#endif
