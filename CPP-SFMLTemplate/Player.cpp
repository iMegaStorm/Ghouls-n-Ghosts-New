#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, sf::Vector2f Position, float Mass) :
	animation(texture, imageCount, switchTime)
{
		int currenthealth, maxHealth = 10;
		this->speed = speed;
		this->jumpHeight= jumpHeight;
		row = 0;
		faceRight = true;
		bool cantMove;
		bool canShoot;
		bool canAttack;
		bool gravity;

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

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && mainCharacter.getPosition().x > 5 && !cantMove)
	{
		velocity.x -= speed;
		//std::cout << mainCharacter.getPosition().x << std::endl;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && mainCharacter.getPosition().x < 1809 && !cantMove)
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
	window.draw(mainCharacter);
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