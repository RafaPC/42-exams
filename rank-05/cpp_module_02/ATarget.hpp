#ifndef ATARGET_HPP
# define ATARGET_HPP

#include <string>
#include "ASpell.hpp"

class ASpell;

class ATarget
{
protected:
	std::string type;
public:
	ATarget();
	ATarget(const std::string &type);
	ATarget &operator=(const ATarget &other);
	virtual ~ATarget();
	const std::string	&getType() const;
	virtual ATarget *clone() const = 0;
	void	getHitBypell(const ASpell &spell) const;
};

#endif