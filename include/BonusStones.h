#pragma once
#include <SFML/Graphics.hpp>
#include "ImmobileObject.h"
#include "Bonus.h"

class Controller;

class BonusStones : public Bonus
{
public:
	BonusStones() = default;
	
	virtual bool collisionConsequence(Controller&) override;
};