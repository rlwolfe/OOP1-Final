#include "StatsDisplay.h"
#include "Controller.h"
#include "Constsants.h"

StatsDisplay::StatsDisplay()			//loads fonts in use
{
	if (!m_livesTexture.loadFromFile("lives.png"))
		exit(EXIT_FAILURE);

	m_font.loadFromFile("C:/Windows/Fonts/Impact.ttf");
}

void StatsDisplay::setStatsDisplay(Controller& controller)				//collects information for the stats list
{
	m_spritesVector.push_back(sf::Sprite(controller.getBoard().getPointsTexture()));
	
	int sideLength = m_spritesVector[0].getGlobalBounds().height;

	m_spritesVector[0].setPosition(controller.getWindowSize().x - 150, 0);

	m_spritesVector.push_back(sf::Sprite(m_livesTexture));
	m_spritesVector[1].setPosition(controller.getWindowSize().x - 150, sideLength * 1.5);

	m_spritesVector.push_back(sf::Sprite(controller.getBoard().getClockTexture()));
	m_spritesVector[2].setPosition(controller.getWindowSize().x - 150, sideLength * 2.5 + sideLength /2);

	m_spritesVector.push_back(sf::Sprite(controller.getBoard().getDiamondTexture()));	
	m_spritesVector[3].setPosition(controller.getWindowSize().x - 150, sideLength * 3.5 + sideLength);

	m_spritesVector.push_back(sf::Sprite(controller.getBoard().getStonesTexture()));
	m_spritesVector[4].setPosition(controller.getWindowSize().x - 150, sideLength * 4.5 + sideLength * 1.5);

	for (int i = 0; i < m_spritesVector.size(); i++)					//holds pictures then numbers of the stats list
	{
		m_textsVector.push_back(sf::Text("", m_font));
		m_textsVector[i].setColor(sf::Color::Magenta);
		m_textsVector[i].setPosition(m_spritesVector[i].getPosition() + sf::Vector2f(sideLength + 10, 10));

	}														//sets amount of what to display next to each picture

	m_levelID = sf::Text("LEVEL " + std::to_string(controller.getLevel()), m_font);

	m_levelID.setCharacterSize(50);
	m_levelID.setLetterSpacing(2);
	m_levelID.setPosition(sf::Vector2f(0, controller.getWindowSize().y - m_levelID.getGlobalBounds().height * 1.5));
	m_levelID.setColor(sf::Color::Magenta);
	
	updateStatsData(controller);
}

void StatsDisplay::draw(sf::RenderWindow& window)		//draws to the side of the board th pictures and amounts
{   
	for(int i = 0; i < m_spritesVector.size(); i++)
	    window.draw(m_spritesVector[i]);

	for (int i = 0; i < m_textsVector.size(); i++)
		window.draw(m_textsVector[i]);

	window.draw(m_levelID);
}

void StatsDisplay::updateStatsData(Controller& controller)						//updates numbers accordingly when needed to in game
{
	m_textsVector[0].setString(std::to_string(controller.getPoints()));
	int lives = controller.getDigger().getLives();
	if (lives > BEGIN_NUMBER_OF_LIVES)
	{
		lives--;
		//controller.getDigger().decLives();
	}

	m_textsVector[1].setString(std::to_string(lives));

	if (controller.getTime() == -1)
		m_textsVector[2].setString("----- ");								//what is printed when a level isn't timed
	
	else														//when a level is timed
	{
		if (controller.isTimeMoving())
			m_textsVector[2].setString(std::to_string(controller.getTime() - (int)controller.getClock().getElapsedTime().asSeconds()));

		else
			m_textsVector[2].setString(std::to_string(controller.getTime()));
	}

	m_textsVector[3].setString(std::to_string(controller.getDiamondsNeeded()));				//retreives needed information
	m_textsVector[4].setString(std::to_string(controller.getStonesLeft()));
}