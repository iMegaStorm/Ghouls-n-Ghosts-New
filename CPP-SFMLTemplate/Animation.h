#pragma once
#include <SFML\Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	void Animation::Update(int row, float deltaTime, bool faceRight);
	void Animation::DragonAnimation(sf::Vector2u dragonImageCount, float dragonSwitchTime, bool dFaceRight);

public:
	sf::IntRect uvRect; //uvrect to display the animation
	sf::IntRect uvDRect;
private:
	//Player
	sf::Vector2u imageCount; //total number of images
	sf::Vector2u currentImage; //current image
	float totalTime; //total time taken before it switches to the next image
	float switchTime; 
};