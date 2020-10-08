#include "Board.h"
#include "Controller.h"
#include "Diamond.h"
#include "Stone.h"
#include "Bonus.h"
#include "Wall.h"
#include "Constsants.h"
#include "Monster.h"
#include "SmartMonster.h"
#include "StupidMonster.h"

Board::Board()
{   
	srand(time(NULL));

	if (!m_diggerLTexture.loadFromFile("diggerL.png") || !m_diggerRTexture.loadFromFile("diggerR.png")
		|| !m_diggerUTexture.loadFromFile("diggerU.png") || !m_diggerDTexture.loadFromFile("diggerD.png"))
		exit(EXIT_FAILURE);
	
	if (!m_backroundTexture.loadFromFile("backround.png"))
		exit(EXIT_FAILURE);

	if (!m_diamondTexture.loadFromFile("diamond.png"))
		exit(EXIT_FAILURE);

	if (!m_wallTexture.loadFromFile("wall.png"))
		exit(EXIT_FAILURE);

	if (!m_stoneTexture.loadFromFile("stone.png"))
		exit(EXIT_FAILURE);

	if (!m_pointsTexture.loadFromFile("points.png"))
		exit(EXIT_FAILURE);

	if (!m_clockTexture.loadFromFile("clock.png"))
		exit(EXIT_FAILURE);

	if (!m_stoneBonusTexture.loadFromFile("stoneBonus.png"))
		exit(EXIT_FAILURE);

	if (!m_monsterLTexture.loadFromFile("monsterL.png") || !m_monsterRTexture.loadFromFile("monsterR.png"))
		exit(EXIT_FAILURE);

	if (!m_blueMonsterLTexture.loadFromFile("blueMonsterL.png") || !m_blueMonsterRTexture.loadFromFile("blueMonsterR.png"))
		exit(EXIT_FAILURE);	
}

void Board::setBoard(Controller& controller)
{
	m_rows = controller.getRows();
	m_cols = controller.getCols();
	
	m_matrix.clear();					//clears board

	string line;

	for (int i = 0; i < m_rows; i++)
	{
		vector <ImmobileObject*> temp;
		getline(controller.getFileHandler(), line);

		for (int j = 0; j < m_cols; j++)
		{
			switch (line[j])		//checks what is in the given space in the board file and saves it to the game board
			{
				case DIGGER:		// ' / '
				{
					controller.getDigger() = Digger(sf::Vector2f(0, 0), sf::Vector2f(m_rows, m_cols), &m_diggerLTexture, i, j, 10.5);			    
					temp.push_back(new ImmobileObject(NULL, &m_backroundTexture, i, j, 0));
					break;
				}
				case MONSTER:		// ' ! '
				{
					controller.incMonsters();
					if ((controller.countMonsters()) % 2)			//every other monster is a smart monster
					{
						controller.getMonsters().push_back(new smartMonster(sf::Vector2f(0, 0), sf::Vector2f((float)m_rows, (float)m_cols), &m_blueMonsterLTexture, i, j, 10.5));
						temp.push_back(new ImmobileObject(NULL, &m_backroundTexture, i, j, 0));
					}

					else						//other monsters will be stupid monsters
					{
						controller.getMonsters().push_back(new stupidMonster(sf::Vector2f(0, 0), sf::Vector2f((float)m_rows, (float)m_cols), &m_monsterLTexture, i, j, 10.5));
						temp.push_back(new ImmobileObject(NULL, &m_backroundTexture, i, j, 0));
					}
					break;
				}
				case DIAMOND:		// ' D '
				{
					temp.push_back(new Diamond(&m_diamondTexture, &m_backroundTexture, i, j, 0));
					controller.incDiamonds();
					break;
				}

				case STONE:		// ' @ '
				{
					temp.push_back(new Stone(&m_stoneTexture, &m_backroundTexture, i, j, 0));
					break;
				}
				
				case WALL:		// ' # '
				{
					temp.push_back(new Wall(&m_wallTexture, &m_backroundTexture, i, j, 0));
					break;
				}

				case BONUS:		// ' + '
				{
					Bonus bonus(NULL, &m_backroundTexture, i, j, 0);
					temp.push_back(bonus.makeSpecificBonus(&m_clockTexture, &m_pointsTexture, &m_stoneBonusTexture, controller.getTime()));
					break;
				}

				default:		// '  '
					temp.push_back(new ImmobileObject(NULL, &m_backroundTexture, i, j, 0));
			}
		}
		m_matrix.push_back(temp);
	}
}


void Board::draw(sf::RenderWindow& window)			//draws gameboard with textures
{
	for (int i = 0; i < m_rows; i++)
		for (int j = 0; j < m_cols; j++)
			m_matrix[i][j]->draw(window);

}

bool Board::checkForCollisions(Controller& controller, int character)
{   
	if (character == 0)
	{
		bool result;
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_cols; j++)
			{
				result = (m_matrix[i][j]->didCollide(controller));
				if (result == 1)					//checks that the moving object didnt run into a immobile object
				{
					if (!(m_matrix[i][j]->collisionConsequence(controller)))
						return false;		//checks if the moving object is allowed to interact with the immobile object and then acts if necessary
				}

			}
	}

	else
	{
		bool result;
		for (int i = 0; i < m_rows; i++)
			for (int j = 0; j < m_cols; j++)
			{
				result = (m_matrix[i][j]->didCollide(controller));
				if (result == 2)
				{
					if (!(m_matrix[i][j]->collisionConsequence(controller)))
						return false;
				}

			}
	}

	return true;
}

void Board::clearObjectFromBoard(sf::Vector2f coordinance)
{   
	int col = coordinance.x;
	int row = coordinance.y;

	delete m_matrix[row][col];
	
	m_matrix[row][col] = new ImmobileObject(NULL, &m_backroundTexture, row, col, 0);
}

Board::~Board()
{
	for (int i = 0; i < m_matrix.size(); i++)
		for (int j = 0; j < m_matrix[i].size(); j++)
			delete m_matrix[i][j];
}

void Board::deleteBoard()
{
	for (int i = 0; i < m_matrix.size(); i++)
		for (int j = 0; j < m_matrix[i].size(); j++)
			delete m_matrix[i][j];
}

void Board::resetStones(Controller& controller)
{   
	controller.getFileHandler().seekg(0, std::ios::beg);
	
	string line;
	getline(controller.getFileHandler(), line);

	for (int i = 0; i < m_rows; i++)				//puts stone back in original places from start of level
	{
		getline(controller.getFileHandler(), line);

		for (int j = 0; j < m_cols; j++)
		{
			if (line[j] == STONE)
			{
				delete m_matrix[i][j];
				m_matrix[i][j] = new Stone(&m_stoneTexture, &m_backroundTexture, i, j, 0);
			}
		}
	}
}
