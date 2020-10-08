#pragma once
#include "Board.h"
#include "Digger.h"
#include "StatsDisplay.h"
#include "BonusInfoDisplayer.h"
class Monster;

#include <SFML/Audio.hpp>
#include <fstream>

class Controller
{
public:

	Controller();
	
	Board& getBoard() { return m_board; }
	Digger& getDigger() { return m_digger; }
	Monster* getMonster(int i) { return m_monsters[i]; }
	vector <Monster*>& getMonsters() { return m_monsters; }
	BonusInfoDisplayer& getBonusDisplayer() { return m_bonusInfoDisplayer; }

	void playGame();
	void restartLevel();
	void open_menu(sf::Sprite);
	void playAgain(Controller&);

	void incMonsters() { m_monsterTeam++; }
	void incDiamonds() { m_diamondsNeeded++; }
	void decDiamonds() { m_diamondsNeeded--;  }
	void decStones() { m_stonesLeft--; }
	void addPoints(int points) { m_gamePoints += points; }
	void addTime(int seconds) { m_startingTime += seconds; }
	void addStonesAllowed(int stones) { m_stonesLeft += stones; }
	void setEaten() { m_wasEaten = true; }
	void moveTime() { m_moveTime = true; }

	int getRows() { return m_rows; }
	int getCols() { return m_cols; }
	int getDiamondsNeeded() { return m_diamondsNeeded; }
	int getTime() { return m_startingTime; }
	int getStonesLeft() { return m_stonesLeft; }
	int getPoints() { return m_gamePoints; }
	int getLevel() { return m_level; }
	int countMonsters() { return m_monsterTeam; }

	bool isTimeMoving() { return m_moveTime; }
	bool lostRound();
	bool wonRound();
	bool nextLevel();
	
	std::ifstream& getFileHandler() { return m_file; }

	sf::Vector2f& getWindowSize() { return m_windowSize; }
	sf::Font* getFont() { return m_statsDisplayer.getFont(); }
	sf::RenderWindow& getWindow() { return m_window; }
	sf::Clock& getClock() { return m_clock; }

private:

	void open_file_and_get_level_data();
	
	Board m_board;
	Digger m_digger;
	vector <Monster*> m_monsters;
	StatsDisplay m_statsDisplayer;
	BonusInfoDisplayer m_bonusInfoDisplayer;

	int m_rows;
	int m_cols;
	int m_level;
	int m_timeLeft;
	int m_stonesLeft;
	int m_monsterTeam;
	int m_startingTime;
	int m_stonesAllowed;
	int m_gamePoints = 0;
	int m_diamondsNeeded = 0;
	
	bool m_moveTime = false;
	bool m_wasEaten = false;

	std::ifstream m_file;

	sf::Music m_music;
	sf::Music m_start;
	sf::Music m_winner;
	sf::Music m_loser;

	sf::Texture m_wallpaperTexture;
	sf::Texture m_openingTexture;
	sf::Texture m_winTexture;
	sf::Texture m_loseTexture;
	
	sf::Sprite m_openingSprite;
	sf::Sprite m_winSprite;
	sf::Sprite m_loseSprite;
	sf::Sprite m_wallpaperSprite;
	
	sf::Clock m_clock;
	
	sf::Vector2f m_windowSize;
	
	sf::RenderWindow m_window;
};


