#include "stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Game 4 Platform", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}



void Game::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(this->window->getSize().x / 2, this->window->getSize().y - this->player->getPlayerBounds().height);
}


void Game::initGUI()
{
	//load fonts
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cerr << "ERROR::GAME::INITGUI:: Failed to load font" << '\n';
	}
	//init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::Black);
	this->pointText.setString("test");
	this->pointText.setPosition(900.f, 10.f);

	//Init game over text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Black);
	this->gameOverText.setString("GAME OVER");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	//Init pause  text
	this->pauseText.setFont(this->font);
	this->pauseText.setCharacterSize(24);
	this->pauseText.setFillColor(sf::Color::Black);
	this->pauseText.setString("PAUSE");
	this->pauseText.setPosition(
		this->window->getSize().x / 2.f - this->pauseText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->pauseText.getGlobalBounds().height / 2.f);


	//Init PlayerGUI
	this->playerHpBar.setSize(sf::Vector2f(10.f, 200.f));
	this->playerHpBar.setFillColor(sf::Color::Black);
	this->playerHpBar.setPosition(20.f, 20.f);

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(128, 128, 128, 200));
}

void Game::initSystems()
{
	this->points = 0;

	if (!this->meowBuffer.loadFromFile("Audio/meow.ogg"))
	{
		std::cerr << "ERROR::GAME::INITSYSTEMS:: Failed to load sound" << '\n';
	}
	if (!this->eatBuffer.loadFromFile("Audio/hrust_chipsov.ogg"))
	{
		std::cerr << "ERROR::GAME::INITSYSTEMS:: Failed to load sound" << '\n';
	}

	this->meowSound.setBuffer(meowBuffer);
	this->eatSound.setBuffer(eatBuffer);

	this->meowSound.setVolume(15);
	this->eatSound.setVolume(30);
}

void Game::initBubbles()
{
	this->spawnTimerMax = 30.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initEnemies()
{
	this->spawnTimerMaxEnem = static_cast<float>(rand() % 60 + 20.f);
	this->spawnTimerEnem = this->spawnTimerMaxEnem;
}

Game::Game()
{
	this->initWindow();

	this->initPlayer();
	this->initBubbles();
	this->initEnemies();

	this->initGUI();
	this->initSystems();
}

Game::~Game()
{
	delete this->player;
	delete this->window;

	//Delete bubbles
	for (auto* b : this->bubbles)
	{
		delete b;
	}
	//Delete Enemies
	for (auto* e : this->enemies)
	{
		delete e;
	}
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		if (this->player->getHp() > 0)
		{
			this->update();
			this->render();
		}

	}
}

void Game::togglePause()
{
	this->paused = !paused;
}

void Game::updatePollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window->close();
		else if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
			this->window->close();
		if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::P)
			this->togglePause();

		if (this->event.type == sf::Event::KeyReleased &&
			(this->event.key.code == sf::Keyboard::A ||
				this->event.key.code == sf::Keyboard::D ||
				this->event.key.code == sf::Keyboard::Space ||
				this->event.key.code == sf::Keyboard::S))
		{
			this->player->resetAnimationTimer();
		}
	}
}

void Game::updateCollision()
{
	//Collision of screen
	if (this->player->getPosition().y + this->player->getPlayerBounds().height >= window->getSize().y)
	{
		this->player->setOnGround(true);
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, this->window->getSize().y - this->player->getPlayerBounds().height);
	}
	if (this->player->getPosition().y <= 0)
	{
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, 0);
	}

	if (this->player->getPlayerBounds().left < 0)
	{
		this->player->setPosition(0 + this->player->getPlayerBounds().width / 2, this->player->getPosition().y);
	}

	if (this->player->getPosition().x + this->player->getPlayerBounds().width / 2 > window->getSize().x)
	{
		this->player->setPosition(window->getSize().x - this->player->getPlayerBounds().width / 2, this->player->getPosition().y);
	}

	//Collision with Bubbles
	for (int i = 0; i < this->bubbles.size(); ++i)
	{
		if (this->bubbles[i]->getBounds().intersects(this->player->getPlayerBounds()))
		{
			float distanceY = this->bubbles[i]->getBounds().top - (this->player->getPosition().y + this->player->getPlayerBounds().height);

			if (distanceY <= 0.f && distanceY >= -5 && this->player->getOnGround() == false
				&& this->player->getPosition().x > this->bubbles[i]->getBounds().left
				&& this->player->getPosition().x < this->bubbles[i]->getBounds().left + this->bubbles[i]->getBounds().width)
			{
				this->player->resetVelocityY();
				this->player->setPosition(this->player->getPosition().x, this->bubbles[i]->getBounds().top - this->player->getPlayerBounds().height + 3);
				this->player->setOnBubble(true);
			}
			else this->player->setOnBubble(false);
		}
	}
}

void Game::updateEnemyCollision()
{
	//Update enemy collision
	unsigned counter = 0;

	for (auto* e : this->enemies)
	{

		//Player collision
		bool isDeleted = false;

		if (e->getBounds().intersects(this->player->getPlayerBounds()))
		{
			if (this->player->getPlayerBounds().top + this->player->getPlayerBounds().height < e->getBounds().top + 6)
			{
				this->eatSound.play();
				this->player->gainHp(e->getPoints() * 2);
				this->points += e->getPoints();

			}
			else
			{
				this->meowSound.play();
				this->player->loseHp(e->getDamage());
			}

			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			isDeleted = true;
		}

		if (!isDeleted) {
			//Left collision

			if (e->getBounds().left < 0)
			{
				e->setDir(-1.f);
			}

			if (e->getBounds().left + e->getBounds().width > window->getSize().x)
			{
				e->setDir(-1.f);
			}

			if (e->getBounds().top < 0)
			{
				e->setDir(-1.f);
			}

			if (e->getBounds().top + e->getBounds().height > window->getSize().y)
			{
				e->setDir(-1.f);
			}
		}
		++counter;
	}

}



void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateBubbles()
{
	//Spawning
	this->spawnTimer += 0.5f;

	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->bubbles.emplace_back(new Bubble(rand() % this->window->getSize().x, this->window->getSize().y));
		this->spawnTimer = 0.f;
		this->spawnTimerMax = static_cast<float>(rand() % 31 + 10.f);
	}


	//Update
	unsigned counter = 0;

	for (auto* b : this->bubbles)
	{
		b->update();

		if (b->getBounds().top + b->getBounds().height < 0.f)
		{
			//Delete bubble
			delete this->bubbles.at(counter);
			this->bubbles.erase(this->bubbles.begin() + counter);
		}
		++counter;
	}

}



void Game::updateEnemies()
{
	//Spawning
	this->spawnTimerEnem += 0.2f;

	if (this->spawnTimerEnem >= this->spawnTimerMaxEnem)
	{
		int r = rand() % 4 + 1;
		switch (r)
		{
		case 1:
			this->enemies.emplace_back(new Enemy(60.f, rand() % 500 + 60.f));
			break;
		case 2:
			this->enemies.emplace_back(new Enemy(rand() % 900 + 50.f, this->window->getSize().y - 50.f));
			break;
		case 3:
			this->enemies.emplace_back(new Enemy(this->window->getSize().x - 60.f, rand() % 500 + 60.f));
			break;
		case 4:
			this->enemies.emplace_back(new Enemy(rand() % 900 + 50.f, 60.f));
			break;
		}
		this->spawnTimerEnem = 0.f;
		this->spawnTimerMaxEnem = static_cast<float>(rand() % 40 + 20.f);
	}

	for (auto* e : this->enemies) e->update();

}


void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points << '\n';

	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float> (this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(this->playerHpBar.getSize().x, 200.f * hpPercent));
}

void Game::update()
{
	this->updatePollEvents();

	if (!this->paused) {
		this->updateGUI();
		this->updatePlayer();
		this->updateBubbles();
		this->updateCollision();
		this->updateEnemyCollision();
		this->updateEnemies();
	}
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}


void Game::renderPlayer()
{
	this->player->render(*this->window);
}


void Game::render()
{
	this->window->clear(sf::Color(245, 245, 245));

	//Render game


	//Render bubbles
	for (auto* b : this->bubbles)
	{
		b->render(*this->window);
	}

	this->renderPlayer();

	this->renderGUI();


	//Render enemies
	for (auto* e : this->enemies)
	{
		e->render(*this->window);
	}


	if (this->paused) this->window->draw(this->pauseText);
	if (this->player->getHp() <= 0) this->window->draw(this->gameOverText);

	this->window->display();
}

const sf::RenderWindow* Game::getWindow() const
{
	return this->window;
}
