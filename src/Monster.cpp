#include "Monster.h"
#include "Controller.h"
#include "Board.h"
#include "Wall.h"
#include "Stone.h"
#include <typeinfo>

Monster::Monster(sf::Vector2f direction, sf::Vector2f bounds, sf::Texture* texture, int row, int col, double ratio)
	: MovableCharacter(direction, bounds, texture, row, col, ratio)
{
	m_originalPos.x = row;
	m_originalPos.y = col;
}

void Monster::move(sf::Time& deltaTime, Controller& controller, Board& board)
{
	if (!(*this).isOutOfBounds())
		getSprite().move(getDirection() * deltaTime.asSeconds());

	for (int i = 0; i < controller.getRows(); i++)
	{														//runs through game board
		for (int j = 0; j < controller.getCols(); j++)
		{
			Wall* wall = dynamic_cast<Wall*>(controller.getBoard().getObject(i, j));
			if (wall)
			{
				if (controller.getBoard().getObject(i, j)->getObjectSprite().getGlobalBounds().intersects(this->getSprite().getGlobalBounds()))
					getSprite().move(-getDirection() * deltaTime.asSeconds());
			}
																//stops monsters when they run into a wall or stone
			else
			{
				Stone* stone = dynamic_cast<Stone*>(controller.getBoard().getObject(i, j));
				
				if (stone)
				{
					if (controller.getBoard().getObject(i, j)->getObjectSprite().getGlobalBounds().intersects(this->getSprite().getGlobalBounds()))
						getSprite().move(-getDirection() * deltaTime.asSeconds());
				}
			}
		}
	}
}

void Monster::setEaten(Controller& controller)
{
	if ((*this).getSprite().getGlobalBounds().intersects(controller.getDigger().getSprite().getGlobalBounds()))
		controller.setEaten();				//announces that the monster has eaten the digger :(
}