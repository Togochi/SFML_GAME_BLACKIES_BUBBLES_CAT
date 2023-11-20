#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()

{
	this->points = rand() % 3 + 1;
	this->type = rand() % 2 + 1;
	this->onGround = false;

	switch (type)
	{
	case 1:
		this->velocity = sf::Vector2f(static_cast<float>(rand() % 4) , static_cast<float>(this->points));
		break;
	case 2:
		this->velocity = sf::Vector2f( - static_cast<float>(this->points), - static_cast<float>(rand() % 4));
		break;
	}
	this->damage = this->points*5; 

	this->resetTimerMax = this->resetTimerMax = static_cast<float>(rand() % 60 + 10.f);
	this->resetTimer = 0.f;
}

void Enemy::initTexture()
{
	if (!this->texture.loadFromFile("Textures/chern.png"))
	{
		std::cerr << "ERROR::ENEMY::INITTEXTURE: error loading texture from file!" << '\n';
	}
	this->texture.setSmooth(true);
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(80, 227, 82, 83));
	this->sprite.setOrigin(this->getBounds().width / 2, this->getBounds().top);

	switch (type)
	{
	case 1:
		this->sprite.setScale(0.5f, 0.5f);
		break;
	case 2:
		this->sprite.setScale(-0.5f, 0.5f);
		break;

	}
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->sprite.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const float& Enemy::getDir() const
{
	return this->dir_x;
}

const int& Enemy::getType() const
{
	return this->type;
}

void Enemy::updateVelocity()
{
	this->resetTimer += 0.2f; 
	if (this->resetTimer >= this->resetTimerMax)
	{
		switch (this->type)
		{
		case 1:
			this->velocity = sf::Vector2f(- static_cast<float>(rand() % 4) + 0.1f, - static_cast<float>(rand() % 4) + 0.1f);
			break;
		case 2:
			this->velocity = sf::Vector2f(static_cast<float>(rand() % 4) + 0.1f, static_cast<float>(rand() % 4) + 0.1f);
			break;
		}
		this->resetTimer = 0;
		this->resetTimerMax = static_cast<float>(rand() % 60 + 10.f);
	}
}

void Enemy::setOnGround(const bool g)
{
	this->onGround = g;
}

void Enemy::setDir(float dir)
{
	this->velocity *= dir;
}

void Enemy::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}


void Enemy::update()
{
	this->updateVelocity();
	this->sprite.move(this->velocity);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
