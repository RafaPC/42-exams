#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <string>
#include "ASpell.hpp"
#include "Spellbook.hpp"

class Warlock
{
private:
	std::string _name;
	std::string _title;
	Spellbook _spellbook;
	Warlock& operator= (const Warlock &);

public:
	Warlock(std::string const &name, std::string const &title);
	~Warlock();
	std::string	getName(void) const;
	std::string getTitle(void) const;
	void	setTitle(std::string const &title);
	void	introduce() const;
	void	learnSpell(ASpell *spell);
	void	forgetSpell(std::string spell_name);
	void	launchSpell(std::string spell_name, ATarget &target);
};

#endif