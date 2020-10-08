#pragma once
#include <SFML/Graphics.hpp>
#include "ImmobileObject.h"

class Stone : public ImmobileObject
{
public:
	Stone(sf::Texture* backTexture, sf::Texture* stoneTexture, int row, int col, double r)
		: ImmobileObject(backTexture, stoneTexture, row, col, r)
	{
		getObjectSprite().setPosition(getLocation() + sf::Vector2f(10, 10));
	}
	virtual bool collisionConsequence(Controller&) override;
};