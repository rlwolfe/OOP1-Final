#include "Diamond.h"
#include "Controller.h"
#include "Constsants.h"

bool Diamond::collisionConsequence(Controller& controller) 
{
	controller.getBoard().clearObjectFromBoard(this->getCoordinance());
	controller.decDiamonds();						//creates and controls actions with diamonds on the board
	controller.addPoints(DIAMOND_PTS);

	return true;
}