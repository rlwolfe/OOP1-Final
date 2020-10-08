#pragma once
#include "Monster.h"

class smartMonster : public Monster
{
public:
	smartMonster(sf::Vector2f direction, sf::Vector2f bounds, sf::Texture* texture, int row, int col, double ratio);
	
	virtual void chase(sf::Time&, Controller&, Board&, int);
};
