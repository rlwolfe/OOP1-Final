#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Controller;
using std::vector;

class StatsDisplay {

public:
	StatsDisplay();
	void setStatsDisplay(Controller&);
	void draw(sf::RenderWindow&);
	void updateStatsData(Controller&);
	
	sf::Font* getFont() { return &m_font; }

private:
	vector <sf::Text> m_textsVector;
	vector <sf::Sprite> m_spritesVector;
	
	sf::Text m_levelID;
	sf::Texture m_livesTexture;
	sf::Font m_font;
};