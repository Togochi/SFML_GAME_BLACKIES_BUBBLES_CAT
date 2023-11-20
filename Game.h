#pragma once

#include "Player.h"
#include "Bubble.h"
#include "Enemy.h"

class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::Event event;
	
	//Player
	Player* player;

	//GUI
	sf::Font font;
	sf::Text pointText;
	sf::Text pauseText;
	sf::Text gameOverText;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Sound
	sf::SoundBuffer meowBuffer;
	sf::Sound meowSound;
	sf::SoundBuffer eatBuffer;
	sf::Sound eatSound;

	//Systems
	unsigned points;
	bool paused;

	//Bubbles
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Bubble*> bubbles;

	//Enemies
	float spawnTimerEnem;
	float spawnTimerMaxEnem;
	std::vector<Enemy*> enemies;

	//Init
	void initWindow();
	void initPlayer();


	void initGUI();
	void initSystems();

	void initBubbles();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	//Functions
	void run();
	void togglePause();
	void updatePollEvents();
	void updateCollision();
	void updateEnemyCollision();
	void updatePlayer();
	void updateBubbles();
	void updateEnemies();
	
	void updateGUI();
	void update();

	void renderGUI();
	void renderPlayer();
	void render();

	const sf::RenderWindow* getWindow() const;
};