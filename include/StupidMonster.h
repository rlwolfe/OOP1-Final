#pragma once
#include "Monster.h"

class stupidMonster : public Monster
{	
public:
	stupidMonster(sf::Vector2f direction, sf::Vector2f bounds, sf::Texture * texture, int row, int col, double ratio);

	virtual void chase(sf::Time&, Controller&, Board&, int);
};
