#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//Class that acts as the game engine. Wrapper class
class Game
{
public:
	//Constructor /Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void update();
	void render();
	void pollEvents();

private:

	//Functions
	void initVariables();
	void initWindow();
	void initEnemies();

	//Window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	//Game objects
	sf::RectangleShape enemy;
};

