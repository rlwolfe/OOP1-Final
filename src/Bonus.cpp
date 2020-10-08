#include "Bonus.h"
#include "Controller.h"
#include "BonusPoints.h"
#include "BonusStones.h"
#include "BonusTime.h"
#include "Constsants.h"

Bonus* Bonus::makeSpecificBonus(sf::Texture* clock, sf::Texture* points, sf::Texture* stones, int time)
{  
	(*this).getObjectSprite().setPosition(getLocation() + sf::Vector2f(MOV_CNTR_SQ_DIST, MOV_CNTR_SQ_DIST)); 

	int type;
	
	if (time != UNLIMTED)
		type = rand() % NUM_DIFF_BONUSES;
												//randomly generates which bonus is displayed
	else
		type = rand() % (NUM_DIFF_BONUSES - 1);

	switch (type)
	{
		case 0:				//extra points
		{
			(*this).getObjectSprite().setTexture(*points);

			BonusPoints* temp = (static_cast<BonusPoints*>(this));
			BonusPoints* bonus = new BonusPoints(*temp);
			return bonus;
			break;
		}
		case 1:				//extra stones
		{
			(*this).getObjectSprite().setTexture(*stones);

			BonusStones* temp = (static_cast<BonusStones*>(this));
			BonusStones* bonus = new BonusStones(*temp);
			return bonus;
			break;
		}
		default:		//extra time
		{
			(*this).getObjectSprite().setTexture(*clock);

			BonusTime* temp = (static_cast<BonusTime*>(this));
			BonusTime* bonus = new BonusTime(*temp);
			return bonus;
			break;
		}
	}
}

void Bonus::displayBonusAmount(string msg, Controller& controller)
{
	sf::Text* bonusMsg = new sf::Text(msg, *(controller.getFont()));
	
	bonusMsg->setColor(sf::Color::Red);
	bonusMsg->setCharacterSize(BONUS_MSG_CHAR_SIZE);
	(*bonusMsg).setPosition(controller.getDigger().getSprite().getPosition().x + controller.getDigger().getSprite().getGlobalBounds().width / 4, controller.getDigger().getSprite().getPosition().y - controller.getDigger().getSprite().getGlobalBounds().height /2);
	
	controller.getBonusDisplayer().getTexts().push_back(bonusMsg);
	
	sf::Clock* clock = new sf::Clock;
	(*clock).restart();
	
	controller.getBonusDisplayer().getClocks().push_back(clock);
}