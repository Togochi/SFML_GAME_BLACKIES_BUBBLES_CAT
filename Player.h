#pragma once

enum PLAYER_ANIMATION_STATE { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING, ATTACK };

class Player
{
private:

	//Variables
	int hp;
	int hpMax;

	//Resources
	sf::Sprite sprite;
	sf::Texture textureSheet;

	//Animation
	sf::IntRect currentFrame;
	sf::Clock animationTimer;

	short animState;
	bool animationSwitch;

	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float accelerationY;
	float drag;
	float gravity;
	float velocityMaxY;
	float velocityMinY;

	//Jump
	bool onGround;
	bool onBubble;

	//Combat
	bool attack;
	sf::FloatRect attackRect;

	//Init
	void initVariables();
	void initSprite();
	void initTexture();
	void initAnimation();
	void initPhysics();

public:
	Player();
	virtual ~Player();

	//Accessors
	const bool& getAnimationSwitch();
	const sf::FloatRect getPlayerBounds() const;
	const sf::Vector2f getPosition() const;
	const bool getOnGround() const;
	const bool getOnBubble() const;
	const float getVelovityX() const;

	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();
	void setOnGround(const bool g);
	void setOnBubble(const bool g);

	void setHp(const int hp);
	void gainHp(const int hp);
	void loseHp(const int value);

	//Functions
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMove();
	void updateAnimation();
	void update();
	void render(sf::RenderTarget& target);
};

