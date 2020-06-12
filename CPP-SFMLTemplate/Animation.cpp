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

void Animation::Update(int row, int dRow, float deltaTime, bool faceRight, bool dFaceRight)
{
	currentImage.y = row; //Setting the currentImage.y to row
	dCurrentImage.y = dRow;
	totalTime += deltaTime; //Increment totalTime with deltaTime

	if (totalTime >= switchTime) //if totalTime is bigger or equal to switchTime then do the following
	{
		totalTime -= switchTime; //totalTime -= switchTime for a smoother animation, rather than just setting it to zero
		currentImage.x++; //Switches the current image we have to the next image
		dCurrentImage.x++;

		if (currentImage.x > 5) //If the currentImage is bigger than the image count 
		{
			currentImage.x = 0; //Then set it back to zero
		}
		if(dCurrentImage.x > 3)
		{
			dCurrentImage.x = 0;
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
	uvDRect.top = currentImage.y * uvDRect.height; //Setting the offset of the uvDRect

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

	if(dFaceRight)
	{
		uvDRect.left = currentImage.x * uvDRect.width;
		uvDRect.width = abs(uvRect.width); //makes the width positive
	}
	else
	{
		uvDRect.left = (currentImage.x + 1) * abs(uvDRect.width);
		uvDRect.width = -abs(uvDRect.width); //makes the width negative
	}

}

void Animation::DragonAnimation(sf::Vector2u dragonImageCount, float dragonSwitchTime, bool dFaceRight)
{
	dragonText.loadFromFile("Assets/Enemies/Dragon.png");
	this->imageCount = dragonImageCount;  //Pointer to this class, in order to access variables of the same name within the class
	this->switchTime = dragonSwitchTime;  //Pointer to this class, in order to access variables of the same name within the class

	uvDRect.width = dragonText.getSize().x / float(imageCount.x); //Getting the width of the texture and dividing it by the imageCount to get each individual image
	uvDRect.height = dragonText.getSize().y / float(imageCount.y); //Getting the width of the texture and dividing it by the imageCount to get each individual image

}