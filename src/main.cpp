
#include <stdlib.h>
#include <crtdbg.h>
#include <SFML/Graphics.hpp>
#include "Controller.h"

int main()
{   
	Controller game;			//creates main game controller

	game.playGame();			//initiates gameplay, good luck!
	
	return EXIT_SUCCESS;		//game over, bye bye
}
//#include <iostream>
//int main()
//{
//	sf::RenderWindow window;
//	window.create(sf::VideoMode(500, 500), "tester");
//
//	sf::Texture texture;
//	sf::Sprite picture;
//
//	if (!texture.loadFromFile("digger.png"))
//		std::cout << "didn't work!" << std::endl;
//
//	picture.setTexture(texture);
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while(window.pollEvent(event))
//		{
//			switch (event.type)
//			{
//			case sf::Event::Closed:
//				window.close();
//				break;
//			}
//		}
//		//window.draw()
//		window.draw(picture);
//		window.display();
//	}
//}