#pragma once

#include "ImmobileObject.h"
#include "MovableCharacter.h"
#include "Constsants.h"

#pragma once

#include <vector>
class Controller;
using std::vector;

class Board
{
public:
	Board();
	~Board();
	
	ImmobileObject* getObject(int i, int j) const { return m_matrix[i][j]; }

	void draw(sf::RenderWindow&);
	void clearObjectFromBoard(sf::Vector2f);
	void resetStones(Controller&); 
	void setBoard(Controller&);
	void deleteBoard();
	
	bool checkForCollisions(Controller&, int);

	sf::Texture& getDiamondTexture() { return m_diamondTexture; }
	sf::Texture& getPointsTexture() { return m_pointsTexture; }
	sf::Texture& getClockTexture() { return m_clockTexture; }
	sf::Texture& getStonesTexture() { return m_stoneTexture; }
	
	sf::Texture& getDiggerLTexture() { return m_diggerLTexture; }
	sf::Texture& getDiggerRTexture() { return m_diggerRTexture; }
	sf::Texture& getDiggerUTexture() { return m_diggerUTexture; }
	sf::Texture& getDiggerDTexture() { return m_diggerDTexture; }
	
	sf::Texture& getMonsterLTexture() { return m_monsterLTexture; }
	sf::Texture& getMonsterRTexture() { return m_monsterRTexture; }

	sf::Texture& getBlueMonsterLTexture() { return m_blueMonsterLTexture; }
	sf::Texture& getBlueMonsterRTexture() { return m_blueMonsterRTexture; }

	sf::Vector2f getObjectPos(int i, int j) { return m_matrix[i][j]->getLocation(); }

private:
	vector <vector <ImmobileObject*> > m_matrix;
	
	int m_rows = 0;
	int m_cols = 0;

	sf::Texture m_wallTexture;
	sf::Texture m_clockTexture;
	sf::Texture m_stoneTexture;
	sf::Texture m_pointsTexture;
	sf::Texture m_diamondTexture;
	sf::Texture m_backroundTexture;
	sf::Texture m_stoneBonusTexture;

	sf::Texture m_diggerLTexture;
	sf::Texture m_diggerRTexture;
	sf::Texture m_diggerUTexture;
	sf::Texture m_diggerDTexture;

	sf::Texture m_monsterLTexture;
	sf::Texture m_monsterRTexture;

	sf::Texture m_blueMonsterLTexture;
	sf::Texture m_blueMonsterRTexture;
};
