#ifndef Polymorph_HPP
# define Polymorph_HPP

#include "ASpell.hpp"

class Polymorph: public ASpell
{
private:
	/* data */
public:
	Polymorph();
	virtual ~Polymorph();
	virtual Polymorph* clone() const;
};

#endif