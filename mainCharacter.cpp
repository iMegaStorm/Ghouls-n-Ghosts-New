#include "mainCharacter.h"
#include <iostream>

mainCharacter::mainCharacter()
{
	jumpCount = 0;
	knightSpriteGravity = 8.0f;
	knightSpritePosition.x = x;
	knightSpritePosition.y = y;

}



void mainCharacter::init(std::string textureName, sf::Vector2f position,float mass)
{
	knightSpritePosition = position;
	knightSpriteMass = mass;
	knightSpriteOnGround = false;

	knightSpriteTexture.loadFromFile(textureName.c_str());
	knightSprite.setTexture(knightSpriteTexture);
	knightSprite.setPosition(knightSpritePosition.x, knightSpritePosition.y);
	knightSprite.setOrigin(160/2, 160/2);
}

void mainCharacter::Update(float speed)
{
	//Local Variable
	int groundLevel = 655;

	//Main "Update()"
	knightSpriteVelocity -= knightSpriteMass * knightSpriteGravity * speed;
	knightSpritePosition.y -= knightSpriteVelocity * speed;
	knightSprite.setPosition(knightSpritePosition.x, knightSpritePosition.y);
	if (knightSpritePosition.y >= (groundLevel * 0.75f))
		{
		knightSpritePosition.y = groundLevel * 0.75f;
		knightSpriteVelocity = 0;
		knightSpriteOnGround = true;
		jumpCount = 0;
		}
}

void mainCharacter::Jump(float velocity)
{
	//Local Variables

//Main "Jump()"

	if (jumpCount < 2)
		{
		jumpCount++;
		knightSpriteVelocity = velocity;
		knightSpriteOnGround = false;
		}
}

void mainCharacter::Move(float speed, int offsetX, int offsetY)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			knightSpritePosition.x = knightSpritePosition.x +1 +offsetX;
			//knightSprite.move(50.0f * speed, 0);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
		knightSpritePosition.x = knightSpritePosition.x -1 -offsetX;
		//knightSprite.move(-50.0f * speed, 0);
		}



}

void Draw()
{

}

sf::Sprite mainCharacter::GetSprite()
{
	return knightSprite;
}