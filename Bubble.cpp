#include "stdafx.h"
#include "Bubble.h"

void Bubble::initVariables()
{
	this->points = rand() % 31 + 20;
	this->speed = -0.6f;//static_cast<float>(this->points / -4); 
}

void Bubble::initShape()
{
	this->shape.setRadius(this->points);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));

}

Bubble::Bubble(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
	
}

Bubble::~Bubble()
{
}

const sf::FloatRect Bubble::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int Bubble::getPoints() const
{
	return this->points;
}

const sf::Vector2f Bubble::getPosition() const
{
	return this->shape.getPosition();
}

void Bubble::update()
{
	this->shape.move(0.f, this->speed);
}

void Bubble::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
