#include "StupidMonster.h"
#include "Controller.h"
#include "Constsants.h"

stupidMonster::stupidMonster(sf::Vector2f direction, sf::Vector2f bounds, sf::Texture* texture, int row, int col, double ratio)
	: Monster(direction, bounds, texture, row, col, ratio)
{ }

void stupidMonster::chase(sf::Time& deltaTime, Controller& controller, Board& board, int index)
{
	srand(time(NULL) + index);

	switch (rand() % 4)								//randomly selects a direction for the stupid monster to move in
	{
	case right:
		getSprite().setTexture(board.getMonsterRTexture());
		setDirection(sf::Vector2f(MONST_SPEED_IN_PXLS, 0));
		break;

	case left:
		getSprite().setTexture(board.getMonsterLTexture());
		setDirection(sf::Vector2f(-MONST_SPEED_IN_PXLS, 0));
		break;

	case up:
		setDirection(sf::Vector2f(0, -MONST_SPEED_IN_PXLS));
		break;

	case down:
		setDirection(sf::Vector2f(0, MONST_SPEED_IN_PXLS));
		break;
	}

	setEaten(controller);				//checks if the monster succeeded in eating the digger

	move(deltaTime, controller, board);			//confirms if the monster got stuck on a wall or rock
}