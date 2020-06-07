#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
class Player
{

//public:
//	sf::View cameraView;
	float x;
	float y;

public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y);
	~Player(void);

	void Update(float deltaTime, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	void Crouch ();
	void Camera (sf::RenderWindow& window, float x, float y);
	void Draw(sf::RenderWindow& window);
	void intersects(sf::Sprite sprite, int type);

private:
	sf::RectangleShape mainCharacter;
	Animation animation;
	unsigned int row; //never less than 0
	float speed;
	int powerUp;
	bool faceRight;

};

