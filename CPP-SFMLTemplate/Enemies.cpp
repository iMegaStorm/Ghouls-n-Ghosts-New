#include "Enemies.h"

Enemies::Enemies()
{
}


Enemies::~Enemies()
{
}


Wolf::Wolf()
{
	//this init enemies type wolf
	 
	currentHealth = 5;
	maxHealth = 5;
	enemyText.loadFromFile("Assets/Enemies/Wolf.png");
	
	wolf.setTexture(enemyText);
	wolf.setScale(0.4,0.4);
	wolf.setOrigin(206/2, 158/2);

	hBOutline.setSize(sf::Vector2f(50,14));
	hBOutline.setOrigin(50,14 - wolf.getLocalBounds().height/2+120);
	hBOutline.setFillColor(sf::Color (0, 0, 0)); //Setting the hBOutline to black

	healthBar.setSize(sf::Vector2f (50, 12)); //Sets the size of the healthBar
	healthBar.setOrigin (49, 13  - wolf.getLocalBounds().height/2+120); //Attaching the healthBar to the car
	healthBar.setFillColor(sf::Color::Red); //Setting the healthBar to black

	//std::cout << "Wolf loaded" << std::endl;

}

Wolf::~Wolf()
{
}

void Wolf::Update()
{
	if(currentHealth > 0)
	{
		int width = currentHealth * 48 / maxHealth; //Calculates how much to draw
		healthBar.setSize(sf::Vector2f (width, 12)); //Sets the size of the healthBar
		hBOutline.setPosition (wolf.getPosition().x+20, wolf.getPosition().y);
		healthBar.setPosition (wolf.getPosition().x+20, wolf.getPosition().y);
	}
	else if(currentHealth <= 0)
	{	
		currentHealth = 0; 
		enemyText.loadFromFile("Assets/Enemies/wolfDead.png");	
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
	currentHealth = 5;
	maxHealth = 5;
	enemyText.loadFromFile("Assets/Enemies/Dragon.png");
	
	dragon.setTexture(enemyText);
	dragon.setScale(0.4,0.4);
	dragon.setOrigin(206/2, 158/2);

	hBOutline.setSize(sf::Vector2f(50,14));
	hBOutline.setOrigin(50,14 - dragon.getLocalBounds().height/2+230);
	hBOutline.setFillColor(sf::Color (0, 0, 0)); //Setting the hBOutline to black

	healthBar.setSize(sf::Vector2f (50, 12)); //Sets the size of the healthBar
	healthBar.setOrigin (49, 13  - dragon.getLocalBounds().height/2+230); //Attaching the healthBar to the car
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
		healthBar.setSize(sf::Vector2f (width, 12)); //Sets the size of the healthBar
		hBOutline.setPosition (dragon.getPosition().x+20, dragon.getPosition().y);
		healthBar.setPosition (dragon.getPosition().x+20, dragon.getPosition().y);
	}
	else if(currentHealth <= 0)
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