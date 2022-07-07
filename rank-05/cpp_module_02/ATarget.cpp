#include "ATarget.hpp"
#include <iostream>

const std::string	&ATarget::getType() const
{
	return type;
}

ATarget::ATarget() {};
ATarget::ATarget(const std::string &type): type(type) {};

ATarget &ATarget::operator=(const ATarget &other)
{
	type = other.type;
	return *this;
}

ATarget::~ATarget() {};

void	ATarget::getHitBypell(const ASpell &spell) const
{
	std::cout << type << " has been " << spell.getEffects() << "!\n";
}
