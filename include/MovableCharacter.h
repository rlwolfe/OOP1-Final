#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Board;
class Controller;
class MovableCharacter : public GameObject {

public:
	MovableCharacter() = default;
	MovableCharacter(const MovableCharacter&) = default;

	MovableCharacter(sf::Vector2f direction, sf::Vector2f bounds, sf::Texture* texture, int row, int col, double ratio)
		: m_direction(direction), m_bounds(bounds), GameObject(texture, row, col, ratio)
	{
		m_texture = texture;
	}

	void setDirection(sf::Vector2f direction)
	{
		m_direction = direction; 
	}

	sf::Vector2f getDirection() { return m_direction; }

	sf::Texture* getTexture() { return m_texture; }
	
	virtual void move(sf::Time&, Controller&, Board&) = 0;

	void draw(sf::RenderWindow&) {}
	bool isOutOfBounds();
    
private:
	sf::Vector2f m_direction;
	sf::Vector2f m_bounds;

	sf::Texture* m_texture;
};