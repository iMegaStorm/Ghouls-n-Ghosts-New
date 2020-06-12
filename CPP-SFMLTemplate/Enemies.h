#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Animation.h"

class Enemies
{
public:
	float x ;
	float y;
	float deltaaa;
	int currentHealth;
	int maxHealth;
	sf::Texture enemyText;
	sf::Vector2f enemySpeed;
	sf::RectangleShape healthBar, hBOutline;

public:
	void Enemies::Spawner();
	
	Enemies();
	~Enemies();
};

class Wolf : public Enemies
{
public:
	void Wolf::Update();
	void Wolf::Draw(sf::RenderWindow& window);


	sf::Sprite wolf;
	
	Wolf();	//ctor
	~Wolf();
};

class Dragon : public Enemies
{
public:
	void Dragon::Update();
	void Dragon::Draw(sf::RenderWindow& window);
	

	sf::Sprite dragon;

	Dragon(); //ctor
	~Dragon();
};

