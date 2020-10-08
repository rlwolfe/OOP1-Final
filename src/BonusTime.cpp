#include "BonusTime.h"
#include "Bonus.h"
#include "Controller.h"
#include "Constsants.h"

bool BonusTime::collisionConsequence(Controller& controller)
{
	controller.getBoard().clearObjectFromBoard(this->getCoordinance());
	
	int bonus = (rand() % TIME_UPPER_BOUND) + TIME_LOWER_BOUND;
	
	controller.addTime(bonus);			//adds time to the running clock for the game
	
	string msg = "+";
	
	msg += std::to_string(bonus);
	msg += "!";
	
	(*this).displayBonusAmount(msg, controller);
	
	return true;
}