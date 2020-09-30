#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <stdlib.h>
sf::RenderWindow window;
sf::Texture backgroundtexture;
sf::Sprite background;
void delay(int number_of_seconds)
{
	// Converting time into milli_seconds 
	int milli_seconds = number_of_seconds;

	// Storing start time 
	clock_t start_time = clock();

	// looping till required time is not achieved 
	while (clock() < start_time + milli_seconds)
		;
}

int main() {
	//window

	sf::RenderWindow window(sf::VideoMode(1240, 720), "Game");
	printf("Opening window . . .\n");

	//-------------------------------------background-------------------------------------------//

	backgroundtexture.loadFromFile("Background.png");
	sf::Sprite background(backgroundtexture);
	background.setScale(0.6f, 0.5f);
	
	//--------------------------------------player & texture----------------------------------------//
	
	sf::Texture playerTexture;
	playerTexture.loadFromFile("player texture the real one for sure dont need to fix anynmore.png");
	printf("Loading. . .\n");
	if (!playerTexture.loadFromFile("player texture the real one for sure dont need to fix anynmore.png")) {
		printf("Loading. . .\n");
	}
	else {
		printf("Loading Player Done!\n");
	}
	sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
	player.setTexture(&playerTexture);
	sf::Vector2u textureSize = playerTexture.getSize();
	int playerSizeX = textureSize.x / 13;
	int playerSizeY = textureSize.y / 21;
	player.setTextureRect(sf::IntRect(playerSizeX* 2, playerSizeY * 2, playerSizeX, playerSizeY));
	int animationFrame = 0,skillFrame = 0;
	bool spaceCheck = false;

	//---------------------------------------level 1----------------------------------------------//

	bool lv1 = true;
	
	//Wall1//

	sf::Texture wall1_tx;
	wall1_tx.loadFromFile("wall01.png");
	if (!wall1_tx.loadFromFile("wall01.jpg")){
		printf("Loading. . .\n");
	}
	else {
		printf("Loading wall 01 done!\n");
	}
	sf::RectangleShape wall1(sf::Vector2f(600,150));
	wall1.setPosition(0, 310);
	wall1.setTexture(&wall1_tx);

	//wall2//

	sf::Texture wall2_tx;
	wall2_tx.loadFromFile("wall02.jpg");
	if (!wall2_tx.loadFromFile("wall02.jpg")) {
		printf("Loading. . .\n");
	}
	else {
		printf("Loading wall 02 done!\n");
	}
	sf::RectangleShape wall2(sf::Vector2f(400, 150));
	wall2.setPosition(900, 310);
	wall2.setTexture(&wall2_tx);
	
	//wall3//

	sf::RectangleShape wall3(sf::Vector2f(100, 400));
	wall3.setPosition(700, 500);
	wall3.setFillColor(sf::Color(0, 0, 0));

	//wall4//

	sf::Texture wall4_tx;
	wall4_tx.loadFromFile("wall04.jpg");
	if (!wall4_tx.loadFromFile("wall04.jpg")) {
		printf("loading. . .\n");
	}
	else {
		printf("Loading wall04 done!\n");
	}
	sf::RectangleShape wall4(sf::Vector2f(100, 200));
	wall4.setTexture(&wall4_tx);
	wall4.setPosition(800, 0);

	//wall5//

	sf::Texture wall5_tx;
	wall4_tx.loadFromFile("wall05.jpg");
	if (!wall5_tx.loadFromFile("wall05.jpg")) {
		printf("loading. . .\n");
	}
	else {
		printf("Loading wall04 done!\n");
	}
	sf::RectangleShape wall5(sf::Vector2f(100, 200));
	wall5.setTexture(&wall5_tx);
	wall5.setPosition(200, 0);


	//Enemy01//

	sf::Texture enemy01_tx;
	enemy01_tx.loadFromFile("Enemy.png");
	if (!enemy01_tx.loadFromFile("Enemy.png")) {
		printf("Loading. . .\n");
	}
	else {
		printf("Loading Enemy01 Done!\n");
	}
	sf::RectangleShape enemy01(sf::Vector2f(100.0f, 100.0f));
	enemy01.setTexture(&enemy01_tx);
	sf::Vector2u enemy01TextureSize = enemy01_tx.getSize();
	int enemy01SizeX = enemy01TextureSize.x / 13;
	int enemy01SizeY = enemy01TextureSize.y / 21;
	enemy01.setTextureRect(sf::IntRect(enemy01SizeX * 2, enemy01SizeY * 2, enemy01SizeX, enemy01SizeY));
	enemy01.setPosition(1000, 200);
	int  enemyMaxX = 0;
	float enemyPosX = 0, enemy01FrameX = 0, enemy01FrameY = 9;

	//Enemy02//

	sf::Texture enemy02_tx;
	enemy02_tx.loadFromFile("Enemy2.png");
	if (!enemy02_tx.loadFromFile("Enemy2.png")) {
		printf("Loading. . .\n");
	}
	else {
		printf("Loading Enemy02 Done!\n");
	}
	sf::RectangleShape enemy02(sf::Vector2f(100.0f, 100.0f));
	enemy02.setTexture(&enemy02_tx);
	sf::Vector2u enemy02TextureSize = enemy02_tx.getSize();
	int enemy02SizeX = enemy02TextureSize.x / 13;
	int enemy02SizeY = enemy02TextureSize.y / 21;
	enemy02.setTextureRect(sf::IntRect(enemy02SizeX * 2, enemy02SizeY * 2, enemy02SizeX, enemy02SizeY));
	enemy02.setPosition(900, 600);
	int  enemy02MaxY = 0;
	float enemy02PosY = 0, enemy02FrameX = 0, enemy02FrameY = 8;
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (lv1 == true) {
			player.setPosition(20, 600);
			lv1 = false;
		}

		// ---------------------------------KeyboardInput------------------------------------// 

		player.setTextureRect(sf::IntRect(playerSizeX * 0, playerSizeY * 2, playerSizeX, playerSizeY));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player.move(4.5f, 0.0f);
			player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 11, playerSizeX, playerSizeY));
			printf("Keypress : D\n");

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player.move(-4.5f, 0.0f);
			player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 9, playerSizeX, playerSizeY));
			printf("Keypress : A\n");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player.move(0.0f, -4.5f);
			player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 8, playerSizeX, playerSizeY));
			printf("Keypress : W\n");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player.move(0.0f, 4.5f);
			player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 10, playerSizeX, playerSizeY));
			printf("Keypress : S\n");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			spaceCheck = true;
			printf("Keypress : Space\n");
		}
		if (spaceCheck == true) {
			skillFrame++;
			player.setTextureRect(sf::IntRect(playerSizeX * skillFrame, playerSizeY * 2, playerSizeX, playerSizeY));
			delay(100);
			if (skillFrame >= 6) {
				skillFrame = 0;
				spaceCheck = false;
				continue;
			}
		}
		else {
			animationFrame++;
			delay(45);
			if (animationFrame >= 9) {
				animationFrame = 0;
			}
		}
		//--------------------------------------enemy01 move------------------------------------------//

		enemy01.move(enemyPosX, 0.0f);
		enemy01.setTextureRect(sf::IntRect(enemy01SizeX * enemy01FrameX, enemy01SizeY * enemy01FrameY, enemy01SizeX, enemy01SizeY));
		enemy01FrameX++;
		if (enemy01FrameX >= 9) {
			enemy01FrameX = 0;
		}

		//Check Enemy 01 Position//

		if (enemyMaxX < 100) {
			enemyPosX = -4.5;
			enemyMaxX++;
		}
		else if (enemyMaxX >= 100 && enemyMaxX < 200) {
			enemy01FrameY = 11;
			enemyPosX = 4.5;
			enemyMaxX++;
		}
		else {
			enemyMaxX = 0;
			enemyPosX = 0;
			enemy01FrameY = 9;
		}

		//--------------------------------------enemy02 move------------------------------------------//

		enemy02.move(0.0f, enemy02PosY);
		enemy02.setTextureRect(sf::IntRect(enemy02SizeX * enemy02FrameX, enemy02SizeY * enemy02FrameY, enemy02SizeX, enemy02SizeY));
		enemy02FrameX++;
		if (enemy02FrameX >= 9) {
			enemy02FrameX = 0;
		}

		//Check Enemy 02 Position//

		if (enemy02MaxY < 50) {
			enemy02PosY = -4.5;
			enemy02MaxY++;
		}
		else if (enemy02MaxY >= 50 && enemy02MaxY < 100) {
			enemy02FrameY = 10;
			enemy02PosY = 4.5;
			enemy02MaxY++;
		}
		else {
			enemy02MaxY = 0;
			enemy02PosY = 0;
			enemy02FrameY = 8;
		}

		window.clear();
		window.draw(background);
		window.draw(wall1);
		window.draw(wall2);
		window.draw(player);
		window.draw(wall3);
		window.draw(wall4);
		window.draw(wall5);
		window.draw(enemy01);
		window.draw(enemy02);
		
		window.display();
	}
}