#include "BonusStones.h"
#include "Bonus.h"
#include "Controller.h"
#include "Constsants.h"

bool BonusStones::collisionConsequence(Controller& controller)
{
	controller.getBoard().clearObjectFromBoard(this->getCoordinance());
	
	int bonus = (rand() % STNS_UPPER_BOUND) + STNS_LOWER_BOUND;
	
	controller.addStonesAllowed(bonus);			//allowed number of stones increases

	string msg = "+";
	
	msg += std::to_string(bonus);
	msg += "!";

	(*this).displayBonusAmount(msg, controller);
	
	return true;
}