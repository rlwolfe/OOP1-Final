#include "GameObject.h"

GameObject::GameObject(sf::Texture* texture, int row, int col, double ratio)
{
	m_sprite = (sf::Sprite(*texture));
	
	m_coordinance.x = col;				//assigns location of object
	m_coordinance.y = row;

	m_location.x = col * (m_sprite.getGlobalBounds().width + ratio);
	m_location.y = row * (m_sprite.getGlobalBounds().height + ratio);
	
	m_sprite.setPosition(m_location);
}
