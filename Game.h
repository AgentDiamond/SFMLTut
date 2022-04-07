#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <ctime>
#include <iostream>
#include <sstream>

//Class that acts as the game engine. Wrapper class
class Game
{
public:
	//Constructor /Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void update();
	void render();
	void pollEvents();

private:

	//Functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();

	void updateText();
	void updateEndGameText();
	void updateMousePositions();
	void updateEnemies();

	void renderText(sf::RenderTarget& target);
	void renderEndGameText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);

	void spawnEnemy();

	//State Functions

	void pauseGame();
	void endGame();

	//Game State
	bool gamePaused;
	bool gameEnded;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;
	sf::Text endGameText;

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

