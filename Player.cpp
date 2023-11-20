#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);

	this->currentFrame = sf::IntRect(200, 500, 200, 100);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setOrigin(this->getPlayerBounds().width / 2, this->getPlayerBounds().top);
	this->sprite.setScale(0.6f, 0.6f);
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/spritesheetcat.png"))
	{
		std::cerr << "ERROR::PLAYER::INITTEXTURE: error loading texture from file!" << '\n';
	}
	this->textureSheet.setSmooth(true);
}

void Player::initAnimation()
{
	this->animState = PLAYER_ANIMATION_STATE::IDLE;
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 8.f;
	this->velocityMin = 1.f;
	this->acceleration = 4.f;
	this->drag = 0.8f;
	this->gravity = 1.f;

	this->accelerationY = 35.f;
	this->velocityMinY = 0;
	this->velocityMaxY = 70.f;
	this->onGround = false;
	this->onBubble = false;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
	this->initPhysics();
}

Player::~Player()
{
}

const bool& Player::getAnimationSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}



const sf::FloatRect Player::getPlayerBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}


const bool Player::getOnGround() const
{
	return this->onGround;
}

const bool Player::getOnBubble() const
{
	return this->onBubble;
}

const float Player::getVelovityX() const
{
	return this->velocity.x;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}


void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}


void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}


void Player::setOnGround(const bool g)
{
	this->onGround = g;
}

void Player::setOnBubble(const bool g)
{
	this->onBubble = g;
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::gainHp(const int hp)
{
	this->hp += hp;
	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}


void Player::updateAnimation()
{
	if (this->animState == PLAYER_ANIMATION_STATE::IDLE && (this->onGround || this->onBubble)) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.05f || this->getAnimationSwitch())
		{
			// IDLE animation
			this->currentFrame = sf::IntRect(200, 500, 200, 100);

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::MOVING_LEFT && (this->onGround || this->onBubble))
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.04f || this->getAnimationSwitch())
		{

			this->currentFrame.left = 0.f;
			this->currentFrame.top += 100.f;
			if (this->currentFrame.top >= 1100.f)
				this->currentFrame.top = 0.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(0.6f, 0.6f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::MOVING_RIGHT && (this->onGround || this->onBubble))
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.04f || this->getAnimationSwitch())
		{

			this->currentFrame.left = 0.f;
			this->currentFrame.top += 100.f;
			if (this->currentFrame.top >= 1100.f)
				this->currentFrame.top = 0.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
		this->sprite.setScale(-0.6f, 0.6f);

	}

	else if (!this->onGround && !this->onBubble)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.06f || this->getAnimationSwitch())
		{
			this->currentFrame.left = 600.f;
			this->currentFrame.top += 100.f;
			if (this->currentFrame.top > 1200.f)
				this->currentFrame.top = 0.f;


			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else
		this->animationTimer.restart();

}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	//Acceleration
	this->velocity.x += dir_x * this->acceleration;
	this->velocity.y += dir_y * this->accelerationY;

	//Limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}

}

void Player::updatePhysics()
{
	//Gravity
	if (!this->onGround)
	{
		this->velocity.y += this->gravity;
	}
	if (std::abs(this->velocity.y) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	//Deceleration
	this->velocity *= this->drag;

	//Limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMinY)
		this->velocity.y = 0.f;

	this->sprite.move(this->velocity);
}

void Player::updateMove()
{
	this->animState = PLAYER_ANIMATION_STATE::IDLE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATE::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATE::MOVING_RIGHT;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (this->onGround || this->onBubble))
	{
		this->move(0.f, -1.f);
		this->animState = PLAYER_ANIMATION_STATE::JUMPING;
		this->onGround = false;
		this->onBubble = false;
	}

}

void Player::update()
{
	this->updateMove();
	this->updateAnimation();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
