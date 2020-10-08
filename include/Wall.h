#pragma once
#include <SFML/Graphics.hpp>
#include "ImmobileObject.h"

class Wall : public ImmobileObject
{
public:
	Wall(sf::Texture* backTexture, sf::Texture* wallTexture, int row, int col, double r)
		: ImmobileObject(backTexture, wallTexture, row, col, r)
	{
		getObjectSprite().setOrigin(0, 0);
	}
	virtual bool collisionConsequence(Controller&) override;
};