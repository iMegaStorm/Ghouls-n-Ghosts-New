#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

class Enemies
{
public:
	float x;
	float y;
	int currentHealth;
	int maxHealth;
	sf::Texture enemyText;
	sf::Vector2f enemySpeed;



	Enemies(void);
	~Enemies(void);
};

class Wolf : public Enemies
{
public:
	void Wolf::Draw(sf::RenderWindow& window);

	sf::Sprite wolf;
	

	Wolf();
	~Wolf();
};
