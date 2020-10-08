#pragma once
#include <SFML/Graphics.hpp>
#include "ImmobileObject.h"

class Diamond : public ImmobileObject
{
public:
	Diamond(sf::Texture* backTexture, sf::Texture* diaTexture, int row, int col, double r) 
		: ImmobileObject(backTexture, diaTexture, row, col, r) 
	{   
		getObjectSprite().setPosition(getLocation() + sf::Vector2f(10, 10));
	}

	virtual bool collisionConsequence(Controller&) override;
};