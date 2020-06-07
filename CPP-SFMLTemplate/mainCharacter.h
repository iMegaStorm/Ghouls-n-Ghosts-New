#include <SFML/Graphics.hpp>

//Compiler directives
using namespace std;

class mainCharacter
{
public:
	mainCharacter();
	float x,y;
	int offsetX;
	int offsetY;
	int level;

	void init(std::string textureName, sf::Vector2f position,float mass);
	void Update(float speed);
	void Jump(float Velocity);
	void Draw(sf::RenderWindow& window);
	void Move(float speed, int offsetX, int offsetY);

	sf::Sprite GetSprite();

private:
	sf::Texture knightSpriteTexture;
	sf::Sprite knightSprite;
	sf::Vector2f knightSpritePosition;
	int jumpCount;
	float knightSpriteMass;
	float knightSpriteVelocity;
	float knightSpriteGravity;
	bool knightSpriteOnGround;


};