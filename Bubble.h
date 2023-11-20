#pragma once


class Bubble
{
private:

	sf::CircleShape shape;

	//Variable
	float speed;
	int points;


	//Init
	void initVariables();
	void initShape();

public:
	Bubble(float pos_x, float pos_y); 
	~Bubble();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int getPoints() const;

	const sf::Vector2f getPosition() const;

	//Functions
	void update();
	void render(sf::RenderTarget& target);

};


