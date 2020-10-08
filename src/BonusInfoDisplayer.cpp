#include "BonusInfoDisplayer.h"
#include "Controller.h"
#include "Constsants.h"

void BonusInfoDisplayer::draw(sf::RenderWindow& window)
{   
	for (int i = 0; i < m_texts.size() - 1 && m_texts.size() != 0; i++)
		if (m_texts[i]->getGlobalBounds().intersects(m_texts[i + 1]->getGlobalBounds()))
			m_texts[i + 1]->setPosition(m_texts[i + 1]->getPosition() + sf::Vector2f((m_texts[i + 1]->getGlobalBounds().width * SPACE_BW_MSG), 0));

	for (int i = 0; i < m_texts.size(); i++)					//draws bonus prize won on screen for player to view
		window.draw(*m_texts[i]);

	for (int i = 0; i < m_timeToShow.size(); i++)
	{
		if ((*m_timeToShow[i]).getElapsedTime().asSeconds() >= SECONDS_FOR_MSG)
			    (*m_texts[i]).setString("");
	}
}

BonusInfoDisplayer::~BonusInfoDisplayer()				// bonus destructor
{
	for (int i = 0; i < m_texts.size(); i++)
		    delete m_texts[i];

	for (int i = 0; i < m_timeToShow.size(); i++)
		    delete m_timeToShow[i];
}


void BonusInfoDisplayer::deleteBonusDisplayer()				//deletes for not memory overflow
{
	for (int i = 0; i < m_texts.size(); i++)
		delete m_texts[i];

	for (int i = 0; i < m_timeToShow.size(); i++)
		delete m_timeToShow[i];

	m_texts.clear();
	m_timeToShow.clear();
}