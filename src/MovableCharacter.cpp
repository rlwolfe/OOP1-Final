#include "MovableCharacter.h"
#include "Constsants.h"

bool MovableCharacter::isOutOfBounds()				//confirms that the little dude didn't run away
{   
	if (getSprite().getPosition().x > (getSprite().getGlobalBounds().width + 10.0 ) * (m_bounds.y - RATIO_BW_MOVABLE) && getDirection() == sf::Vector2f(DIGR_SPEED_IN_PXLS, 0))
		return true;

	if (getSprite().getPosition().x < getSprite().getGlobalBounds().width * 0 && getDirection() == sf::Vector2f(-DIGR_SPEED_IN_PXLS, 0))
		return true;
	 
	if (getSprite().getPosition().y > (getSprite().getGlobalBounds().height + 10.0 ) * (m_bounds.x - RATIO_BW_MOVABLE) && getDirection() == sf::Vector2f(0, DIGR_SPEED_IN_PXLS))
		return true;

	if (getSprite().getPosition().y < getSprite().getGlobalBounds().height * 0 && getDirection() == sf::Vector2f(0, -DIGR_SPEED_IN_PXLS))
		return true;

	return false;
}

