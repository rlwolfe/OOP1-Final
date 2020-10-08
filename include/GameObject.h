#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using std::string;
class Controller;

class GameObject
{
public:
	GameObject() = default;
	GameObject(sf::Texture*, int, int, double);

	virtual void draw(sf::RenderWindow&) = 0;
	virtual bool collisionConsequence(Controller&) { return true; }
	
	sf::Sprite& getSprite() { return m_sprite;  }
	sf::Vector2f getLocation() { return m_location; }
	sf::Vector2f getCoordinance() { return m_coordinance; }

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_location;
	sf::Vector2f m_coordinance;
};