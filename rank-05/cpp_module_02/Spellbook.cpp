#include "Spellbook.hpp"


Spellbook::Spellbook()
{

}

Spellbook::~Spellbook()
{

}

void Spellbook::learnSpell(ASpell* spell)
{
	_book.push_back(spell);
}

void Spellbook::forgetSpell(std::string const &spell_name)
{
	for (std::vector<ASpell*>::iterator it = _book.begin(), last = _book.end(); it != last; ++it)
	{
		if ((*it)->getName() == spell_name)
		{
			_book.erase(it);
			return ;
		}
	}
}

ASpell* Spellbook::createSpell(std::string const &spell_name)
{
	for (std::vector<ASpell*>::iterator it = _book.begin(), last = _book.end(); it != last; ++it)
	{
		if ((*it)->getName() == spell_name)
			return (*it);
	}
	return NULL;
}