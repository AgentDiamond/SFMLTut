#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <ctime>
#include <iostream>

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
	void updateMousePositions();
	void updateEnemies();
	void renderEnemies();
	void spawnEnemy();

	//State Functions

	void pauseGame();
	void endGame();

	//Game State
	bool gamePaused;
	bool gameEnded;

	//Window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	//Game logic
	unsigned int points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;



	//Game objects
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

	//Mouse Positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
};

