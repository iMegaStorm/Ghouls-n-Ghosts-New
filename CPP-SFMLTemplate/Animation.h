#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public: 
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime); //Only passing in the size of the texture, dont need to store it
	~Animation(void);

	void Update(int row, float deltatime); //Row - what row of the animation to access, deltaTime - time of the previous frame and current frame


public: //Public functions
	sf::IntRect uvRect; //To display the animation

private: //Private functions
	sf::Vector2u imageCount; //Vector2u as these will never be less than zero, so, you can't access an image thats not available
	sf::Vector2u currentImage; //Vector2u as these will never be less than zero, so, you can't access an image thats not available

	float totalTime; //Total time before switching to the next image
	float switchTime; //The switch time between images

};

