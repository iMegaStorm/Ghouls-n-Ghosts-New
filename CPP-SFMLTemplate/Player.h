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
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, sf::Vector2f Position);
	~Player();

	void View(sf::RenderWindow& window);
	void Update(float deltaTime, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() { return mainCharacter.getPosition(); }

public:
	sf::RectangleShape healthBar, hBOutline;
	sf::RectangleShape mainCharacter;
	sf::View view;
	Animation animation;

	unsigned int row; //never less than 0
	float speed;
	int powerUp;
	int currentHealth;
	int maxHealth;
	bool faceRight;
	bool dFaceRight;
	bool cantMove;
	bool canShoot;
	bool canAttack;
	bool notShooting;
	bool gravity;
	bool gameOver;
	bool gameWon;

	sf::Sprite mainCharacterSprite;


private:
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
};

