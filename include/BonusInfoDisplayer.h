#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Controller;
using std::vector;

class BonusInfoDisplayer
{
public:
	vector <sf::Text*>& getTexts() { return m_texts; }
	vector <sf::Clock*>& getClocks() { return m_timeToShow; }

	void draw(sf::RenderWindow& window);
	void deleteBonusDisplayer();

	~BonusInfoDisplayer();

private:
	vector <sf::Text*> m_texts;
	vector <sf::Clock*> m_timeToShow;
};