#pragma once
#include <SFML/Graphics.hpp>

#include "ImmobileObject.h"
#include "Bonus.h"
class Controller;

class BonusTime : public Bonus
{
public:
	BonusTime() = default;

	virtual bool collisionConsequence(Controller&) override;
};