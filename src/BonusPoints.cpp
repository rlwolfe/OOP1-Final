#include "BonusPoints.h"
#include "Bonus.h"
#include "Controller.h"
#include "Constsants.h"

bool BonusPoints::collisionConsequence(Controller& controller)
{ 
	controller.getBoard().clearObjectFromBoard(this->getCoordinance());
	
	int bonus = (rand() % PTS_UPPER_BOUND) + PTS_LOWER_BOUND;
	
	controller.addPoints(bonus);				//player gets extra points!
	
	string msg = "+";
	
	msg += std::to_string(bonus);
	msg += "!";
	
	(*this).displayBonusAmount(msg, controller);
    
	return true;
}