#pragma once


class Enemy
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f velocity;
	float dir_x;
	bool onGround;
	int type;

	int damage;
	int points;
	float resetTimer;
	float resetTimerMax;

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Accesorrs
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	const float& getDir() const;
	const int& getType() const;

	//Modifiers
	void setOnGround(const bool g);
    void setDir(float dir);
	void setPosition(float x, float y);
	void updateVelocity();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

