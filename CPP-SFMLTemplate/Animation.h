#pragma once
#include <SFML\Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation(void);

	void Update(int row, float deltaTime, bool faceRight);

public:
	sf::IntRect uvRect; //uvrect to display the animation

private:
	sf::Vector2u imageCount; //total number of images
	sf::Vector2u currentImage; //current image

	float totalTime; //total time taken before it switches to the next image
	float switchTime; 
};