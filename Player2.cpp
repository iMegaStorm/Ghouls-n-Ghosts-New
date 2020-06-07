#include "Player.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y) :
	animation(texture, imageCount, switchTime)
{
		this->speed = speed;
		row = 0;
		faceRight = true;
		powerUp = 1;

		mainCharacter.setSize(sf::Vector2f(94.0f,120.0f));
		mainCharacter.setPosition(x, y);
		mainCharacter.setTexture(texture);
}


Player::~Player(void)
{
}

void Player::Update(float deltaTime, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) 
{
	sf::Vector2f movement(0.0f, 0.0f);
	bool cantMove = false;
	
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
				movement.x -= speed * deltaTime;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
		if(!cantMove)
			{
				movement.x += speed * deltaTime;
			}
		}
		//else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W));
			//movement.y -= speed * deltaTime;
		


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
				animation.Update(2, 0.08f, faceRight);
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
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T) && cantMove)
		{
			row = 3;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			sf::Vector2u imageCount(4,5);
			if(movement.x == 0.0f)
			{
				Player player(texture, sf::Vector2u(6-2,5), 0.3f, 100.0f, x, y);
				row = 4;
				
			}
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && cantMove)
		{
			row = 5;
		}
		animation.Update(row, deltaTime, faceRight);
		mainCharacter.setTextureRect(animation.uvRect);
		mainCharacter.move(movement);
}

void Crouch ()
{


}

void Camera(sf::RenderWindow& window, float x, float y)
{
	sf::View cameraView;

	cameraView.reset (sf::FloatRect(0, 0, 300, 120));
	cameraView.setCenter(x,  y);

	if (x <= 5 * 32) 
			{
			
				cameraView.setCenter(150, y);
			}
			else if (x >= 17 * 32) 
			{
				cameraView.setCenter(550, y);
			}
		
		window.setView(cameraView);

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(mainCharacter);
}

void Player::intersects(sf::Sprite sprite, int type)
{
	if(mainCharacter.getGlobalBounds().intersects(sprite.getGlobalBounds())) powerUp = type;
}
