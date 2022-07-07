#include "TargetGenerator.hpp"


TargetGenerator::TargetGenerator()
{

}

void TargetGenerator::learnTargetType(ATarget* target)
{
	for (size_t i = 0; i < _targets.size(); ++i)
		if (_targets[i]->getType() == target->getType())
			return ;
	_targets.push_back(target->clone());
}

void TargetGenerator::forgetTargetType(std::string const &type)
{
	for (std::vector<ATarget *>::iterator it = _targets.begin(), last = _targets.end(); it != last; it++)
		if ((*it)->getType() == type)
		{
			delete *it;
			_targets.erase(it);
			return ;
		}
}

ATarget* TargetGenerator::createTarget(std::string const &type)
{
	for (size_t i = 0; i < _targets.size(); i++)
		if (_targets[i]->getType() == type)
			return _targets[i];
	return (NULL);
}
