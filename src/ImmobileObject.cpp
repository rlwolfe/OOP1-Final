#include "ImmobileObject.h"
#include "Controller.h"
#include "Monster.h"
#include "Wall.h"

#include <typeinfo>


ImmobileObject::ImmobileObject(sf::Texture* objTexture, sf::Texture* backTexture, int row, int col, double r)
: GameObject(backTexture, row, col, r)
{   
	if (!objTexture == NULL)
	{
		m_objectSprite = (sf::Sprite(*objTexture));
		m_objectSprite.setPosition(sf::Vector2f(getLocation()));			//allocates sprite to object
	}
}

void ImmobileObject::draw(sf::RenderWindow& window)
{   
	window.draw(getSprite());								//draws the object on the game board
	window.draw(m_objectSprite);
}

int ImmobileObject::didCollide(Controller& controller) 
{  
	if(m_objectSprite.getGlobalBounds().intersects(controller.getDigger().getSprite().getGlobalBounds()))
		return 1;
								//confirms if there was or wasn't a collision on the board
	return 0;
}

