#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class ImmobileObject : public GameObject {

public:
	ImmobileObject(sf::Texture* objTexture, sf::Texture* backTexture, int row, int col, double r);
	ImmobileObject() = default;
	
	virtual int didCollide(Controller&);
	
	void draw(sf::RenderWindow&);

	sf::Sprite& getObjectSprite() { return m_objectSprite; }

private:
	sf::Sprite m_objectSprite;
};