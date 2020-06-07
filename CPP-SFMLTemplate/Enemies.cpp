#include "Enemies.h"

Enemies::Enemies()
{

}


Enemies::~Enemies()
{
}

Wolf::Wolf() : Enemies()
{

	int currentHealth, maxHealth = 5;

	enemyText.loadFromFile("Assets/Enemies/Wolf.png");
	wolf.setTexture(enemyText);
	//std::cout << "Wolf loaded" << std::endl;

}

Wolf::~Wolf()
{
}

void Wolf::Draw(sf::RenderWindow& window) 
	{
		wolf.setPosition(1000,515);
		wolf.setScale(0.4,0.4);
		window.draw(wolf);
		//std::cout << "Wolf is being drawn" << std::endl;
	}
	


