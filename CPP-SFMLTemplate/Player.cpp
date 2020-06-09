#include "Player.h"

Wolf enemyWolf;

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, sf::Vector2f Position, float Mass) :
	animation(texture, imageCount, switchTime)
{
		currentHealth = 10;
		maxHealth = 10;
		this->speed = speed;
		this->jumpHeight= jumpHeight;
		row = 0;
		faceRight = true;
		cantMove;
		canShoot;
		canAttack;
		notShooting = true;
		gravity;
		gameOver = false;


		mainCharacter.setSize(sf::Vector2f(94.0f,120.0f));
		mainCharacter.setOrigin(50/2,37/2);
		mainCharacter.setPosition(Position);
		mainCharacter.setTexture(texture);
}

Player::~Player(void)
{
}

void Player::View(sf::RenderWindow& window)
{
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 800, 600));
	view.setCenter(mainCharacter.getPosition());
	
	if (mainCharacter.getPosition().x <= 400) 
	{
		//std::cout << "Less than 400" << std::endl;
		view.setCenter(400,300);
	}
	else if (mainCharacter.getPosition().x >= 1456) 
	{
		//view.setCenter(550, y);
		view.setCenter(1456,300);
		//std::cout << "Greater than 1456" << std::endl;
	}
	else 
	{
		//std::cout << "Inbetween" << std::endl;
		view.setCenter(mainCharacter.getPosition().x, 300);
		//view.move(0,-175);
	}
		window.setView(view);
}

void Player::Update(float deltaTime, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) 
{
	//Local Variable
	//bool cantMove = false;
	velocity.x = 0.0f;
	bool gravity = true;

	if(!gameOver)
		{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && mainCharacter.getPosition().x > 5 && !cantMove && notShooting)
		{
			velocity.x -= speed;
			//std::cout << mainCharacter.getPosition().x << std::endl;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && mainCharacter.getPosition().x < 1809 && !cantMove && notShooting)
		{
			velocity.x += speed;
			//std::cout << "Your X axis is: " << mainCharacter.getPosition().x << std::endl;
			//std::cout << "Your Y axis is: " << mainCharacter.getPosition().y << std::endl;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && canJump)
		{
			//std::cout << "You're jumping " << gravity << "/" << velocity.y << std::endl;
			canJump = false; //If you jump then you can't jump again
			velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight); // Velocity for the jump, square root(float) of 2.0f * gravity * jumpHeight
		}
		else if (mainCharacter.getPosition().y < 475.0f && gravity)
		{
			std::cout << "Gravity active " << gravity << "/" << velocity.y << std::endl;
			velocity.y += 981.0f * deltaTime; //Gravity 
		}
		else if(mainCharacter.getPosition().y >= 470.0f)
		{
			canJump = true;
			gravity = false;
			velocity.y = 0.0f;
			mainCharacter.setPosition(mainCharacter.getPosition().x, 475);
			//std::cout << "On the ground " << gravity << "/" << velocity.y << "/" << mainCharacter.getPosition().y << std::endl;
		}


		if(velocity.x == 0.0f)
		{
			row = 0;
			canAttack = true;
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) //Whilst the S key is held, you cannot attack
			{
				canAttack = true;
				cantMove = false;
			}
		}
		else
		{
			row = 1;
			if (velocity.x > 0.0f && !cantMove)
			{
				faceRight = true;
				cantMove = false;
				canAttack = false;
			}
			else
			{
				faceRight = false;
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !cantMove && canAttack)
		{
			if (powerUp == 1)
			{
				row = 2;
			}
			else if (powerUp == 2)
			{
				row = 3;
			}
			else if (powerUp == 3)
			{
				row = 5;
			}
		}
 		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			canJump = false; 
			cantMove = true;
			canAttack = false;
			if(velocity.x == 0.0f)
			{
				row = 4;
			}
		}

	}
	if(currentHealth <= 0) //Keeps the health bars from continously decreasing
	{
		currentHealth = 0;
		row = 0; //943 change to dead animaton if included
		gameOver = true;
	}
	
	//std::cout << cantMove << " / " << canAttack << std::endl;
		animation.Update(row, deltaTime, faceRight);
		mainCharacter.setTextureRect(animation.uvRect);
		mainCharacter.move(velocity * deltaTime);
}


bool Player::Intersects(sf::Sprite sprite, int type, int randType, bool powerUpDisplay)
{
	if(mainCharacter.getGlobalBounds().intersects(sprite.getGlobalBounds())) 
	{
			powerUp = type;
			return true;
	}
	if(randType > 0)
	{
		return true;
	}
	return false;
}

void Player::Draw(sf::RenderWindow& window)
{
	//currentHealth = maxHealth = 10;
	maxHealth = 10;
	sf::RectangleShape healthBar, hBOutline;
	hBOutline.setSize(sf::Vector2f(100,14));
	hBOutline.setOrigin(50,14 - mainCharacter.getLocalBounds().height/2+70);
	hBOutline.setFillColor(sf::Color (0, 0, 0)); //Setting the hBOutline to black
	hBOutline.setPosition (mainCharacter.getPosition().x+20, mainCharacter.getPosition().y); //Sets the position of the hBOutline
	window.draw(hBOutline);

	int width = currentHealth * 98 / maxHealth; //Calculates how much to draw
	healthBar.setSize(sf::Vector2f (width, 12)); //Sets the size of the healthBar
	healthBar.setOrigin (49, 13  - mainCharacter.getLocalBounds().height/2+70); //Attaching the healthBar to the car
	healthBar.setFillColor(sf::Color (118, 255, 3)); //Setting the healthBar to black
	healthBar.setPosition (mainCharacter.getPosition().x+20, mainCharacter.getPosition().y); //Sets the position of the healthBar
	window.draw(healthBar);



	window.draw(mainCharacter);

	//std::cout << currentHealth << " / " << maxHealth << std::endl;
}



//void Player::Shoot(float deltaTime, sf::Sprite& fireBall, sf::Sprite& arrow, sf::RenderWindow& window)
//{
//	sf::Vector2f fireBallLocation(10,520);
//	sf::Vector2f arrowLocation(10,520);
//	sf::Clock animationClock;
//	float animationDelay = 0.04f;
//	this->cantMove;
//	std::cout << cantMove << std::endl;
//	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
//	{	
//		std::cout << powerUp << std::endl;
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && powerUp == 2) //The <Control> Keyboard Key Is Pressed...
//		{
//			
//			canShoot = false;
//			powerUp = true;
//			fireBallLocation.x = mainCharacter.getPosition().x -50;
//			fireBallLocation.y = mainCharacter.getPosition().y +20;
//			fireBall.setPosition(fireBallLocation.x,fireBallLocation.y);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && powerUp == 3 && canShoot) //The <Control> Keyboard Key Is Pressed...
//		{
//			canShoot = false;
//			powerUp = true;
//			arrowLocation.x = mainCharacter.getPosition().x;
//			arrowLocation.y = mainCharacter.getPosition().y +27;
//			arrow.setPosition(arrowLocation.x,arrowLocation.y);
//		}
//
//		if (powerUp && powerUp == 2)
//		{
//			fireBall.setPosition(fireBallLocation.x,fireBallLocation.y);
//			window.draw(fireBall);
//			if (animationClock.getElapsedTime().asSeconds() > animationDelay)
//			{
//				std::cout << "Yes" << std::endl;
//				fireBallLocation.x = fireBallLocation.x + 50;
//				animationClock.restart();
//			}
//			if (fireBallLocation.x > mainCharacter.getPosition().x+400)
//			{
//				//fireBall.setPosition(fireBallLocation.x,fireBallLocation.y);
//				canShoot = true;
//				powerUp = false;
//			}
//		}
//
//		if (powerUp && powerUp == 3)
//		{
//			arrow.setPosition(arrowLocation.x,arrowLocation.y);
//			window.draw(arrow);
//			if (animationClock.getElapsedTime().asSeconds() > animationDelay)
//			{
//				arrowLocation.x = arrowLocation.x + 50;
//				animationClock.restart();
//			}
//			if (arrowLocation.x > mainCharacter.getPosition().x+400)
//			{
//				//arrow.setPosition(arrowLocation.x,arrowLocation.y);
//				canShoot = true;
//				powerUp = false;
//			}
//		}
//	}
//}