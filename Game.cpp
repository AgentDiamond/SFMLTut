#include "Game.h"

Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initFonts();
    this->initText();
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
    if (gameEnded == false)
    {
        this->updateMousePositions();
        this->updateText();
        this->updateEnemies();


    }
    else if (this->gameEnded == true)
    {
        std::cout << "You died! Game over..." << std::endl;
    }

    //endgame condition
    if (this->health <= 0)
    {
        this->endGame();
    }
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
    this->renderEnemies(*this->window);
    this->renderText(*this->window);
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
    this->health = 100;
    this->enemySpawnTimerMax = 60.f;
    this->enemySpawnTimer = enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
    this->gameEnded = false;
    this->gamePaused = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "My First Game", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);

}

void Game::initFonts()
{
    this->font.loadFromFile("Fonts/ARCADE.ttf");
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(50);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("DEFAULT");
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

void Game::updateText()
{
    std::stringstream ss;
    ss << "Points: " << this->points << std::endl
        << "Health: " << this->health << std::endl;
    this->uiText.setString(ss.str());


}

/// <summary>
/// Updates the mouse position relative to the window
/// </summary>
void Game::updateMousePositions()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
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

    //Move and update enemies
    for (int i = 0; i < enemies.size(); i++)
    {
        
        bool deleted = false;
        
        this->enemies[i].move(0.f, 5.f);

        //if the enemy is past the bottom of the screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 5;
            std::cout << "Health " << this->health << std::endl;

        }

    }

        //check if clicked upon
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this->mouseHeld == false)
            {
                this->mouseHeld = true;
                bool deleted = false;
                for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
                {
                    if (enemies[i].getGlobalBounds().contains(this->mousePosView))
                    {
                        //Delete the enemy
                        deleted = true;
                        this->enemies.erase(this->enemies.begin() + i);

                        //Gain points
                        this->points += 10;
                        std::cout << "Points " << this->points << std::endl;
                    }
                }
            }
        }
        //inorder to reset mouseHeld to false so we can delete
        //enemies again,the mouse has to be released
        else
        {
            this->mouseHeld = false;
        }
  
}
void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}
void Game::renderEnemies(sf::RenderTarget& target)
{
    for (auto& e : this->enemies)
    {
        target.draw(e);
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

void Game::pauseGame()
{
    this->gamePaused = true;
}

void Game::endGame()
{
    this->gameEnded = true;
}
