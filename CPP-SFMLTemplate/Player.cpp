#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, sf::Vector2f Position) :
	animation(texture, imageCount, switchTime)
{
		currentHealth = 10;
		maxHealth = 10;
		this->speed = speed;
		this->jumpHeight = jumpHeight;
		row = 0;
		faceRight = true;
		cantMove;
		canShoot;
		canAttack;
		notShooting = true;
		gravity;
		gameOver = false;
		gameWon = false;
		x = 100;
		y = 475;

		mainCharacter.setSize(sf::Vector2f(94.0f,120.0f));
		mainCharacter.setOrigin(50/2,37/2);
		mainCharacter.setPosition(Position);
		mainCharacter.setTexture(texture);

		hBOutline.setSize(sf::Vector2f(100,14));
		hBOutline.setOrigin(50,14 - mainCharacter.getLocalBounds().height/2+70);
		hBOutline.setFillColor(sf::Color(0, 0, 0)); //Setting the hBOutline to black
	
		healthBar.setOrigin(49, 13  - mainCharacter.getLocalBounds().height/2+70); //Attaching the healthBar to the player
		healthBar.setFillColor(sf::Color(118, 255, 3)); //Setting the healthBar to black
}

Player::~Player(void)
{
}

void Player::View(sf::RenderWindow& window)
{
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 800, 600));
	view.setCenter(mainCharacter.getPosition());
	
	if(mainCharacter.getPosition().x <= 400 || (gameWon || gameOver)) 
	{
		view.setCenter(400,300);
	}
	else if(mainCharacter.getPosition().x >= 1456 && !gameOver && !gameWon) 
	{
		view.setCenter(1456,300);
	}
	else 
	{
		view.setCenter(mainCharacter.getPosition().x, 300);
	}
		window.setView(view);
}

void Player::Update(float deltaTime, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) 
{

	int width = currentHealth * 98 / maxHealth; //Calculates how much to draw
	healthBar.setSize(sf::Vector2f(width, 12)); //Sets the size of the healthBar
	hBOutline.setPosition(mainCharacter.getPosition().x+20, mainCharacter.getPosition().y); //Sets the position of the hBOutline and updates per frame
	healthBar.setPosition(mainCharacter.getPosition().x+20, mainCharacter.getPosition().y); //Sets the position of the healthbar and updates per frame
	velocity.x = 0.0f;
	bool gravity = true;

	if(!gameOver)
		{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && mainCharacter.getPosition().x > 5 && !cantMove && notShooting)
		{
			velocity.x -= speed;
			velocity.x -= x;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && mainCharacter.getPosition().x < 1809 && !cantMove && notShooting)
		{
			velocity.x += speed;
			velocity.x += x;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && canJump)
		{
			canJump = false; //If you jump then you can't jump again
			velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight); // Velocity for the jump, square root(float) of 2.0f * gravity * jumpHeight
		}
		else if(mainCharacter.getPosition().y < 475.0f && gravity)
		{
			velocity.y += 981.0f * deltaTime; //Gravity 
		}
		else if(mainCharacter.getPosition().y >= 470.0f)
		{
			canJump = true;
			gravity = false;
			velocity.y = 0;
			mainCharacter.setPosition(mainCharacter.getPosition().x, 475);
		}
		//std::cout << "X axis: " << mainCharacter.getPosition().x << " Y axis: " << mainCharacter.getPosition().y <<std::endl;

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
			if(velocity.x > 0.0f && !cantMove)
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
			if(powerUp == 1)
			{
				row = 2;
			}
			else if(powerUp == 2)
			{
				row = 4;
			}
		}
 		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && canJump)
		{
			canJump = false; 
			cantMove = true;
			canAttack = false;
			if(velocity.x == 0.0f)
			{
				row = 3;
			}
		}
	}
	if(currentHealth <= 0) //Keeps the health bars from continously decreasing
	{
		currentHealth = 0;
		gameOver = true;
		velocity.y = 0;
	}
	if(mainCharacter.getPosition().x < 5)
	{
		mainCharacter.setPosition(6, mainCharacter.getPosition().y);
	}

	animation.Update(row, deltaTime, faceRight);
	mainCharacter.setTextureRect(animation.uvRect);
	mainCharacter.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(hBOutline);
	window.draw(healthBar);
	window.draw(mainCharacter);
}