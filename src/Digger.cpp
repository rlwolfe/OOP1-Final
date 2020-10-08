#include "Digger.h"
#include "Controller.h"
#include "Constsants.h"

Digger::Digger(sf::Vector2f direction, sf::Vector2f bounds, sf::Texture* texture, int row, int col, double ratio) 
: MovableCharacter(direction, bounds, texture, row, col, ratio)
{
	m_lives = BEGIN_NUMBER_OF_LIVES;
	
	m_firstMove = true;				//initiates start of movement from the player
}

void Digger::changeDirection(sf::Keyboard::Key key, Controller& controller, Board &board)
{
	if (controller.getTime() == UNLIMTED)
		m_firstMove = false;

	if (m_firstMove)
	{
		controller.moveTime();
		controller.getClock().restart();
		m_firstMove = false;
	}
	
	switch (key)			//starts movement in given direction according to what the player clicked
	{
		case sf::Keyboard::Key::Space:				//stops movement in any direction
			setDirection(sf::Vector2f(0, 0));
			break;

		case sf::Keyboard::Key::Left:
			getSprite().setTexture(board.getDiggerLTexture());
			setDirection(sf::Vector2f(-DIGR_SPEED_IN_PXLS, 0));
			break;

		case sf::Keyboard::Key::Right:
			getSprite().setTexture(board.getDiggerRTexture());
			setDirection(sf::Vector2f(DIGR_SPEED_IN_PXLS, 0));
			break;

		case sf::Keyboard::Key::Down:
			getSprite().setTexture(board.getDiggerDTexture());
			setDirection(sf::Vector2f(0, DIGR_SPEED_IN_PXLS));
			break;

		case sf::Keyboard::Key::Up:
			getSprite().setTexture(board.getDiggerUTexture());
			setDirection(sf::Vector2f(0, -DIGR_SPEED_IN_PXLS));
			break;
	}
}

void Digger::move(sf::Time& deltaTime, Controller& controller, Board& board)
{   
	if(!(*this).isOutOfBounds())						//checks that the digger hasn't run into anything or off the board
	   getSprite().move(getDirection() * deltaTime.asSeconds());

	if(!(controller.getBoard().checkForCollisions(controller, 0)))
		getSprite().move(-getDirection() * deltaTime.asSeconds());
}
