#include "Enemies.h"

Enemies::Enemies()
{
	currentHealth = 5;
	maxHealth = 5;
}


Enemies::~Enemies()
{
}


Wolf::Wolf()
{
	enemyTexture.loadFromFile("Assets/Enemies/Wolf.png");
	wolf.setTexture(enemyTexture);
	wolf.setScale(0.4,0.4);
	wolf.setOrigin(206/2, 158/2);

	hBOutline.setSize(sf::Vector2f(50,14));
	hBOutline.setOrigin(50,14 - wolf.getLocalBounds().height/2+120);
	hBOutline.setFillColor(sf::Color(0, 0, 0)); //Setting the hBOutline to black

	healthBar.setSize(sf::Vector2f(50, 12)); //Sets the size of the healthBar
	healthBar.setOrigin(49, 13  - wolf.getLocalBounds().height/2+120); //Attaching the healthBar to the wolf
	healthBar.setFillColor(sf::Color::Red); //Setting the healthBar to black
}

Wolf::~Wolf()
{
}

void Wolf::Update()
{
	if(currentHealth > 0)
	{
		int width = currentHealth * 48 / maxHealth; //Calculates how much to draw
		healthBar.setSize(sf::Vector2f(width, 12)); //Sets the size of the healthBar
		hBOutline.setPosition(wolf.getPosition().x+20, wolf.getPosition().y);
		healthBar.setPosition(wolf.getPosition().x+20, wolf.getPosition().y);
	}
	else
	{	
		currentHealth = 0; 
		enemyTexture.loadFromFile("Assets/Enemies/wolfDead.png");	
		wolf.setPosition(wolf.getPosition().x, 565);
	}
}

void Wolf::Draw(sf::RenderWindow& window)
{
	if(currentHealth > 0)
	{
		window.draw(hBOutline);
		window.draw(healthBar);
	}
		window.draw(wolf);
}

Dragon::Dragon()
{
	enemyTexture.loadFromFile("Assets/Enemies/Dragon.png");
	
	dragon.setTexture(enemyTexture);
	dragon.setScale(0.4,0.4);
	dragon.setOrigin(206/2, 158/2);

	hBOutline.setSize(sf::Vector2f(50,14));
	hBOutline.setOrigin(50,14 - dragon.getLocalBounds().height/2+230);
	hBOutline.setFillColor(sf::Color(0, 0, 0)); //Setting the hBOutline to black

	healthBar.setSize(sf::Vector2f(50, 12)); //Sets the size of the healthBar
	healthBar.setOrigin(49, 13  - dragon.getLocalBounds().height/2+230); //Attaching the healthBar to the dragon
	healthBar.setFillColor(sf::Color::Red); //Setting the healthBar to black
}

Dragon::~Dragon() 
{

}

void Dragon::Update()
{
	if(currentHealth > 0)
	{
		int width = currentHealth * 48 / maxHealth; //Calculates how much to draw
		healthBar.setSize(sf::Vector2f(width, 12)); //Sets the size of the healthBar
		hBOutline.setPosition(dragon.getPosition().x+20, dragon.getPosition().y);
		healthBar.setPosition(dragon.getPosition().x+20, dragon.getPosition().y);
	}
	else
	{	
		currentHealth = 0;
	}
}

void Dragon::Draw(sf::RenderWindow& window)
{
	if(currentHealth > 0)
	{
		window.draw(hBOutline);
		window.draw(healthBar);
	}
	window.draw(dragon);
}