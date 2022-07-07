#include "Warlock.hpp"
#include <iostream>

Warlock::Warlock(std::string const &name, std::string const &title): _name(name), _title(title)
{
	std::cout << name << ": This looks like another boring day.\n";
};

Warlock::~Warlock()
{
	std::cout << _name << ": My job here is done!\n";
}
std::string	Warlock::getName() const
{
	return _name;
}

std::string	Warlock::getTitle() const
{
	return _title;
}

void	Warlock::setTitle(std::string const &title)
{
	_title = title;
}

void	Warlock::introduce() const
{
	std::cout << _name << ": I am " << _name << ", " << _title << "!\n";
}

void	Warlock::learnSpell(ASpell *spell)
{
	spellbook.push_back(spell);
}
	
void	Warlock::forgetSpell(std::string spell_name)
{
	for (std::vector<ASpell*>::iterator it = spellbook.begin(), last = spellbook.end(); it != last; ++it)
	{
		if ((*it)->getName() == spell_name)
		{
			spellbook.erase(it);
			return ;
		}
	}
}

void	Warlock::launchSpell(std::string spell_name, ATarget &target)
{
	for (std::vector<ASpell*>::iterator it = spellbook.begin(), last = spellbook.end(); it != last; ++it)
	{
		if ((*it)->getName() == spell_name)
		{
			(*it)->launch(target);
			return ;
		}
	}
}
