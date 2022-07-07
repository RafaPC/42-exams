#ifndef Fireball_HPP
# define Fireball_HPP

#include "ASpell.hpp"

class Fireball: public ASpell
{
private:
	/* data */
public:
	Fireball();
	virtual ~Fireball();
	virtual Fireball* clone() const;
};

#endif