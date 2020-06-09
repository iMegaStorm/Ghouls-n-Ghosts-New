#include "Enemies.h"

Wolf wolves[4];

Enemies::Enemies()
{
	float x;
	float y;
}


Enemies::~Enemies()
{
}

void Enemies::Spawner(sf::Clock& clock, sf::RenderWindow& window)
{
	
	//float frequency = 2.5f;
	//float amplitude = 70.0f;
	//int distance = 80;
	//for(int i = 1; i < 3; i++)
	//	{
	//		wolves[i].x = (i*6) * 32;
	//		wolves[i].y = 7 * 33;
	//		wolves[i].wolf.setPosition(wolves[i].x, wolves[i].y);
			

			/*snakes[i].EnemySpeed = Vector2f(10, 0);

			snakes[i].y = 7 * 33;
			snakes[i].x = (i*6)  * 32;

			birds[i].Bird.setScale(-1,1);
			birds[i].y = 5 * 32;
			birds[i].x = ((i+1)*7) * 32;

			snakes[i].x -=   6 * (snakes[i].EnemySpeed.x * dt);
			
			birds[i].x += distance *(-2 * dt);
			birds[i].y += (sin(frequency * dt) * amplitude);
			
			birds[i].Bird.setPosition(birds[i].x, birds[i].y);
			snakes[i].Enemy.setPosition(snakes[i].x, snakes[i].y);
			app.draw(birds[i].Bird);
			app.draw(snakes[i].Enemy);*/
			window.draw(wolves[i].wolf);
		}
}

Wolf::Wolf() : Enemies()
{

	currentHealth = 5;
	maxHealth = 5;

	enemyText.loadFromFile("Assets/Enemies/Wolf.png");
	
	wolf.setTexture(enemyText);
	//std::cout << "Wolf loaded" << std::endl;
}

Wolf::~Wolf()
{
}

void Wolf::Draw(sf::RenderWindow& window) 
{
	maxHealth = 5;
	wolf.setPosition(1000,545);
	wolf.setScale(0.4,0.4);
	wolf.setOrigin(206/2, 158/2); 

	if(currentHealth > 0)
	{
		sf::RectangleShape healthBar, hBOutline;
		hBOutline.setSize(sf::Vector2f(50,14));
		hBOutline.setOrigin(50,14 - wolf.getLocalBounds().height/2+120);
		hBOutline.setFillColor(sf::Color (0, 0, 0)); //Setting the hBOutline to black
		hBOutline.setPosition (wolf.getPosition().x+20, wolf.getPosition().y); //Sets the position of the hBOutline

		int width = currentHealth * 48 / maxHealth; //Calculates how much to draw
		healthBar.setSize(sf::Vector2f (width, 12)); //Sets the size of the healthBar
		healthBar.setOrigin (49, 13  - wolf.getLocalBounds().height/2+120); //Attaching the healthBar to the car
		healthBar.setFillColor(sf::Color::Red); //Setting the healthBar to black
		healthBar.setPosition (wolf.getPosition().x+20, wolf.getPosition().y); //Sets the position of the healthBar

		window.draw(hBOutline);
		window.draw(healthBar);
		window.draw(wolf);
	}
	else if(currentHealth <= 0) //Keeps the health bars from continously decreasing
	{
		currentHealth = 0; //943 move this when class fully created
		enemyText.loadFromFile("Assets/Enemies/wolfDead.png");
		wolf.setPosition(wolf.getPosition().x, wolf.getPosition().y+20);
		window.draw(wolf);
	}
		
		//std::cout << "Wolf is being drawn" << std::endl;
}
	


