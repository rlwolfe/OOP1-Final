#include "Controller.h"
#include "Constsants.h"
#include "Monster.h"
#include "SmartMonster.h"
#include "StupidMonster.h"

#include <sstream>

Controller::Controller() 
{
	m_level = FIRST_LEVEL;

	open_file_and_get_level_data();

	m_board.setBoard(*this);
	
	m_windowSize = sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT);

	m_statsDisplayer.setStatsDisplay(*this);

	if (!m_openingTexture.loadFromFile("opening.jpg"))
		exit(EXIT_FAILURE);

	if (!m_start.openFromFile("start.wav"))
		exit(EXIT_FAILURE);

	if (!m_wallpaperTexture.loadFromFile("wallpaper.jpg"))
		exit(EXIT_FAILURE);

	if (!m_music.openFromFile("audio.wav"))
		exit(EXIT_FAILURE);

	if (!m_winTexture.loadFromFile("youWin.jpg"))
		exit(EXIT_FAILURE);

	if (!m_winner.openFromFile("win.wav"))
		exit(EXIT_FAILURE);

	if (!m_loseTexture.loadFromFile("gameOver.jpg"))
		exit(EXIT_FAILURE);
	
	if (!m_loser.openFromFile("lose.wav"))
		exit(EXIT_FAILURE);

										//collects all background textures and sounds for use later
	
	m_wallpaperSprite = (sf::Sprite(m_wallpaperTexture));

	m_openingSprite = (sf::Sprite(m_openingTexture));

	m_winSprite = (sf::Sprite(m_winTexture));

	m_loseSprite = (sf::Sprite(m_loseTexture));

	m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y), "DIGGER 2020");
	
	m_clock.restart();				//sets clock to zero
}

void Controller::playGame()
{  
	open_menu(m_openingSprite);
	
	sf::Clock motionClock;
	
	m_music.play();							//starts playing music
	m_music.setLoop(true);
	
	while (m_window.isOpen())
	{
		m_window.clear();				//begins level

		auto deltaTime = motionClock.restart();

		m_digger.move(deltaTime, (*this), m_board);

		m_board.checkForCollisions(*this, 0);
		m_board.checkForCollisions(*this, 1);


		m_statsDisplayer.updateStatsData((*this));			//sets initial data for each level

		m_window.draw(m_wallpaperSprite);
		m_board.draw(m_window);					//draws game board

		for (int index = 0; index < getMonsters().size(); index++)
		{
///			m_monsters[index]->getSprite().setTextureRect(sf::IntRect(m_monsters[index]->getMover().x * CHARACTER_SIZE, m_monsters[index]->getMover().y * CHARACTER_SIZE, CHARACTER_SIZE, CHARACTER_SIZE));
			m_window.draw(m_monsters[index]->getSprite());			//places monsters on the board

			m_monsters[index]->chase(deltaTime, (*this), m_board, index);	//moves monsters
		}

///		m_digger.getSprite().setTextureRect(sf::IntRect(m_digger.getMover().x * CHARACTER_SIZE, m_digger.getMover().y * CHARACTER_SIZE, CHARACTER_SIZE, CHARACTER_SIZE));
		m_window.draw((m_digger).getSprite());
		
		m_statsDisplayer.draw(m_window);
		m_bonusInfoDisplayer.draw(m_window);			//adds on bonuses for game

		m_window.display();

		for (auto event = sf::Event{}; m_window.pollEvent(event); )
		{
			switch (event.type)
			{
			case sf::Event::Closed:					//if player closes the window
			{
				m_music.stop();
				m_window.close();
				break;
			}

			case sf::Event::KeyPressed:				//reacts when player moves the digger
				m_digger.changeDirection(event.key.code, (*this), m_board);
				break;
			}
		}

		if (lostRound())
		{
			if (m_digger.getLives() == NO_MORE_LIVES)
			{  
				m_loser.stop();
				m_loser.play();
			
				open_menu(m_loseSprite);

				m_file.close();
				m_file.clear();				//resets for continued playing (if desired)
				
				playAgain((*this));
			}

			else
				restartLevel();				//if there are more lives level restarts (not whole game)
		
		}

		if (wonRound())					//YAYYY!!! :)
		{
			if (!nextLevel())
			{
				m_winner.stop();
				m_winner.play();
				
				open_menu(m_winSprite);
			
				playAgain(*this);			//asks if player wants to start again
			}
		}
	}
}

void Controller::open_file_and_get_level_data()
{   
	string fileName = "BoardX.txt";
	fileName[5] = m_level + '0';

	m_file.open(fileName);				//loads game board from file in resources
	if (!m_file)
		return;

	string levelData;
	getline(m_file, levelData);

	std::stringstream ss;
	ss << levelData;

	string temp;
	
	ss >> temp;
	std::stringstream(temp) >> m_rows;
	temp = "";

	ss >> temp;

	std::stringstream(temp) >> m_cols;
	temp = "";

	ss >> temp;
	std::stringstream(temp) >> m_stonesAllowed;			//counts allowed stones to eat
	m_stonesLeft = m_stonesAllowed;
	temp = "";

	ss >> temp;

	std::stringstream(temp) >> m_startingTime;			//tracks time left
	m_timeLeft = m_startingTime;
}

bool Controller::lostRound()
{
	if (m_stonesLeft <= 0)			//if the digger ate too many rocks
	{   
		m_digger.decLives();
		return true;
	}
	
	if (m_moveTime && m_startingTime - (int)m_clock.getElapsedTime().asSeconds() <= 0)
	{
		m_timeLeft = m_startingTime;		//if the time ran out
		m_clock.restart();
		
		m_digger.decLives();
		return true;
	}

	if (m_wasEaten)				//if the monster ate the digger
	{
		m_wasEaten = false;
		m_digger.decLives();
			return true;
	}
	
	return false;				//if the games still being played
}

void Controller::restartLevel()		//resets stats and data for whole game when needed
{   
	if(m_stonesLeft <= 0 )
		m_stonesLeft = m_stonesAllowed;

	if(m_timeLeft <= 0)
		m_timeLeft -= m_clock.getElapsedTime().asSeconds();

	m_stonesLeft = m_stonesAllowed;

	m_moveTime = false;

	int currLives = m_digger.getLives();

	m_digger = Digger(sf::Vector2f(0, 0), sf::Vector2f(m_rows, m_cols), m_digger.getTexture(), m_digger.getCoordinance().y, m_digger.getCoordinance().x, 10.5);

	m_digger.setLives(currLives);


	for (int i = 0; i < m_monsters.size(); i++)
	{
		Monster temp;				//resets positions of monsters
		
		if (rand() % 2 == 0)
			temp = smartMonster(sf::Vector2f(0, 0), sf::Vector2f((float)m_rows, (float)m_cols), m_monsters[i]->getTexture(), m_monsters[i]->getOriginalPos().x, m_monsters[i]->getOriginalPos().y, 10.5);

		else
			temp = stupidMonster(sf::Vector2f(0, 0), sf::Vector2f((float)m_rows, (float)m_cols), m_monsters[i]->getTexture(), m_monsters[i]->getOriginalPos().x, m_monsters[i]->getOriginalPos().y, 10.5);
	
		(*m_monsters[i]) = temp;

		m_board.resetStones((*this));
	}
}

bool Controller::wonRound()
{
	if (m_diamondsNeeded == 0)
		return true;

	return false;
}

bool Controller::nextLevel()				//keeps score and moves onto  next level
{   
	m_level ++;
	m_gamePoints += 20;
	m_file.close();
	m_file.clear();
	
	int currLives = m_digger.getLives();

	m_moveTime = false;
	m_bonusInfoDisplayer.deleteBonusDisplayer();

	for (int i = 0; i < m_monsters.size(); i++)
	{
		delete m_monsters[i];
		m_monsters.clear();
	}

	open_file_and_get_level_data();
	
	if (!m_file)			//if the player just finished the last level and got to end of game and won
		return false;

	m_board.deleteBoard();
	m_board.setBoard(*this);
	
	m_digger.setLives(currLives);

	m_statsDisplayer = StatsDisplay();

	m_statsDisplayer.setStatsDisplay(*this);

	m_clock.restart();

	if (!m_file)
		return false;

	m_bonusInfoDisplayer = BonusInfoDisplayer();

	return true;
}

void Controller::open_menu(sf::Sprite sprite)			//menu for player select
{
	m_music.stop();

	while (m_window.isOpen())
	{
		m_window.draw(sprite);
		m_window.display();

		for (auto event = sf::Event{}; m_window.pollEvent(event); )
		{
			switch (event.type)			//finishes game and stops gameplay with all its features
			{
				case sf::Event::Closed:
					m_window.close();
					break;

				case sf::Event::KeyPressed:
				{
					if (event.key.code == sf::Keyboard::Key::N)			//to start a new game
					{
						m_start.stop();
						m_start.play();
						
						return;
					}

					if (event.key.code == sf::Keyboard::Key::E)			//to exit gameplay
					{
						m_window.close();

						exit(EXIT_SUCCESS);
					}
					break;
				}
			}
		}
	}
}

void Controller::playAgain(Controller& controller)
{   
 	m_digger.setLives(BEGIN_NUMBER_OF_LIVES + 1);
	m_gamePoints = 0;
	m_diamondsNeeded = 0;
	
	for (int i = 0; i < m_monsters.size(); i++)			//prepares game for repeat playing
	{
		delete m_monsters[i];
		m_monsters.clear();
	}
	int lostAtlevel = m_level;

	m_level = FIRST_LEVEL;
	open_file_and_get_level_data();

	m_board.setBoard(*this);

	m_statsDisplayer = StatsDisplay();	
	m_digger.setLives(BEGIN_NUMBER_OF_LIVES);

	if(lostAtlevel != FIRST_LEVEL)
		m_digger.setLives(BEGIN_NUMBER_OF_LIVES + 1);


	m_statsDisplayer.setStatsDisplay(*this);
	m_bonusInfoDisplayer.deleteBonusDisplayer();

	this->playGame();
}