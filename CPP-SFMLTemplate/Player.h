#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <iostream>
#include "Enemies.h"

class Player
{

public:

	float x;
	float y;

public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, sf::Vector2f Position, float Mass);
	~Player(void);

	void View(sf::RenderWindow& window);
	void Update(float deltaTime, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	void Draw(sf::RenderWindow& window);
	bool Intersects(sf::Sprite sprite, int type, int randType, bool powerUpDisplay);
	sf::Vector2f GetPosition() { return mainCharacter.getPosition(); }

public:
	sf::RectangleShape mainCharacter;
	sf::View view;
	Animation animation;
	unsigned int row; //never less than 0
	float speed;
	int powerUp;
	int currentHealth;
	int maxHealth;
	bool faceRight;
	bool cantMove;
	bool canShoot;
	bool canAttack;
	bool notShooting;
	bool gravity;
	bool gameOver;

	sf::Sprite mainCharacterSprite;


private:
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
};

