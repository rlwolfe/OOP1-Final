#pragma once
#include <SFML/Graphics.hpp>
#include "ImmobileObject.h"

class Bonus : public ImmobileObject
{
public:
	Bonus(sf::Texture* bonusTexture, sf::Texture* backTexture, int row, int col, double r)
		: ImmobileObject(NULL, backTexture, row, col, r) { }

	Bonus() = default;

	Bonus* makeSpecificBonus(sf::Texture*, sf::Texture*, sf::Texture*, int);
	
	void displayBonusAmount(string, Controller&);
};