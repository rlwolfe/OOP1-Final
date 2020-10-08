#pragma once
#include <SFML/Graphics.hpp>
#include "MovableCharacter.h"

class Board;

class Digger : public MovableCharacter
{
public:
	Digger() = default;
	Digger(const Digger&) = default;
	Digger(sf::Vector2f direction, sf::Vector2f bounds, sf::Texture* texture, int row, int col, double);
	
	virtual void draw(sf::RenderWindow&) {}
	virtual void move(sf::Time&, Controller&, Board&);
	
	void changeDirection(sf::Keyboard::Key, Controller&, Board&);
	void decLives() { m_lives--; }
	void setLives(int newLives) { m_lives = newLives;}
	unsigned int getLives() { return m_lives; }

private:
	bool m_firstMove;
	unsigned int m_lives;
};