#pragma once

#include <SFML/Graphics.hpp>
#include "ImmobileObject.h"
#include "Bonus.h"
class Controller;

class BonusPoints : public Bonus
{	
public:
	BonusPoints() = default;
	
	virtual bool collisionConsequence(Controller&) override; 
};