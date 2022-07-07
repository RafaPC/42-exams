#include "Brickwall.hpp"

BrickWall::BrickWall(): ATarget("Inconspicuous Red-brick Wall") {};

BrickWall *BrickWall::clone() const
{
	return new BrickWall(*this);
}