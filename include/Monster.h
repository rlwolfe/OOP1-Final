#pragma once
#include <SFML/Graphics.hpp>

#include "MovableCharacter.h"
#include "Board.h"

class Monster : public MovableCharacter
{
public:
	Monster() = default;
	Monster(const Monster&) = default;
	Monster(sf::Vector2f, sf::Vector2f, sf::Texture*, int, int, double);
	
	virtual void draw(sf::RenderWindow&) {}
	virtual void move(sf::Time&, Controller&, Board&);
	virtual void chase(sf::Time&, Controller&, Board&, int) { }
	
	void setEaten(Controller&);
	bool getEaten() { return m_eaten; }
	
	sf::Vector2f getOriginalPos() { return m_originalPos; }

private:
	bool m_eaten = false;
	sf::Vector2f m_originalPos;
};