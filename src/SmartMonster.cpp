#include "SmartMonster.h"
#include "Controller.h"
#include "Constsants.h"

smartMonster::smartMonster(sf::Vector2f direction, sf::Vector2f bounds, sf::Texture* texture, int row, int col, double ratio)
	: Monster(direction, bounds, texture, row, col, ratio)
{ }

void smartMonster::chase(sf::Time& deltaTime, Controller& controller, Board& board, int index)
{
								//if the monster is to the right of the digger
	if (controller.getDigger().getSprite().getPosition().x > (*this).getSprite().getPosition().x)
	{
		getSprite().setTexture(board.getBlueMonsterRTexture());
		
		//if the monster is lower than the digger on the board
		if (controller.getDigger().getSprite().getPosition().y > (*this).getSprite().getPosition().y)
			setDirection(sf::Vector2f(MONST_SPEED_IN_PXLS, MONST_SPEED_IN_PXLS));

		//if the monster is higher than the digger on the board
		else if(controller.getDigger().getSprite().getPosition().y < (*this).getSprite().getPosition().y)
			setDirection(sf::Vector2f(MONST_SPEED_IN_PXLS, -MONST_SPEED_IN_PXLS));
		
		else
			setDirection(sf::Vector2f(MONST_SPEED_IN_PXLS, 0));
	}
								//if the monster is to the left of the digger
	else if (controller.getDigger().getSprite().getPosition().x < (*this).getSprite().getPosition().x)
	{
		getSprite().setTexture(board.getBlueMonsterLTexture());

		if (controller.getDigger().getSprite().getPosition().y > (*this).getSprite().getPosition().y)
			setDirection(sf::Vector2f(-MONST_SPEED_IN_PXLS, MONST_SPEED_IN_PXLS));

		else if (controller.getDigger().getSprite().getPosition().y < (*this).getSprite().getPosition().y)
			setDirection(sf::Vector2f(-MONST_SPEED_IN_PXLS, -MONST_SPEED_IN_PXLS));

		else
			setDirection(sf::Vector2f(-MONST_SPEED_IN_PXLS, 0));
	}

	else
	{
		if (controller.getDigger().getSprite().getPosition().y > (*this).getSprite().getPosition().y)
			setDirection(sf::Vector2f(0, MONST_SPEED_IN_PXLS));
		else
			setDirection(sf::Vector2f(0, -MONST_SPEED_IN_PXLS));
	}

	setEaten(controller);						//checks if the monster succeeded in eating the digger

	move(deltaTime, controller, board);			//confirms if the monster got stuck on a wall or rock
}


