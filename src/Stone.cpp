#include "Stone.h"
#include "Controller.h"

bool Stone::collisionConsequence(Controller& controller)
{
	controller.getBoard().clearObjectFromBoard(this->getCoordinance());
	controller.decStones();								//interacts with digger and disappears when eaten by the player

	return true;
}