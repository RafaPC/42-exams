#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <string>

class Warlock
{
private:
	std::string _name;
	std::string _title;
public:
	Warlock(std::string const &name, std::string const &title);
	~Warlock();
	std::string	getName(void) const;
	std::string getTitle(void) const;
	void	setTitle(std::string const &title);
	void	introduce() const;
};

#endif