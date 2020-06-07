#include "Animation.h"
#include <iostream>


Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;  //Pointer to this class, in order to access variables of the same name within the class
	this->switchTime = switchTime;  //Pointer to this class, in order to access variables of the same name within the class
	totalTime = 0.0f; //Set total time to zero
	currentImage.x = 0; //Setting the current image to zero

	uvRect.width = texture->getSize().x / float(imageCount.x); //Getting the width of the texture and dividing it by the imageCount to get each individual image
	uvRect.height = texture->getSize().y / float(imageCount.y); //Getting the width of the texture and dividing it by the imageCount to get each individual image
}


Animation::~Animation(void)
{
}

void Animation::Update(int row, float deltaTime, bool faceRight)
{
	currentImage.y = row; //Setting the currentImage.y to row
	totalTime += deltaTime; //Increment totalTime with deltaTime

	if (totalTime >= switchTime) //if totalTime is bigger or equal to switchTime then do the following
	{
		totalTime -= switchTime; //totalTime -= switchTime for a smoother animation, rather than just setting it to zero
		currentImage.x++; //Switches the current image we have to the next image
		
		if (currentImage.x > 5) //If the currentImage is bigger than the image count 
		{
			currentImage.x = 0; //Then set it back to zero
		}
		//else if(currentImage.x >= 3 && row == 0)
		//{
		//	currentImage.x = 0;
		//}
		//else if (currentImage.x >= 4 && row == 2)
		//{
		//	currentImage.x = 0;
		//}
		//else if (currentImage.x >= 3 && row == 4)
		//{
		//	currentImage.x = 0;
		//}
	}
	//std::cout << currentImage.x << std::endl;

	uvRect.top = currentImage.y * uvRect.height; //Setting the offset of the uvRect

	if(faceRight)
	{
			uvRect.left = currentImage.x * uvRect.width;
			uvRect.width = abs(uvRect.width); //makes the width positive
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width); //makes the width negative
	}
}