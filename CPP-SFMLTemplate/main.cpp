//Updated 23/02/2020

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Initialise.h"
#include "Player.h"
#include "Enemies.h"

//Compiler Directives
using namespace std;

RenderWindow window(VideoMode(800, 600), "Ghouls 'n Ghosts"); // 13 squares wide, 9 square high
//sf::View view;


Initialise init;
Enemies enemies;
Wolf wolf;

//Game Screen Variables
	//Assigns a value for each screen
const int GAME_MENU_SCREEN = 0; //Main game screen
const int INSTRUCTIONS_MENU_SCREEN = 1; //Instructions Menu screen
const int LEVEL_1_SCREEN = 2; // Level 1 of the game
const int GAME_OVER_SCREEN = 3; //Game Over screen
int CURRENT_SCREEN = LEVEL_1_SCREEN; //Using current screen in order to switch to another screen
int level = 1; 
int offsetX = 0;
int offsetY = 0;

Vector2i MouseCursorLocation(0,0);

sf::Vector2f fireBallLocation(10,520);
sf::Vector2f arrowLocation(10,520);

bool weaponActive = false;

/*void drawDebugLayout(int playField[20][50]) {
	for (int i = 0; i < 15; i++)
    {
        cout<<  endl;
	}


	int i, j;
	for(i=0; i<20; i++)
	{
		for(j=0; j<50; j++)
		{
			cout<<playField[i][j]<<' ';	
		}
		cout<<'\n';
	}
	cout<<'\n';
}*/



void spawnGrass(int tileGrass, int tilePositionX, int tilePositionY, Sprite tiles[1])
{
	Sprite grass = tiles[tileGrass = 0];
	grass.setPosition(tilePositionX *32, tilePositionY *30);
	window.draw(grass);
}

void Init (Sprite &gameScreen, Sprite &playButton, Sprite &exitButton, Sprite &startButton, Sprite &instructionMenu,Sprite &background, Sprite &health,
Sprite &healthPotion, Sprite &chest, Sprite &grass, Sprite &fireBall, Sprite &arrow, Sprite &swordPowerUp, Sprite &spellPowerUp, Sprite &bowPowerUp)
{
	gameScreen = init.LoadSpriteFromTexture("Assets/Menus/", "GameScreen", "png");

	instructionMenu = init.LoadSpriteFromTexture("Assets/Menus/", "InstructionsMenu", "png");

	background = init.LoadSpriteFromTexture("Assets/Menus/", "BackGround", "png");
	background.setPosition(0,-28);

	playButton = init.LoadSpriteFromTexture("Assets/Menus/", "playButton", "png");
	playButton.setOrigin(90.0/2, 42.0/2);
	playButton.setPosition(390, 300);

	exitButton = init.LoadSpriteFromTexture("Assets/Menus/", "exitButton", "png");
	exitButton.setOrigin(86.0/2, 42.0/2);
	exitButton.setPosition(390, 400);

	startButton = init.LoadSpriteFromTexture("Assets/Menus/", "startButton", "png");
	startButton.setOrigin (100.0/2, 42.0/2);
	startButton.setPosition (400, 550);

	health = init.LoadSpriteFromTexture("Assets/Objects/", "Health", "png");
	health.setPosition(50, 50);
	
	healthPotion = init.LoadSpriteFromTexture("Assets/Objects/", "HealthPotion", "png");
	healthPotion.setPosition (400, 544);

	chest = init.LoadSpriteFromTexture("Assets/Objects/", "chest", "png");
	chest.setScale(3, 3);
	chest.setPosition (450, 527);

	grass = init.LoadSpriteFromTexture("Assets/Menus/", "placeHolderTileset", "png");

	fireBall = init.LoadSpriteFromTexture("Assets/WeaponAnimations/", "Frame1", "png");
	fireBall.setScale(0.2, 0.2);

	arrow = init.LoadSpriteFromTexture("Assets/WeaponAnimations/", "Arrow", "png");
	arrow.setScale(1.5, 1.5);

	swordPowerUp = init.LoadSpriteFromTexture("Assets/Objects/", "SwordPowerUp", "png");
	//swordPowerUp.setPosition(150, 527); 
	swordPowerUp.setPosition(-50, -50); 

	spellPowerUp = init.LoadSpriteFromTexture("Assets/Objects/", "SpellPowerUp", "png");
	//spellPowerUp.setPosition(600, 527);
	spellPowerUp.setPosition(-50, -50); 
	bowPowerUp = init.LoadSpriteFromTexture("Assets/Objects/", "BowPowerUp", "png");
	//bowPowerUp.setPosition(500, 527);
	bowPowerUp.setPosition(-50, -50); 
}

int main()
{
//Local Variables
	//Event Variables
	Event event;
	//Local Variables
	Clock ClockTime;
	Time speed;

	sf::Clock animationClock;
	float animationDelay = 0.04f;

	int currentHealth = 3;
	bool canShoot = true;
	bool canShootRight;
	bool canShootLeft;
	bool newChest = true;

	Sprite gameScreen, playButton, exitButton, startButton, instructionMenu, background, health, healthPotion, chest, grass, fireBall, arrow, swordPowerUp, spellPowerUp, bowPowerUp;
	Init(gameScreen, playButton, exitButton, startButton, instructionMenu, background, health, healthPotion, chest, grass, fireBall, arrow, swordPowerUp, spellPowerUp, bowPowerUp);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("Assets/Main Character/MainCharacterSheet.png");
	Player player(&playerTexture, sf::Vector2u(6,6), 0.3f, 100.0f, 150.0f, sf::Vector2f(100.0f, 475.0f), 200);

	
	float deltaTime = 0.0f;
	sf::Clock clock;

	window.setFramerateLimit(60);
	

	int i, j;
	srand(time(NULL));
	int playField[20][58] =
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	};
	//drawDebugLayout(playField);


Sprite tiles[1] = {grass};
	
	while (window.isOpen()) //The Game Window Loop
	{
		deltaTime = ClockTime.restart().asSeconds();
		while (window.pollEvent(event)) //Checks for input for keyboard
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) //Checks to see if the window is closed and then executes the code
			{
				window.close(); //closes the window
				break;
			}			
			if (event.type == Event::MouseMoved) //Mouse Movement
				{
				MouseCursorLocation = Mouse::getPosition(window); //Get position within the window
				}
			else if (event.type == Event::MouseButtonPressed) //Checks input of the mouse button is pressed
				{
				if (event.mouseButton.button == Mouse::Left && CURRENT_SCREEN == GAME_MENU_SCREEN || CURRENT_SCREEN == INSTRUCTIONS_MENU_SCREEN)
					{
					if ((MouseCursorLocation.x > playButton.getPosition().x - playButton.getGlobalBounds().width/2) && (MouseCursorLocation.x < (playButton.getPosition().x + playButton.getGlobalBounds().width/2)) && (MouseCursorLocation.y > playButton.getPosition().y - playButton.getGlobalBounds().height/2) && (MouseCursorLocation.y < (playButton.getPosition().y + playButton.getGlobalBounds().height/2)))
						{
							CURRENT_SCREEN = INSTRUCTIONS_MENU_SCREEN; //Changes the current screen if you click on the play button
						}
					else if ((MouseCursorLocation.x > exitButton.getPosition().x - exitButton.getGlobalBounds().width/2) && (MouseCursorLocation.x < (exitButton.getPosition().x + exitButton.getGlobalBounds().width/2)) && (MouseCursorLocation.y > exitButton.getPosition().y - exitButton.getGlobalBounds().height/2) && (MouseCursorLocation.y < (exitButton.getPosition().y + exitButton.getGlobalBounds().height/2)))
						{
							window.close(); //Closes the window if you click on the exit button
						}
					else if ((MouseCursorLocation.x > startButton.getPosition().x - startButton.getGlobalBounds().width/2) && (MouseCursorLocation.x < (startButton.getPosition().x + startButton.getGlobalBounds().width/2)) && (MouseCursorLocation.y > startButton.getPosition().y - startButton.getGlobalBounds().height/2) && (MouseCursorLocation.y < (startButton.getPosition().y + startButton.getGlobalBounds().height/2)))
						{
							CURRENT_SCREEN = LEVEL_1_SCREEN; //Changes the current screen if you click on the start button
						}
					}
				}
				if(event.type == Event::KeyPressed) 
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canShoot && player.powerUp == 2 && player.canAttack && player.cantMove == false) //The <Control> Keyboard Key Is Pressed...
						{
						canShoot = false;
						weaponActive = true;
						player.notShooting = false; //After firing right/left once turning into the opposite direction would freeze the animation, this prevents that by locking the player into the animation
						if(player.faceRight == true)
						{
							fireBallLocation.x = player.GetPosition().x +20;
							fireBallLocation.y = player.GetPosition().y +30;
							fireBall.setRotation(0); //Sets fireBall direction to face right
							canShootRight = true; //Prevents being able to spam left to right 
							canShootLeft = false; //Prevents being able to spam left to right 
							cout << fireBallLocation.x << " /  " << fireBallLocation.y << endl;
						}
						else if(player.faceRight == false)
						{
							fireBallLocation.x = player.GetPosition().x +10;
							fireBallLocation.y = player.GetPosition().y +60;
							fireBall.setRotation(180); //Sets fireBall direction to face left
							canShootRight = false;  //Prevents being able to spam left to right 
							canShootLeft = true; //Prevents being able to spam left to right 
							cout << fireBallLocation.x << " /  " << fireBallLocation.y << endl;
						}
						fireBall.setPosition(player.mainCharacter.getPosition());
						}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canShoot && player.powerUp == 3 && player.canAttack && player.cantMove == false) //The <Control> Keyboard Key Is Pressed...
						{
						canShoot = false;
						weaponActive = true;
						player.notShooting = false; //After firing right/left once turning into the opposite direction would freeze the animation, this prevents that by locking the player into the animation
						if(player.faceRight == true)
						{
							arrowLocation.x = player.GetPosition().x;
							arrowLocation.y = player.GetPosition().y +27;
							arrow.setRotation(0); //Sets fireBall direction to face right
							canShootRight = true; //Prevents being able to spam left to right 
							canShootLeft = false; //Prevents being able to spam left to right 
						}
						else if(player.faceRight == false)
						{
							arrowLocation.x = player.GetPosition().x +30;
							arrowLocation.y = player.GetPosition().y +77;
							arrow.setRotation(180); //Sets arrow direction to face left
							canShootRight = false;  //Prevents being able to spam left to right 
							canShootLeft = true; //Prevents being able to spam left to right
							cout << "1" << endl;
						}
						arrow.setPosition(player.mainCharacter.getPosition());
						}
				}			
		}
		//cout << sf::Keyboard::isKeyPressed(sf::Keyboard::Space) << "/" << player.powerUp << "/" << player.canAttack << "/" << player.cantMove << endl;
	window.clear();

	if (CURRENT_SCREEN == GAME_MENU_SCREEN)
	{
		window.draw(gameScreen);
		window.draw(playButton);
		window.draw(exitButton);
	}
	else if (CURRENT_SCREEN == INSTRUCTIONS_MENU_SCREEN)
	{
		window.draw(instructionMenu);
		window.draw(startButton);
	}
	else if (CURRENT_SCREEN == LEVEL_1_SCREEN)
	{
		window.draw(background);

		for(i = 0; i<20; i++) 
		{
			for(j = 0; j<58; j++)
			{
				if(playField[i][j] == 2)
				{
					spawnGrass (playField[i][j], j, i, tiles);
				}
			}
		}
		int randNo;
		if (player.Intersects(chest,0, 0, false) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && newChest)
		{
			for(i = 0; i < 1; i++)
			{
				srand(time(NULL));
				//randNo = rand() % 3 + 1;
				newChest = false;
				randNo = 3;
				//cout << "Your randNo is " << randNo << endl;
			}
			player.powerUp = randNo;
			chest.setPosition(-50, -50);
		}

		if(randNo == 1)
		{
			swordPowerUp.setPosition(450, 400);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				//cout << "Working " << randNo << endl;
				swordPowerUp.setColor(Color::Transparent);
				//swordPowerUp.setPosition (-50,-50);
				//powerUp = 1;
			}
		}
		else if(randNo == 3)
		{
			bowPowerUp.setPosition(450, 400);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				//cout << "Working " << randNo << endl;
				bowPowerUp.setColor(Color::Transparent);
				//bowPowerUp.setPosition (-50,-50);
				//powerUp = 2;
			}
		}
		else if(randNo == 2)
		{
			spellPowerUp.setPosition(450, 400);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				//cout << "Working " << randNo << endl;
				spellPowerUp.setColor(Color::Transparent);
				//spellPowerUp.setPosition (-50,-50);
				//powerUp = 3;
			}
		}

		//Healing potion
		if(player.mainCharacter.getGlobalBounds().intersects(healthPotion.getGlobalBounds()) && player.currentHealth < 10 && player.currentHealth > 0)
		{
			if(player.currentHealth < 10 && player.currentHealth > 7)
			{
				player.currentHealth = player.maxHealth; //If player health is 8 or 9 then set it to 10
			}
			else if(player.currentHealth <= 7)
			{
				player.currentHealth += 3;
			}
			else if(player.currentHealth > 0 && player.currentHealth < 7)
			{
				player.currentHealth += 3;
			}
			healthPotion.setPosition(-50,-50);
		}

		//Combat
		if(player.mainCharacter.getGlobalBounds().intersects(wolf.wolf.getGlobalBounds()) && wolf.currentHealth > 0 && player.row != 2)
		{
			player.currentHealth -=1;
			//player.mainCharacter.setPosition(player.mainCharacter.getPosition().x-50, player.mainCharacter.getPosition().y);
			std::cout << "Player health: " << player.currentHealth << " COLLISION" << std::endl;
		}
		else if(player.mainCharacter.getGlobalBounds().intersects(wolf.wolf.getGlobalBounds()) && player.row == 2)
		{
			wolf.currentHealth -=1;
			//remove if you remove swords from the game
		}

		if(weaponActive && player.powerUp == 2 && !canShoot)
		{
			fireBall.setPosition(fireBallLocation.x,fireBallLocation.y);
			window.draw(fireBall);
			if(player.faceRight == true && canShootRight == true && canShootLeft == false)
			{
				if(animationClock.getElapsedTime().asSeconds() > animationDelay)
				{
					fireBallLocation.x = fireBallLocation.x + 50;
					animationClock.restart();
				}
				if(fireBallLocation.x > player.mainCharacter.getPosition().x +400)
				{
					canShoot = true; //If the fireBall has travelled the distance the player can fire again
					player.notShooting = true; //If the fireBall has travelled the distance the player can change direction
					cout << player.faceRight << " / " << "Active" << endl;
				}
			}
			else if(player.faceRight == false && canShootRight == false && canShootLeft == true)
			{
				if(animationClock.getElapsedTime().asSeconds() > animationDelay)
				{
					fireBallLocation.x = fireBallLocation.x - 50;
					animationClock.restart();
				}
				if(fireBallLocation.x < player.mainCharacter.getPosition().x -400 && player.faceRight == false)
				{
					cout << player.faceRight << " / " << "False" << endl;
					canShoot = true; //If the fireBall has travelled the distance the player can fire again
					player.notShooting = true;; //If the fireBall has travelled the distance the player can change direction
				}
			}			
			if(fireBall.getGlobalBounds().intersects(wolf.wolf.getGlobalBounds()) && wolf.currentHealth > 0)
			{
				canShoot = true;
				player.notShooting = true; //if contact with the enemy npc is made, the player can change direction
				wolf.currentHealth -=1;
				fireBall.setPosition(player.mainCharacter.getPosition());
				cout << wolf.currentHealth << endl;
			}
		}

		if (weaponActive && player.powerUp == 3 && !canShoot)
		{
			arrow.setPosition(arrowLocation.x,arrowLocation.y);
			window.draw(arrow);
			if(player.faceRight == true && canShootRight == true && canShootLeft == false)
			{
				if (animationClock.getElapsedTime().asSeconds() > animationDelay)
				{
					arrowLocation.x = arrowLocation.x + 50;
					animationClock.restart();
				}
				if (arrowLocation.x > player.mainCharacter.getPosition().x +400)
				{
					canShoot = true;
					player.notShooting = true;
				}
			}
			else if(player.faceRight == false && canShootRight == false && canShootLeft == true)
			{
				cout << "2" << endl;
				if (animationClock.getElapsedTime().asSeconds() > animationDelay)
				{
					arrowLocation.x = arrowLocation.x - 50;
					animationClock.restart();
					cout << "3" << endl;
				}
				if (arrowLocation.x < player.mainCharacter.getPosition().x -400 && player.faceRight == false)
				{
					canShoot = true;
					player.notShooting = true;
					cout << "4" << endl;
				}
			}
			if (arrow.getGlobalBounds().intersects(wolf.wolf.getGlobalBounds()) && wolf.currentHealth > 0)
			{
				canShoot = true;
				player.notShooting = true;
				wolf.currentHealth -=1;
				arrow.setPosition(player.mainCharacter.getPosition());
				cout << wolf.currentHealth << endl;
			}
		}
	
		player.Update(deltaTime, &playerTexture, sf::Vector2u(6,5), 0.3f, 200.0f);
		player.View(window);
		window.draw(healthPotion);
		window.draw(chest);
		window.draw(swordPowerUp);
		window.draw(spellPowerUp);
		window.draw(bowPowerUp);
		window.draw(health);
		wolf.Draw(window);
		wolf.Spawner(clock, window);
		player.Draw(window);

	
		//cout << canShoot << endl;
	}
	else if (CURRENT_SCREEN == GAME_OVER_SCREEN)
	{
		//window.draw(GameOverMenu);
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			CURRENT_SCREEN = LEVEL_1_SCREEN;
		}
	}
		window.display();
	}
	return 0;
}
