#include "ASpell.hpp"

ASpell::ASpell(const std::string &name, const std::string &effects): name(name), effects(effects) {};



ASpell::~ASpell() {}

const std::string	&ASpell::getName() const
{
	return name;
}

const std::string	&ASpell::getEffects() const
{
	return effects;
}

ASpell &ASpell::operator=(const ASpell &other)
{
	name = other.name;
	effects = other.effects;
	return *this;
}

void	ASpell::launch(const ATarget &target) const
{
	target.getHitBypell(*this);
}