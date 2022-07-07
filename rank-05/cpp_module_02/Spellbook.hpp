#ifndef spellbook
# define spellbook

#include "ASpell.hpp"
#include <string>
#include <vector>

class Spellbook
{
private:
	std::vector<ASpell*> _book;
public:
	Spellbook();
	~Spellbook();
	void learnSpell(ASpell*);
	void forgetSpell(std::string const &);
	ASpell* createSpell(std::string const &);
};

#endif