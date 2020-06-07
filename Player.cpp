#include "Player.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f Position, float Mass) :
	animation(texture, imageCount, switchTime)
{
		this->speed = speed;
		row = 0;
		faceRight = true;
		bool cantMove;
		bool canShoot;

		JumpCount = 0;
		mainCharacterGravity = 8.0f;
		mainCharacterPosition = Position;
		mainCharacterMass = Mass;
		mainCharacterOnGround = false;

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
	//view.reset(sf::FloatRect(0, 0, 800, 600));
				//(sf::Vector2f(0.0f,0.0f), sf::Vector2f(800, 600));
			//view.setCenter(player.GetPosition()); //setting the 2D camera to the main character
			//view.move(0,-180);

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
	else if (mainCharacter.getPosition().x > 400 && mainCharacter.getPosition().x < 1456)
	{
		//std::cout << "Inbetween" << std::endl;
		view.setCenter(mainCharacter.getPosition());
		view.move(0,-175);
	}
		window.setView(view);
}

void Player::Update(float deltaTime, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) 
{
	
	//Local Variables
	int GroundLevel = 570;

//Main "Update()"
	mainCharacterVelocity -= mainCharacterMass * mainCharacterGravity * speed;
	mainCharacterPosition.y -= mainCharacterVelocity * speed;
	mainCharacterSprite.setPosition(mainCharacterPosition);
	if (mainCharacterPosition.y >= (GroundLevel * 0.75f))
		{
		mainCharacterPosition.y = GroundLevel * 0.75f;
		mainCharacterVelocity = 0;
		mainCharacterOnGround = true;
		JumpCount = 0;
		}

	//Local Variables
	sf::Vector2f movement(0.0f, 0.0f);
	bool cantMove = false;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && mainCharacter.getPosition().x > 5)
	{
		movement.x -= speed * deltaTime;
		//std::cout << mainCharacter.getPosition().x << std::endl;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && mainCharacter.getPosition().x < 1809)
	{
		if(!cantMove)
		{
			movement.x += speed * deltaTime;
			//std::cout << mainCharacter.getPosition().x << std::endl;
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		Jump(500.0f);
	}

	if(movement.x == 0.0f)
	{
		row = 0;	
		cantMove = true;
	}
	else
	{
		row = 1;
		if (movement.x > 0.0f)
		{
			faceRight = true;
			cantMove = false;
		}
		else
		{
			faceRight = false;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && cantMove)
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
		if(movement.x == 0.0f)
		{
			row = 4;
		}
	}
	
	//std::cout << powerUp << std::endl;
		animation.Update(row, deltaTime, faceRight);
		mainCharacter.setTextureRect(animation.uvRect);
		mainCharacter.move(movement);
}

void Player::Jump(float velocity)
{
	//Main "Jump()"
	if (JumpCount < 2)
		{
		JumpCount++;
		mainCharacterVelocity = velocity;
		mainCharacterOnGround = false;
		}
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