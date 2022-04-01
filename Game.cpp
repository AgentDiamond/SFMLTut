#include "Game.h"

Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::update()
{
    this->pollEvents();
    this->updateMousePositions();
    this->updateEnemies();
}

/*
    -Clear old frame
    -Render objects
    -Display frame in window

    Renders the game objects.>>>>>>>>>>>>>
*/
void Game::render()
{
    this->window->clear();


    //Draw game objects
    this->renderEnemies();
    this->window->display();
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::initVariables()
{
	this->window = nullptr;

    //Game logic
    this->points = 0;
    this->enemySpawnTimerMax = 60.f;
    this->enemySpawnTimer = enemySpawnTimerMax;
    this->maxEnemies = 5;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "My First Game", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);

}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}

/// <summary>
/// Updates the mouse position relative to the window
/// </summary>
void Game::updateMousePositions()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}
/// <summary>
/// Updates the enemy spawn timer and spawns enemies
/// when the total amount of enemies is smaller than the maximum.
/// 
/// Moves the enemies downwards.
/// 
/// Removes the enemies at the edge of the screen.
/// </summary>
void Game::updateEnemies()
{
    //updating the timer for enemy spawning
    if (this->enemySpawnTimer < this->enemySpawnTimerMax)
    {

        this->enemySpawnTimer += 1.f;
        
    }
    else if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
    {
        //spawn the enemy and reset the timer
        this->spawnEnemy();
        this->enemySpawnTimer = 0.f;
    }

    //Move the enemies
    for (auto& e : this->enemies)
    {
        e.move(0.f, 5.f);
    }
}
void Game::renderEnemies()
{
    for (auto& e : this->enemies)
    {
        this->window->draw(e);
    }
}
/// <summary>
/// Spawns enemies and sets their colours and positions
/// -Sets a random position.
/// -Sets a random colour.
/// -Adds enemy to vector
/// </summary>
void Game::spawnEnemy()
{
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    this-> enemy.setFillColor(sf::Color::Green);

    this->enemies.push_back(this->enemy);


}
