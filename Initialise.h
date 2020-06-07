#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <iostream>

//Compiler Directives
using namespace sf;
using namespace std;

class Initialise
{
	list<Texture> TextureList; //Declare a texture list

public:
	Sprite LoadSpriteFromTexture(string, string, string); //Declaring the method inside the class

};

Sprite Initialise::LoadSpriteFromTexture(string Path, string Name, string Extension) 
{
	Texture Texture;
	if(!Texture.loadFromFile(Path + Name + "." + Extension)) //Loads a texture from file, //Assets/FileName/.Extension
	{
		system("pause"); //Pause the system
	}
	TextureList.push_front(Texture); //Pushes the texture to the front of the texture list
	Sprite Sprite(TextureList.front()); //Looks at the front of the texturelist and creates a sprite
	return Sprite; //Returns the sprite to wherever its being called from
}