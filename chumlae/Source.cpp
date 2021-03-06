﻿/*
background
wall top
player & texture
Level 1
Level 2
Level 3
Level 4
LOOP Zone
*/
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <stdlib.h>
#include<SFML/Audio.hpp>
#include<cstring>
#include<iostream>
#include <fstream>
#include <algorithm>
#include <vector>


std::vector<std::pair<std::string, float>> vec;
bool sortbysecdesc(const std::pair<std::string, float>& a, const std::pair<std::string, float>& b)
{
	return a.second < b.second;
}

void delay(int number_of_seconds)
{
	// Converting time into milli_seconds 
	int milli_seconds = number_of_seconds;

	// Storing start time 
	clock_t start_time = clock();

	// looping till required time is not achieved 
	while (clock() < start_time + milli_seconds);
}

int main() {
	//for Random//
	int num = 0;
	int StageCount = 0;
	int Stage[5] = { 0,0,0,0,0 };
	int n = 0;
	bool lv1ch = true;
	//window
	sf::RenderWindow window(sf::VideoMode(1240, 720), "Game");
	printf("Opening window . . .\n");

	//-------------------------------------background-------------------------------------------//
	
	sf::Texture backgroundtexture;
	backgroundtexture.loadFromFile("Background.png");
	sf::Sprite background(backgroundtexture);
	background.setScale(0.6f, 0.5f);

	//-------------------------------------Wall top-------------------------------------------//

	sf::Texture walltop_tx;
	walltop_tx.loadFromFile("walltop.jpg");
	sf::RectangleShape walltop(sf::Vector2f(1240, 100));
	walltop.setPosition(0, 0);
	walltop.setTexture(&walltop_tx);
	sf::Vector2f walltopPos = walltop.getPosition();

	//--------------------------------------player & texture----------------------------------------//

	sf::Texture fade_tx;
	fade_tx.loadFromFile("fade.png");
	sf::RectangleShape fade(sf::Vector2f(3500.0f, 3500.0f));
	fade.setTexture(&fade_tx);
	float fadeScaleTime = 1;
	sf::Vector2f fadeScale = fade.getScale();
	fade.setOrigin(1700, 1700);


	sf::Texture playerShadow_tx;
	playerShadow_tx.loadFromFile("shadow.png");
	sf::RectangleShape playerShadow(sf::Vector2f(120.0f, 110.0f));
	playerShadow.setOrigin(10, 0);
	playerShadow.setTexture(&playerShadow_tx);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("player texture the real one for sure dont need to fix anynmore.png");
	sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
	player.setTexture(&playerTexture);
	sf::Vector2u textureSize = playerTexture.getSize();
	int playerSizeX = textureSize.x / 13;
	int playerSizeY = textureSize.y / 21;
	player.setTextureRect(sf::IntRect(playerSizeX * 2, playerSizeY * 2, playerSizeX, playerSizeY));
	int animationFrame = 0, skillFrame = 0;
	bool spaceCheck = false;
	int spaceEnable = 0;
	bool KeyW = false, KeyA = false, KeyS = false, KeyD = false;
	int playerLife = 3;
	player.setTextureRect(sf::IntRect(playerSizeX * 0, playerSizeY * 2, playerSizeX, playerSizeY));
	//player.setOrigin(50, 50);

	//playerHitBox//
	sf::RectangleShape playerHitbox(sf::Vector2f(50.0f, 80.0f));
	
	//Player > > Bullet//

	//BullKeyState//

	int bullW[3] = { 0,0,0 }, bullA[3] = { 0,0,0 }, bullS[3] = { 0,0,0 }, bullD[3] = { 0,0,0 };
	int  bulletNo[3] = { 0, 0, 0 }, bullOrder = 0;
	bool bull1State = false, bull2State = false, bull3State = false;
	int bulletTimeOut[3] = { 0,0,0 };

	//Bullet > > 1//

	sf::Texture bullet1_tx;
	bullet1_tx.loadFromFile("bullet.png");
	sf::RectangleShape bullet1(sf::Vector2f(20.0f, 20.0f));
	bullet1.setTexture(&bullet1_tx);
	bullet1.setOrigin(15, 15);
	bool bull1out = false, bull1Col = false;
	float spBull1X = 0, spBull1Y = 0;

	//Bullet > > 2//
	
	sf::Texture bullet2_tx;
	bullet2_tx.loadFromFile("bullet2.png");
	sf::RectangleShape bullet2(sf::Vector2f(20.0f, 20.0f));
	bullet2.setTexture(&bullet2_tx);
	bullet2.setOrigin(15, 15);
	bool bull2out = false, bull2Col = false;
	float spBull2X = 0, spBull2Y = 0;

	//Bullet > > 3//

	sf::Texture bullet3_tx;
	bullet3_tx.loadFromFile("bullet3.png");
	sf::RectangleShape bullet3(sf::Vector2f(20.0f, 20.0f));
	bullet3.setTexture(&bullet3_tx);
	bullet3.setOrigin(15, 15);
	bool bull3out = false, bull3Col = false;
	float spBull3X = 0, spBull3Y = 0;


	//---------------------------------------level 1----------------------------------------------//

	//**********wall1**********//

	sf::Texture wall1_tx;
	wall1_tx.loadFromFile("wall01.jpg");
	sf::RectangleShape wall1(sf::Vector2f(600,150));
	wall1.setPosition(0, 310);
	wall1.setTexture(&wall1_tx);
	sf::Vector2f wall1Pos = wall1.getPosition();
	sf::RectangleShape wall1forbull(sf::Vector2f(600, 50));
	wall1forbull.setPosition(wall1Pos);

	//**********wall2**********//

	sf::Texture wall2_tx;
	wall2_tx.loadFromFile("wall02.jpg");
	sf::RectangleShape wall2(sf::Vector2f(400, 150));
	wall2.setPosition(900, 310);
	wall2.setTexture(&wall2_tx);
	sf::Vector2f wall2Pos = wall2.getPosition();
	sf::RectangleShape wall2forbull(sf::Vector2f(400, 50));
	wall2forbull.setPosition(wall2Pos);
	
	//**********wall3**********//

	sf::RectangleShape wall3(sf::Vector2f(100, 400));
	wall3.setPosition(700, 500);
	wall3.setFillColor(sf::Color(0, 0, 0));
	sf::Vector2f wall3Pos = wall3.getPosition();
	sf::RectangleShape wall3forbull(sf::Vector2f(100, 350));
	wall3forbull.setPosition(wall3Pos);

	//**********wall4**********//

	sf::Texture wall4_tx;
	wall4_tx.loadFromFile("wall04.jpg");
	sf::RectangleShape wall4(sf::Vector2f(100, 200));
	wall4.setTexture(&wall4_tx);
	wall4.setPosition(800, 0);
	sf::Vector2f wall4Pos = wall4.getPosition();
	sf::RectangleShape wall4forbull(sf::Vector2f(100, 150));
	wall4forbull.setPosition(wall4Pos);

	//**********wall5**********//

	sf::Texture wall5_tx;
	wall5_tx.loadFromFile("wall05.jpg");
	sf::RectangleShape wall5(sf::Vector2f(100, 200));
	wall5.setTexture(&wall5_tx);
	wall5.setPosition(200, 0);
	sf::Vector2f wall5Pos = wall5.getPosition();
	sf::RectangleShape wall5forbull(sf::Vector2f(100, 150));
	wall5forbull.setPosition(wall5Pos);


	//**********Enemy01**********//

	sf::Texture enemy01_tx;
	enemy01_tx.loadFromFile("Enemy.png");
	sf::RectangleShape enemy01(sf::Vector2f(100.0f, 100.0f));
	enemy01.setTexture(&enemy01_tx);
	sf::Vector2u enemy01TextureSize = enemy01_tx.getSize();
	int enemy01SizeX = enemy01TextureSize.x / 13;
	int enemy01SizeY = enemy01TextureSize.y / 21;
	enemy01.setTextureRect(sf::IntRect(enemy01SizeX * 2, enemy01SizeY * 2, enemy01SizeX, enemy01SizeY));
	enemy01.setPosition(1000, 200);
	sf::Vector2f enemyLV101Position = enemy01.getPosition();
	int  enemyMaxX = 0;
	float enemyPosX = 0, enemy01FrameX = 0, enemy01FrameY = 9;
	bool enemy1SetState = true;
	int enemy1Life = 3;
	
	sf::Texture enemy01Heart1_tx;
	enemy01Heart1_tx.loadFromFile("EnemyHeart1.png");
	sf::RectangleShape enemy01Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy01Heart1.setOrigin(10, 10);
	enemy01Heart1.setTexture(&enemy01Heart1_tx);
	sf::RectangleShape enemy01Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy01Heart2.setOrigin(10, 10);
	enemy01Heart2.setTexture(&enemy01Heart1_tx);
	sf::RectangleShape enemy01Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy01Heart3.setOrigin(10, 10);
	enemy01Heart3.setTexture(&enemy01Heart1_tx);
	

	//**********Enemy02**********//

	sf::Texture enemy02_tx;
	enemy02_tx.loadFromFile("Enemy2.png");
	sf::RectangleShape enemy02(sf::Vector2f(100.0f, 100.0f));
	enemy02.setTexture(&enemy02_tx);
	sf::Vector2u enemy02TextureSize = enemy02_tx.getSize();
	int enemy02SizeX = enemy02TextureSize.x / 13;
	int enemy02SizeY = enemy02TextureSize.y / 21;
	enemy02.setTextureRect(sf::IntRect(enemy02SizeX * 2, enemy02SizeY * 2, enemy02SizeX, enemy02SizeY));
	enemy02.setPosition(900, 600);
	int  enemy02MaxY = 0;
	float enemy02PosY = 0, enemy02FrameX = 0, enemy02FrameY = 8;
	bool enemy2SetState = true;
	int enemy2Life = 3;
	
	sf::RectangleShape enemy02Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy02Heart1.setOrigin(10, 10);
	enemy02Heart1.setTexture(&enemy01Heart1_tx);
	sf::RectangleShape enemy02Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy02Heart2.setOrigin(10, 10);
	enemy02Heart2.setTexture(&enemy01Heart1_tx);
	sf::RectangleShape enemy02Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy02Heart3.setOrigin(10, 10);
	enemy02Heart3.setTexture(&enemy01Heart1_tx);

	


	//**********Democrac Level 1**********//

	sf::Texture democrac_tx;
	democrac_tx.loadFromFile("Democrac 1.png");
	sf::Texture DemocracLV1_tx;
	sf::RectangleShape DemocracLV1(sf::Vector2f(80.0f, 80.0f));
	DemocracLV1.setTexture(&democrac_tx);
	sf::Vector2u DemocracLV1TextureSize = democrac_tx.getSize();
	int democracSizeX = DemocracLV1TextureSize.x / 6;
	int democracSizeY = DemocracLV1TextureSize.y / 1;
	DemocracLV1.setTextureRect(sf::IntRect(democracSizeX * 0, democracSizeY * 0, democracSizeX, democracSizeY));
	DemocracLV1.setPosition(50, 150);
	float animateDemocracFrame = 0;

	//**********Door Level 1**********//
	
	sf::RectangleShape DoorLV1(sf::Vector2f(50.0f, 200.0f));
	DoorLV1.setPosition(225, 125);
	DoorLV1.setFillColor(sf::Color(0, 0, 0));
	sf::Vector2f DoorLV1Pos = DoorLV1.getPosition();
	bool DoorLV1Check = false;

	//**********Key Level 1**********//

	sf::Texture KeyLV1_tx;
	KeyLV1_tx.loadFromFile("Key LV1.png");
	sf::RectangleShape KeyLV1(sf::Vector2f(50.0f, 50.0f));
	KeyLV1.setTexture(&KeyLV1_tx);
	sf::Vector2u KeyLV1TextureSize = KeyLV1_tx.getSize();
	int KeyLV1SizeX = KeyLV1TextureSize.x / 14;
	int KeyLV1SizeY = KeyLV1TextureSize.y / 1;
	KeyLV1.setTextureRect(sf::IntRect(KeyLV1SizeX * 0, KeyLV1SizeY * 0, KeyLV1SizeX, KeyLV1SizeY));
	KeyLV1.setPosition(1100, 150);
	KeyLV1.setOrigin(25, 25);
	bool KeyLV1Check = false;
	float animateKeyLV1Frame = 0;

	//**********Shield Level 1**********//

	sf::Texture shield_tx;
	shield_tx.loadFromFile("SHIELD.png");
	sf::RectangleShape shield(sf::Vector2f(70.0f, 70.0f));
	shield.setTexture(&shield_tx);
	sf::Vector2u shieldTextureSize = shield_tx.getSize();
	int shieldSizeX = shieldTextureSize.x / 16;
	int shieldSizeY = shieldTextureSize.y / 1;
	shield.setTextureRect(sf::IntRect(shieldSizeX * 0, shieldSizeY * 0, shieldSizeX, shieldSizeY));
	shield.setPosition(1100, 600);
	int shieldAnimateFrame = 0;
	bool shieldCheck = false;

	//---------------------------------------level 2----------------------------------------------//




	//**********Stage1**********//

	//**********wall1**********//

	sf::Texture wallLV201_tx;
	wallLV201_tx.loadFromFile("wallLV201.jpg");
	sf::RectangleShape wallLV201(sf::Vector2f(1000, 150));
	wallLV201.setPosition(0, 400);
	wallLV201.setTexture(&wallLV201_tx);
	sf::Vector2f wallLV201Pos = wallLV201.getPosition();
	sf::RectangleShape wallLV201forbull(sf::Vector2f(1000, 50));
	wallLV201forbull.setPosition(wallLV201Pos);


	//**********wall2**********//

	sf::Texture wallLV202_tx;
	wallLV202_tx.loadFromFile("wallLV202.jpg");
	sf::RectangleShape wallLV202(sf::Vector2f(1000, 150));
	wallLV202.setPosition(240, 150);
	wallLV202.setTexture(&wallLV202_tx);
	sf::Vector2f wallLV202Pos = wallLV202.getPosition();
	sf::RectangleShape wallLV202forbull(sf::Vector2f(1000, 50));
	wallLV202forbull.setPosition(wallLV202Pos);

	//**********wall3**********//

	sf::RectangleShape wallLV203(sf::Vector2f(100, 400));
	wallLV203.setPosition(400, 600);
	wallLV203.setFillColor(sf::Color(0, 0, 0));
	sf::Vector2f wallLV203Pos = wallLV203.getPosition();

	//**********Enemy01**********//

	sf::Texture enemyLV201_tx;
	enemyLV201_tx.loadFromFile("EnemyLV201.png");
	sf::RectangleShape enemyLV201(sf::Vector2f(100.0f, 100.0f));
	enemyLV201.setTexture(&enemyLV201_tx);
	sf::Vector2u enemyLV201TextureSize = enemyLV201_tx.getSize();
	int enemyLV201SizeX = enemyLV201TextureSize.x / 13;
	int enemyLV201SizeY = enemyLV201TextureSize.y / 21;
	enemyLV201.setTextureRect(sf::IntRect(enemyLV201SizeX * 2, enemyLV201SizeY * 2, enemyLV201SizeX, enemyLV201SizeY));
	enemyLV201.setPosition(1000, 600);
	int  enemyLV201MaxX = 0;
	float enemyLV201PosX = 0, enemyLV201FrameX = 0, enemyLV201FrameY = 9;
	bool enemyLV201SetState = true;
	int enemyLV201Life = 3;

	sf::Texture enemyHeart2_tx;
	enemyHeart2_tx.loadFromFile("EnemyHeart2.png");
	sf::RectangleShape enemy201Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy201Heart1.setOrigin(10, 10);
	enemy201Heart1.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy201Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy201Heart2.setOrigin(10, 10);
	enemy201Heart2.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy201Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy201Heart3.setOrigin(10, 10);
	enemy201Heart3.setTexture(&enemyHeart2_tx);

	//**********Enemy02**********//

	sf::Texture enemyLV202_tx;
	enemyLV202_tx.loadFromFile("EnemyLV202.png");
	sf::RectangleShape enemyLV202(sf::Vector2f(100.0f, 100.0f));
	enemyLV202.setTexture(&enemyLV201_tx);
	sf::Vector2u enemyLV202TextureSize = enemyLV202_tx.getSize();
	int enemyLV202SizeX = enemyLV202TextureSize.x / 13;
	int enemyLV202SizeY = enemyLV202TextureSize.y / 21;
	enemyLV202.setTextureRect(sf::IntRect(enemyLV202SizeX * 2, enemyLV202SizeY * 2, enemyLV202SizeX, enemyLV202SizeY));
	enemyLV202.setPosition(1000, 260);
	int  enemyLV202MaxX = 0;
	float enemyLV202PosX = 0, enemyLV202FrameX = 0, enemyLV202FrameY = 9;
	bool enemyLV202SetState = true;
	int enemyLV202Life = 3;

	sf::RectangleShape enemy202Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy202Heart1.setOrigin(10, 10);
	enemy202Heart1.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy202Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy202Heart2.setOrigin(10, 10);
	enemy202Heart2.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy202Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy202Heart3.setOrigin(10, 10);
	enemy202Heart3.setTexture(&enemyHeart2_tx);

	//**********Gate2**********//

	sf::Texture GateLV2_tx;
	GateLV2_tx.loadFromFile("gate.png");
	sf::RectangleShape GateLV2(sf::Vector2f(100.0f, 80.0f));
	GateLV2.setTexture(&GateLV2_tx);
	sf::Vector2u GateLV2TextureSize = GateLV2_tx.getSize();
	int GateLV2SizeX = GateLV2TextureSize.x / 8;
	int GateLV2SizeY = GateLV2TextureSize.y / 1;
	GateLV2.setTextureRect(sf::IntRect(GateLV2SizeX * 0, GateLV2SizeY * 0, GateLV2SizeX, GateLV2SizeY));
	GateLV2.setPosition(1100, 80);
	float animateGateLV2Frame = 0;
	
	//speed item//

	sf::Texture speed_tx;
	speed_tx.loadFromFile("speed.png");
	sf::RectangleShape speed(sf::Vector2f(70.0f, 80.0f));
	speed.setTexture(&speed_tx);
	sf::Vector2u speedTextureSize = speed_tx.getSize();
	int speedSizeX = speedTextureSize.x / 6;
	int speedSizeY = speedTextureSize.y / 1;
	speed.setTextureRect(sf::IntRect(speedSizeX * 0, speedSizeY * 0, speedSizeX, speedSizeY));
	
	speed.setPosition(1100, 600);
	bool speedCheck = false, speedStatus = false;
	int speedTimeCount = 0;
	int speedanimateFrame = 0, speedanimateTimeCount = 0;

	//**********Stage2**********//


	//**********Wall4**********//

	sf::RectangleShape wallLV204(sf::Vector2f(300, 600));
	wallLV204.setPosition(200,300);
	wallLV204.setFillColor(sf::Color(0, 0, 0));
	sf::Vector2f wallLV204Pos = wallLV204.getPosition();


	//**********DoorLV2**********//

	sf::RectangleShape DoorLV2(sf::Vector2f(50, 720));
	DoorLV2.setPosition(900, 0);
	DoorLV2.setFillColor(sf::Color(0, 0, 0));
	sf::Vector2f DoorLV2Pos = DoorLV2.getPosition();
	bool DoorLV2Check = false;

	//**********Enemy03**********//

	sf::Texture enemyLV203_tx;
	enemyLV203_tx.loadFromFile("EnemyLV203.png");
	sf::RectangleShape enemyLV203(sf::Vector2f(100.0f, 100.0f));
	enemyLV203.setTexture(&enemyLV203_tx);
	sf::Vector2u enemyLV203TextureSize = enemyLV203_tx.getSize();
	int enemyLV203SizeX = enemyLV203TextureSize.x / 13;
	int enemyLV203SizeY = enemyLV203TextureSize.y / 21;
	enemyLV203.setTextureRect(sf::IntRect(enemyLV203SizeX * 2, enemyLV203SizeY * 2, enemyLV203SizeX, enemyLV203SizeY));
	enemyLV203.setPosition(1000, 600);
	int  enemyLV203MaxY = 0;
	float enemyLV203PosY = 0, enemyLV203FrameX = 0, enemyLV203FrameY = 8;
	bool enemyLV203SetState = true;
	int enemyLV203Life = 3;
	
	sf::RectangleShape enemy203Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy203Heart1.setOrigin(10, 10);
	enemy203Heart1.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy203Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy203Heart2.setOrigin(10, 10);
	enemy203Heart2.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy203Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy203Heart3.setOrigin(10, 10);
	enemy203Heart3.setTexture(&enemyHeart2_tx);


	//**********Enemy04**********//

	sf::Texture enemyLV204_tx;
	enemyLV204_tx.loadFromFile("EnemyLV204.png");
	sf::RectangleShape enemyLV204(sf::Vector2f(100.0f, 100.0f));
	enemyLV204.setTexture(&enemyLV204_tx);
	sf::Vector2u enemyLV204TextureSize = enemyLV204_tx.getSize();
	int enemyLV204SizeX = enemyLV204TextureSize.x / 13;
	int enemyLV204SizeY = enemyLV204TextureSize.y / 21;
	enemyLV204.setTextureRect(sf::IntRect(enemyLV204SizeX * 2, enemyLV204SizeY * 2, enemyLV204SizeX, enemyLV204SizeY));
	enemyLV204.setPosition(700, 120);
	int  enemyLV204MaxY = 0;
	float enemyLV204PosY = 0, enemyLV204FrameX = 0, enemyLV204FrameY = 8;
	bool enemyLV204SetState = true;
	int enemyLV204Life = 3;

	sf::RectangleShape enemy204Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy204Heart1.setOrigin(10, 10);
	enemy204Heart1.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy204Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy204Heart2.setOrigin(10, 10);
	enemy204Heart2.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy204Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy204Heart3.setOrigin(10, 10);
	enemy204Heart3.setTexture(&enemyHeart2_tx);


	//**********DemocracLevel 2**********//

	sf::Texture DemocracLV2_tx;
	DemocracLV2_tx.loadFromFile("Democrac 2.png");
	sf::RectangleShape DemocracLV2(sf::Vector2f(100.0f, 70.0f));
	DemocracLV2.setTexture(&DemocracLV2_tx);
	sf::Vector2u DemocracLV2TextureSize = DemocracLV2_tx.getSize();
	int democracLV2SizeX = DemocracLV2TextureSize.x / 8;
	int democracLV2SizeY = DemocracLV2TextureSize.y / 1;
	DemocracLV2.setTextureRect(sf::IntRect(democracLV2SizeX * 0, democracLV2SizeY * 0, democracLV2SizeX, democracLV2SizeY));
	DemocracLV2.setPosition(1100, 150);
	float animateDemocracLV2Frame = 0;

	//**********Enemy05**********//

	sf::Texture enemyLV205_tx;
	enemyLV205_tx.loadFromFile("Enemy.png");
	sf::RectangleShape enemyLV205(sf::Vector2f(100.0f, 100.0f));
	enemyLV205.setTexture(&enemyLV205_tx);
	sf::Vector2u enemyLV205TextureSize = enemyLV205_tx.getSize();
	int enemyLV205SizeX = enemyLV205TextureSize.x / 13;
	int enemyLV205SizeY = enemyLV205TextureSize.y / 21;
	enemyLV205.setTextureRect(sf::IntRect(enemyLV205SizeX * 2, enemyLV205SizeY * 2, enemyLV205SizeX, enemyLV205SizeY));
	enemyLV205.setPosition(500, 200);
	sf::Vector2f enemyLV205Position = enemyLV205.getPosition();
	int  enemyLV205MaxX = 0;
	float enemyLV205PosX = 0, enemyLV205FrameX = 0, enemyLV205FrameY = 9;
	bool enemyLV205SetState = true;
	int enemyLV205Life = 3;

	sf::RectangleShape enemy205Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy205Heart1.setOrigin(10, 10);
	enemy205Heart1.setTexture(&enemy01Heart1_tx);
	sf::RectangleShape enemy205Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy205Heart2.setOrigin(10, 10);
	enemy205Heart2.setTexture(&enemy01Heart1_tx);
	sf::RectangleShape enemy205Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy205Heart3.setOrigin(10, 10);
	enemy205Heart3.setTexture(&enemy01Heart1_tx);





	//**********KeyLevel 2**********//
	
	sf::Texture KeyLV2_tx;
	KeyLV2_tx.loadFromFile("Key LV2.png");
	sf::RectangleShape KeyLV2(sf::Vector2f(50.0f, 50.0f));
	KeyLV2.setTexture(&KeyLV2_tx);
	sf::Vector2u KeyLV2TextureSize = KeyLV2_tx.getSize();
	int KeyLV2SizeX = KeyLV2TextureSize.x / 14;
	int KeyLV2SizeY = KeyLV2TextureSize.y / 1;
	KeyLV2.setTextureRect(sf::IntRect(KeyLV2SizeX * 0, KeyLV2SizeY * 0, KeyLV2SizeX, KeyLV2SizeY));
	KeyLV2.setPosition(600, 600);
	bool KeyLV2Check = false;
	KeyLV2.setOrigin(25, 25);
	float animateKeyLV2Frame = 0;
	
	//**************life item**************//

	sf::Texture life_tx;
	life_tx.loadFromFile("Heart 1.png");
	sf::RectangleShape life(sf::Vector2f(70.0f, 70.0f));
	life.setTexture(&life_tx);
	life.setPosition(1100, 600);
	bool lifeCheck = false, lifeStatus = false;
	int lifeAnimateTimeDelay = 0;


	//---------------------------------------level 3----------------------------------------------//



	//**********wall1**********//

	sf::RectangleShape wallLV301(sf::Vector2f(200, 600));
	wallLV301.setPosition(200, 300);
	wallLV301.setFillColor(sf::Color(0, 0, 0));
	sf::Vector2f wallLV301Pos = wallLV301.getPosition();

	//**********wall2**********//

	sf::Texture wallLV302_tx;
	wallLV302_tx.loadFromFile("wallLV302.jpg");
	sf::RectangleShape wallLV302(sf::Vector2f(100, 200));
	wallLV302.setTexture(&wallLV302_tx);
	wallLV302.setPosition(300, 0);
	sf::Vector2f wallLV302Pos = wallLV302.getPosition();
	sf::RectangleShape wallLV302forbull(sf::Vector2f(100, 100));
	wallLV302forbull.setPosition(wallLV302Pos);


	//**********wall3**********//

	sf::Texture wallLV303_tx;
	wallLV303_tx.loadFromFile("wallLV303.jpg");
	sf::RectangleShape wallLV303(sf::Vector2f(500, 150));
	wallLV303.setPosition(400, 300);
	wallLV303.setTexture(&wallLV303_tx);
	sf::Vector2f wallLV303Pos = wallLV303.getPosition();
	sf::RectangleShape wallLV303forbull(sf::Vector2f(500, 25));
	wallLV303forbull.setPosition(wallLV303Pos);

	//**********Enemy01**********//

	sf::Texture enemyLV301_tx;
	enemyLV301_tx.loadFromFile("EnemyLV301.png");
	sf::RectangleShape enemyLV301(sf::Vector2f(100.0f, 100.0f));
	enemyLV301.setTexture(&enemyLV301_tx);
	sf::Vector2u enemyLV301TextureSize = enemyLV301_tx.getSize();
	int enemyLV301SizeX = enemyLV301TextureSize.x / 13;
	int enemyLV301SizeY = enemyLV301TextureSize.y / 21;
	enemyLV301.setTextureRect(sf::IntRect(enemyLV301SizeX * 2, enemyLV301SizeY * 2, enemyLV301SizeX, enemyLV301SizeY));
	enemyLV301.setPosition(500, 200);
	int  enemyLV301MaxX = 0;
	float enemyLV301PosX = 0, enemyLV301FrameX = 0, enemyLV301FrameY = 9;
	bool enemyLV301SetState = true;
	int enemyLV301Life = 3;

	sf::RectangleShape enemy301Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy301Heart1.setOrigin(10, 10);
	enemy301Heart1.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy301Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy301Heart2.setOrigin(10, 10);
	enemy301Heart2.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy301Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy301Heart3.setOrigin(10, 10);
	enemy301Heart3.setTexture(&enemyHeart2_tx);

	//**********Enemy02**********//

	sf::Texture enemyLV302_tx;
	enemyLV302_tx.loadFromFile("EnemyLV302.png");
	sf::RectangleShape enemyLV302(sf::Vector2f(100.0f, 100.0f));
	enemyLV302.setTexture(&enemyLV302_tx);
	sf::Vector2u enemyLV302TextureSize = enemyLV302_tx.getSize();
	int enemyLV302SizeX = enemyLV302TextureSize.x / 13;
	int enemyLV302SizeY = enemyLV302TextureSize.y / 21;
	enemyLV302.setTextureRect(sf::IntRect(enemyLV302SizeX * 2, enemyLV302SizeY * 2, enemyLV302SizeX, enemyLV302SizeY));
	enemyLV302.setPosition(1000, 600);
	int  enemyLV302MaxY = 0;
	float enemyLV302PosY = 0, enemyLV302FrameX = 0, enemyLV302FrameY = 8;
	bool enemyLV302SetState = true;
	int enemyLV302Life = 3;

	sf::RectangleShape enemy302Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy302Heart1.setOrigin(10, 10);
	enemy302Heart1.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy302Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy302Heart2.setOrigin(10, 10);
	enemy302Heart2.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy302Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy302Heart3.setOrigin(10, 10);
	enemy302Heart3.setTexture(&enemyHeart2_tx);


	//**********Enemy03**********//

	sf::Texture enemyLV303_tx;
	enemyLV303_tx.loadFromFile("EnemyLV303.png");
	sf::RectangleShape enemyLV303(sf::Vector2f(100.0f, 100.0f));
	enemyLV303.setTexture(&enemyLV303_tx);
	sf::Vector2u enemyLV303TextureSize = enemyLV303_tx.getSize();
	int enemyLV303SizeX = enemyLV303TextureSize.x / 13;
	int enemyLV303SizeY = enemyLV303TextureSize.y / 21;
	enemyLV303.setTextureRect(sf::IntRect(enemyLV303SizeX * 2, enemyLV303SizeY * 2, enemyLV303SizeX, enemyLV303SizeY));
	enemyLV303.setPosition(700, 600);
	int  enemyLV303MaxY = 0;
	float enemyLV303PosY = 0, enemyLV303FrameX = 0, enemyLV303FrameY = 8;
	bool enemyLV303SetState = true;
	int enemyLV303Life = 3;

	sf::RectangleShape enemy303Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy303Heart1.setOrigin(10, 10);
	enemy303Heart1.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy303Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy303Heart2.setOrigin(10, 10);
	enemy303Heart2.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy303Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy303Heart3.setOrigin(10, 10);
	enemy303Heart3.setTexture(&enemyHeart2_tx);

	//**********Democrac Level 3**********//

	sf::Texture DemocracLV3_tx;
	DemocracLV3_tx.loadFromFile("Democrac 3.png");
	sf::RectangleShape DemocracLV3(sf::Vector2f(120.0f, 80.0f));
	DemocracLV3.setTexture(&DemocracLV3_tx);
	sf::Vector2u DemocracLV3TextureSize = DemocracLV3_tx.getSize();
	int democracLV3SizeX = DemocracLV3TextureSize.x / 6;
	int democracLV3SizeY = DemocracLV3TextureSize.y / 1;
	DemocracLV3.setTextureRect(sf::IntRect(democracLV3SizeX * 0, democracLV3SizeY * 0, democracLV3SizeX, democracLV3SizeY));
	DemocracLV3.setPosition(500, 550);
	float animateDemocracLV3Frame = 0;

	//---------------------------------------level 4----------------------------------------------//

	

	//**********Stage1**********//

	//**********wall1**********//

	sf::Texture wallLV401_tx;
	wallLV401_tx.loadFromFile("wallLV401.jpg");
	sf::RectangleShape wallLV401(sf::Vector2f(900, 150));
	wallLV401.setTexture(&wallLV401_tx);
	wallLV401.setPosition(0, 400);
	sf::Vector2f wallLV401Pos= wallLV401.getPosition();
	
	sf::RectangleShape wallLV401forbull(sf::Vector2f(900, 50));
	wallLV401forbull.setFillColor(sf::Color(0, 0, 0));
	wallLV401forbull.setPosition(wallLV401Pos);
	
	//**********wall2**********//
	 
	sf::Texture wallLV402_tx;
	wallLV402_tx.loadFromFile("wallLV402.jpg");
	sf::RectangleShape wallLV402(sf::Vector2f(100, 200));
	wallLV402.setTexture(&wallLV402_tx);
	wallLV402.setPosition(300, 0);
	sf::Vector2f wallLV402Pos = wallLV402.getPosition();
	sf::RectangleShape wallLV402forbull(sf::Vector2f(100, 100));
	wallLV402forbull.setPosition(wallLV402Pos);

	//**********Enemy01**********//

	sf::Texture enemyLV401_tx;
	enemyLV401_tx.loadFromFile("EnemyLV401.png");
	sf::RectangleShape enemyLV401(sf::Vector2f(100.0f, 100.0f));
	enemyLV401.setTexture(&enemyLV401_tx);
	sf::Vector2u enemyLV401TextureSize = enemyLV401_tx.getSize();
	int enemyLV401SizeX = enemyLV401TextureSize.x / 13;
	int enemyLV401SizeY = enemyLV401TextureSize.y / 21;
	enemyLV401.setTextureRect(sf::IntRect(enemyLV401SizeX * 2, enemyLV401SizeY * 2, enemyLV401SizeX, enemyLV401SizeY));
	enemyLV401.setPosition(1000, 600);
	int  enemyLV401MaxX = 0;
	float enemyLV401PosX = 0, enemyLV401FrameX = 0, enemyLV401FrameY = 9;
	bool enemyLV401SetState = true;
	int enemyLV401Life = 3;

	sf::RectangleShape enemy401Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy401Heart1.setOrigin(10, 10);
	enemy401Heart1.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy401Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy401Heart2.setOrigin(10, 10);
	enemy401Heart2.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy401Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy401Heart3.setOrigin(10, 10);
	enemy401Heart3.setTexture(&enemyHeart2_tx);

	//**********Enemy02**********//

	sf::Texture enemyLV402_tx;
	enemyLV402_tx.loadFromFile("EnemyLV402.png");
	sf::RectangleShape enemyLV402(sf::Vector2f(100.0f, 100.0f));
	enemyLV402.setTexture(&enemyLV402_tx);
	sf::Vector2u enemyLV402TextureSize = enemyLV402_tx.getSize();
	int enemyLV402SizeX = enemyLV402TextureSize.x / 13;
	int enemyLV402SizeY = enemyLV402TextureSize.y / 21;
	enemyLV402.setTextureRect(sf::IntRect(enemyLV402SizeX * 2, enemyLV402SizeY * 2, enemyLV402SizeX, enemyLV402SizeY));
	enemyLV402.setPosition(1000, 450);
	int  enemyLV402MaxY = 0;
	float enemyLV402PosY = 0, enemyLV402FrameX = 0, enemyLV402FrameY = 8;
	bool enemyLV402SetState = true;
	int enemyLV402Life = 3;

	sf::RectangleShape enemy402Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy402Heart1.setOrigin(10, 10);
	enemy402Heart1.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy402Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy402Heart2.setOrigin(10, 10);
	enemy402Heart2.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy402Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy402Heart3.setOrigin(10, 10);
	enemy402Heart3.setTexture(&enemyHeart2_tx);

	//**********Enemy05**********//

	sf::Texture enemyLV405_tx;
	enemyLV405_tx.loadFromFile("Enemy.png");
	sf::RectangleShape enemyLV405(sf::Vector2f(100.0f, 100.0f));
	enemyLV405.setTexture(&enemyLV405_tx);
	sf::Vector2u enemyLV405TextureSize = enemyLV405_tx.getSize();
	int enemyLV405SizeX = enemyLV405TextureSize.x / 13;
	int enemyLV405SizeY = enemyLV405TextureSize.y / 21;
	enemyLV405.setTextureRect(sf::IntRect(enemyLV405SizeX * 2, enemyLV405SizeY * 2, enemyLV405SizeX, enemyLV405SizeY));
	enemyLV405.setPosition(1000, 200);
	sf::Vector2f enemyLV405Position = enemyLV405.getPosition();
	int  enemyLV405MaxX = 0;
	float enemyLV405PosX = 0, enemyLV405FrameX = 0, enemyLV405FrameY = 9;
	bool enemyLV405SetState = true;
	int enemyLV405Life = 3;


	sf::RectangleShape enemy405Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy405Heart1.setOrigin(10, 10);
	enemy405Heart1.setTexture(&enemy01Heart1_tx);
	sf::RectangleShape enemy405Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy405Heart2.setOrigin(10, 10);
	enemy405Heart2.setTexture(&enemy01Heart1_tx);
	sf::RectangleShape enemy405Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy405Heart3.setOrigin(10, 10);
	enemy405Heart3.setTexture(&enemy01Heart1_tx);


	//**********Gate4**********//

	sf::Texture GateLV4_tx;
	GateLV4_tx.loadFromFile("gate4.png");
	sf::RectangleShape GateLV4(sf::Vector2f(100.0f, 80.0f));
	GateLV4.setTexture(&GateLV4_tx);
	sf::Vector2u GateLV4TextureSize = GateLV4_tx.getSize();
	int GateLV4SizeX = GateLV4TextureSize.x / 8;
	int GateLV4SizeY = GateLV4TextureSize.y / 1;
	GateLV4.setTextureRect(sf::IntRect(GateLV4SizeX * 0, GateLV4SizeY * 0, GateLV4SizeX, GateLV4SizeY));
	GateLV4.setPosition(100, 150);
	float animateGateLV4Frame = 0;

	//**********ImortalPotion**********//

	sf::Texture ImorPot_tx;
	ImorPot_tx.loadFromFile("imortalpotion.png");
	sf::RectangleShape ImortalPot(sf::Vector2f(60.0f, 60.0f));
	ImortalPot.setTexture(&ImorPot_tx);
	sf::Vector2u ImortalPotTextureSize = ImorPot_tx.getSize();
	int ImortalSizeX = ImortalPotTextureSize.x / 7;
	int ImortalSizeY = ImortalPotTextureSize.y / 1;
	ImortalPot.setTextureRect(sf::IntRect(ImortalSizeX * 0, ImortalSizeY * 0, ImortalSizeX, ImortalSizeY));
	ImortalPot.setPosition(500, 100);
	float animateImortalFrame = 0;
	int animateImortalTimeCount = 0;
	bool imortalCheck = false;
	int imortalTimeCount = 0;

	//**********Key Level 4**********//

	sf::Texture KeyLV4_tx;
	KeyLV4_tx.loadFromFile("Key LV1.png");
	sf::RectangleShape KeyLV4(sf::Vector2f(50.0f, 50.0f));
	KeyLV4.setTexture(&KeyLV4_tx);
	sf::Vector2u KeyLV4TextureSize = KeyLV4_tx.getSize();
	int KeyLV4SizeX = KeyLV4TextureSize.x / 14;
	int KeyLV4SizeY = KeyLV4TextureSize.y / 1;
	KeyLV4.setTextureRect(sf::IntRect(KeyLV4SizeX * 0, KeyLV4SizeY * 0, KeyLV4SizeX, KeyLV4SizeY));
	KeyLV4.setPosition(1100, 150);
	KeyLV4.setOrigin(25, 25);
	bool KeyLV4Check = false;
	float animateKeyLV4Frame = 0;

	//**********Stage2**********//



	//**********Enemy03**********//

	sf::Texture enemyLV403_tx;
	enemyLV403_tx.loadFromFile("EnemyLV403.png");
	sf::RectangleShape enemyLV403(sf::Vector2f(100.0f, 100.0f));
	enemyLV403.setTexture(&enemyLV403_tx);
	sf::Vector2u enemyLV403TextureSize = enemyLV403_tx.getSize();
	int enemyLV403SizeX = enemyLV403TextureSize.x / 13;
	int enemyLV403SizeY = enemyLV403TextureSize.y / 21;
	enemyLV403.setTextureRect(sf::IntRect(enemyLV403SizeX * 2, enemyLV403SizeY * 2, enemyLV403SizeX, enemyLV403SizeY));
	enemyLV403.setPosition(300, 500);
	int  enemyLV403MaxY = 0;
	float enemyLV403PosY = 0, enemyLV403FrameX = 0, enemyLV403FrameY = 8;
	bool enemyLV403SetState = true;
	int enemyLV403Life = 3;

	sf::RectangleShape enemy403Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy403Heart1.setOrigin(10, 10);
	enemy403Heart1.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy403Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy403Heart2.setOrigin(10, 10);
	enemy403Heart2.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy403Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy403Heart3.setOrigin(10, 10);
	enemy403Heart3.setTexture(&enemyHeart2_tx);


	//**********Enemy04**********//


	sf::Texture enemyLV404_tx;
	enemyLV404_tx.loadFromFile("EnemyLV404.png");
	sf::RectangleShape enemyLV404(sf::Vector2f(100.0f, 100.0f));
	enemyLV404.setTexture(&enemyLV404_tx);
	sf::Vector2u enemyLV404TextureSize = enemyLV404_tx.getSize();
	int enemyLV404SizeX = enemyLV404TextureSize.x / 13;
	int enemyLV404SizeY = enemyLV404TextureSize.y / 21;
	enemyLV404.setTextureRect(sf::IntRect(enemyLV404SizeX * 2, enemyLV404SizeY * 2, enemyLV404SizeX, enemyLV404SizeY));
	enemyLV404.setPosition(600, 100);
	int  enemyLV404MaxY = 0;
	float enemyLV404PosY = 0, enemyLV404FrameX = 0, enemyLV404FrameY = 10;
	bool enemyLV404SetState = true;
	int enemyLV404Life = 3;

	sf::RectangleShape enemy404Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy404Heart1.setOrigin(10, 10);
	enemy404Heart1.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy404Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy404Heart2.setOrigin(10, 10);
	enemy404Heart2.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy404Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy404Heart3.setOrigin(10, 10);
	enemy404Heart3.setTexture(&enemyHeart2_tx);


	//**********Enemy06**********//


	sf::Texture enemyLV406_tx;
	enemyLV406_tx.loadFromFile("EnemyLV404.png");
	sf::RectangleShape enemyLV406(sf::Vector2f(300.0f, 300.0f));
	enemyLV406.setTexture(&enemyLV406_tx);
	sf::Vector2u enemyLV406TextureSize = enemyLV406_tx.getSize();
	int enemyLV406SizeX = enemyLV406TextureSize.x / 13;
	int enemyLV406SizeY = enemyLV406TextureSize.y / 21;
	enemyLV406.setTextureRect(sf::IntRect(enemyLV406SizeX * 2, enemyLV406SizeY * 2, enemyLV406SizeX, enemyLV406SizeY));
	enemyLV406.setPosition(950, 200);
	int  enemyLV406MaxY = 0;
	float enemyLV406PosY = 0, enemyLV406FrameX = 0, enemyLV406FrameY = 10;
	bool enemyLV406SetState = true;
	int enemyLV406Life = 6;
	bool animateBoss = false;

	sf::RectangleShape enemy406Heart1(sf::Vector2f(20.0f, 20.0f));
	enemy406Heart1.setOrigin(10, 10);
	enemy406Heart1.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy406Heart2(sf::Vector2f(20.0f, 20.0f));
	enemy406Heart2.setOrigin(10, 10);
	enemy406Heart2.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy406Heart3(sf::Vector2f(20.0f, 20.0f));
	enemy406Heart3.setOrigin(10, 10);
	enemy406Heart3.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy406Heart4(sf::Vector2f(20.0f, 20.0f));
	enemy406Heart4.setOrigin(10, 10);
	enemy406Heart4.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy406Heart5(sf::Vector2f(20.0f, 20.0f));
	enemy406Heart5.setOrigin(10, 10);
	enemy406Heart5.setTexture(&enemyHeart2_tx);
	sf::RectangleShape enemy406Heart6(sf::Vector2f(20.0f, 20.0f));
	enemy406Heart6.setOrigin(10, 10);
	enemy406Heart6.setTexture(&enemyHeart2_tx);

	//**********Door Level 4**********//

	sf::RectangleShape DoorLV4(sf::Vector2f(50.0f, 300.0f));
	DoorLV4.setPosition(325, 125);
	DoorLV4.setFillColor(sf::Color(0, 0, 0));
	sf::Vector2f DoorLV4Pos = DoorLV4.getPosition();
	bool DoorLV4Check = false;

	//**********Democrac Level 4**********//

	sf::Texture DemocracLV4_tx;
	DemocracLV4_tx.loadFromFile("democrac 4.png");
	sf::RectangleShape DemocracLV4(sf::Vector2f(80.0f, 130.0f));
	DemocracLV4.setTexture(&DemocracLV4_tx);
	sf::Vector2u DemocracLV4TextureSize = DemocracLV4_tx.getSize();
	int democracLV4SizeX = DemocracLV4TextureSize.x / 9;
	int democracLV4SizeY = DemocracLV4TextureSize.y / 1;
	DemocracLV4.setTextureRect(sf::IntRect(democracLV4SizeX * 0, democracLV4SizeY * 0, democracLV4SizeX, democracLV4SizeY));
	DemocracLV4.setPosition(900, 350);
	bool DemocracLv4Col = false;
	float animateDemocracLV4Frame = 0;

	//scanf("%d", &n);

	/*#########################################################################################################

												Heart Status

	###########################################################################################################*/

	int imortalTime = 0;
	//1

	sf::Texture heart1_tx;
	heart1_tx.loadFromFile("Heart 1.png");
	sf::RectangleShape heart1(sf::Vector2f(25.0f, 25.0f));
	heart1.setTexture(&heart1_tx);
	heart1.setPosition(10, 10);
	bool heart1Check = true;

	//2

	sf::Texture heart2_tx;
	heart2_tx.loadFromFile("Heart 2.png");
	sf::RectangleShape heart2(sf::Vector2f(25.0f, 25.0f));
	heart2.setTexture(&heart2_tx);
	heart2.setPosition(50, 10);
	bool heart2Check = true;

	//3

	sf::Texture heart3_tx;
	heart3_tx.loadFromFile("Heart 3.png");
	sf::RectangleShape heart3(sf::Vector2f(25.0f, 25.0f));
	heart3.setTexture(&heart3_tx);
	heart3.setPosition(90, 10);
	bool heart3Check = true;

	/*#########################################################################################################

											Shield Status

	###########################################################################################################*/

	sf::Texture shieldStatus_tx;
	shieldStatus_tx.loadFromFile("ShieldStatus.png");
	sf::RectangleShape shieldStatus(sf::Vector2f(35.0f, 35.0f));
	shieldStatus.setTexture(&shieldStatus_tx);
	shieldStatus.setPosition(150, 5);
	bool shieldStatusCheck = false;
	int shieldLife = 0;


	/*#########################################################################################################

										Imortal Status

	###########################################################################################################*/


	sf::Texture imortalStatus_tx;
	imortalStatus_tx.loadFromFile("imortalStatus.png");
	sf::RectangleShape imortalStatus(sf::Vector2f(35.0f, 40.0f));
	imortalStatus.setTexture(&imortalStatus_tx);
	imortalStatus.setPosition(200, 5);
	bool imortalStatusCheck = false;


	//####################################Timer##############################################//

	bool timerload = false;
	sf::Clock clock;
	sf::Font font;
	sf::Text timerClockMilliSec;
	font.loadFromFile("arial.ttf");
	timerClockMilliSec.setFont(font);
	timerClockMilliSec.setCharacterSize(40);
	timerClockMilliSec.setFillColor(sf::Color::White);
	sf::Text timerClockSec;
	timerClockSec.setFont(font);
	timerClockSec.setCharacterSize(40);
	timerClockSec.setFillColor(sf::Color::White);
	sf::Text time;
	time.setFont(font);
	time.setCharacterSize(40);
	time.setFillColor(sf::Color::White);
	time.setString("Time : ");
	time.setPosition(800, 0);
	sf::Text dot;
	dot.setFont(font);
	dot.setCharacterSize(40);
	dot.setFillColor(sf::Color::White);
	dot.setString(".");
	dot.setPosition(990, 0);
	sf::Text unit;
	unit.setFont(font);
	unit.setCharacterSize(40);
	unit.setFillColor(sf::Color::White);
	unit.setString("sec");
	unit.setPosition(1100, 0);
	int countRound = 0;
	float timeSaver = 0;
	int timeSet = 0;
	float timeShow = 0;
	float timeUse = 0;

	int millisec = 0;
	int sec = 0;

	char millisecShow[100];
	char secShow[100];

	float totalTime = 0;
	/*#########################################################################################################

											Mouse hitbox

	###########################################################################################################*/

	sf::RectangleShape mouseHitBox(sf::Vector2f(10.0f, 10.0f));
	sf::Mouse::setPosition(sf::Vector2i(100, 200), window);
	//sf::Vector2i mousePos = sf::Mouse::getPosition();
	//window.setMouseCursorVisible(false);

	/*#############################################################################################

											ENEMY ATK

	#############################################################################################*/

	//enemy01ATK//

	float spBullE1Y = 0, spBullE1X = 0;
	int enemy01AreaTimeCount = 0;
	bool enemy01AreaCheck = false, AtkE1 = false;
	sf::CircleShape enemy01Area;
	enemy01Area.setRadius(250);
	enemy01Area.setOrigin(225, 175);


	//BulletE1 > > 1//

	sf::Texture bulletE1_tx;
	bulletE1_tx.loadFromFile("bullet.png");
	sf::RectangleShape bulletE1(sf::Vector2f(20.0f, 20.0f));
	bulletE1.setTexture(&bulletE1_tx);
	bulletE1.setOrigin(10, 10);
	bool bullE1out = false, bullE1Col = false, E1GetDes = false;
	int bullE1TimeCount = 0;

	//enemyATK//
	float spBullE2Y = 0, spBullE2X = 0;
	int enemy02AreaTimeCount = 0;
	bool enemy02AreaCheck = false, AtkE2 = false;
	sf::CircleShape enemy02Area;
	enemy02Area.setRadius(250);
	enemy02Area.setOrigin(225, 175);


	//BulletE2 > > 2//

	sf::Texture bulletE2_tx;
	bulletE2_tx.loadFromFile("bullet.png");
	sf::RectangleShape bulletE2(sf::Vector2f(20.0f, 20.0f));
	bulletE2.setTexture(&bulletE2_tx);
	bulletE2.setOrigin(10, 10);
	bool bullE2out = false, bullE2Col = false, E2GetDes = false;
	int bullE2TimeCount = 0;

	//enemyATK//
	float spBullE3Y = 0, spBullE3X = 0;
	int enemy03AreaTimeCount = 0;
	bool enemy03AreaCheck = false, AtkE3 = false;
	sf::CircleShape enemy03Area;
	enemy03Area.setRadius(250);
	enemy03Area.setOrigin(225, 175);


	//BulletE2 > > 3//

	sf::Texture bulletE3_tx;
	bulletE3_tx.loadFromFile("bullet.png");
	sf::RectangleShape bulletE3(sf::Vector2f(20.0f, 20.0f));
	bulletE3.setTexture(&bulletE3_tx);
	bulletE3.setOrigin(10, 10);
	bool bullE3out = false, bullE3Col = false, E3GetDes = false;
	int bullE3TimeCount = 0;

	/*#########################################################################################################

												Enemy Shadow

	###########################################################################################################*/

	sf::Texture EnemyShadow_tx;
	EnemyShadow_tx.loadFromFile("shadow.png");
	sf::RectangleShape Enemy1Shadow(sf::Vector2f(120.0f, 110.0f));
	Enemy1Shadow.setOrigin(10, 0);
	Enemy1Shadow.setTexture(&EnemyShadow_tx);
	sf::RectangleShape Enemy2Shadow(sf::Vector2f(120.0f, 110.0f));
	Enemy2Shadow.setOrigin(10, 0);
	Enemy2Shadow.setTexture(&EnemyShadow_tx);
	sf::RectangleShape Enemy3Shadow(sf::Vector2f(120.0f, 110.0f));
	Enemy3Shadow.setOrigin(10, 0);
	Enemy3Shadow.setTexture(&EnemyShadow_tx);
	sf::Vector2f Shadow3Scale = Enemy3Shadow.getScale();

	/*#########################################################################################################

												Main MENU

	###########################################################################################################*/
	//LOGO//
	sf::Texture Logo1_tx;
	Logo1_tx.loadFromFile("Something.png");
	sf::RectangleShape Logo1(sf::Vector2f(900.0f, 150.0f));
	Logo1.setTexture(&Logo1_tx);
	Logo1.setPosition(300, 80);

	sf::Texture Logo2_tx;
	Logo2_tx.loadFromFile("not found.png");
	sf::RectangleShape Logo2(sf::Vector2f(600.0f, 80.0f));
	Logo2.setTexture(&Logo2_tx);
	Logo2.setPosition(600, 250);
	//Start button//

	sf::Texture Start_tx;
	Start_tx.loadFromFile("Start.png");
	sf::RectangleShape Start(sf::Vector2f(200.0f, 80.0f));
	Start.setTexture(&Start_tx);
	sf::Vector2f StartScale1 = Start.getScale();
	Start.setOrigin(100, 40);
	Start.setPosition(200, 300);
	bool mouseColStart = false;

	//LeaderBoard button//

	sf::Texture LeaderBoard_tx;
	LeaderBoard_tx.loadFromFile("LeaderBoard.png");
	sf::RectangleShape LeaderBoard(sf::Vector2f(400.0f, 80.0f));
	LeaderBoard.setTexture(&LeaderBoard_tx);
	sf::Vector2f LeaderBoardScale = LeaderBoard.getScale();
	LeaderBoard.setOrigin(100, 40);
	LeaderBoard.setPosition(200, 400);
	bool mouseColLeaderboard = false;
	
	//Exit button//

	sf::Texture Exit_tx;
	Exit_tx.loadFromFile("Exit.png");
	sf::RectangleShape Exit(sf::Vector2f(200.0f, 80.0f));
	Exit.setTexture(&Exit_tx);
	sf::Vector2f ExitScale = Exit.getScale();
	Exit.setOrigin(100, 40);
	Exit.setPosition(200, 500);
	bool mouseColExit = false;

	sf::Text EnterNametext("Enter name : ", font, 120);
	EnterNametext.setPosition(400, -600);
	
	/*#########################################################################################################

												Pause Button

	###########################################################################################################*/

	sf::Texture Pause_tx;
	Pause_tx.loadFromFile("pause button.png");
	sf::RectangleShape Pause(sf::Vector2f(25.0f, 25.0f));
	sf::Vector2f PauseScale = Pause.getScale();
	Pause.setTexture(&Pause_tx);
	Pause.setPosition(1210, 30);
	Pause.setOrigin(12, 12);
	bool mouseColPause = false;
	bool pauseStatus = false;

	sf::Texture Resume_tx;
	Resume_tx.loadFromFile("Resume.png");
	sf::RectangleShape Resume(sf::Vector2f(300.0f, 80.0f));
	Resume.setTexture(&Resume_tx);
	sf::Vector2f ResumeScale = Resume.getScale();
	Resume.setOrigin(150, 40);
	Resume.setPosition(620, 300);
	bool mouseColResume = false;

	sf::Texture Mainmenu_tx;
	Mainmenu_tx.loadFromFile("Mainmenu.png");
	sf::RectangleShape Mainmenu(sf::Vector2f(450.0f, 80.0f));
	Mainmenu.setTexture(&Mainmenu_tx);
	sf::Vector2f MainmenuScale = Mainmenu.getScale();
	Mainmenu.setOrigin(225, 40);
	Mainmenu.setPosition(620, 400);
	bool mouseColMainmenu= false;


	sf::Text Name;
	Name.setFont(font);
	Name.setCharacterSize(40);
	Name.setFillColor(sf::Color::White);
	Name.setPosition(390, 250);
	char playername[3];
	Name.setOutlineThickness(1);
	sf::String inputName;
	Name.setString("Enter name : ____ ");

	/*#########################################################################################################

												Sound

	###########################################################################################################*/
	
	sf::SoundBuffer backgroundSoundld;
	backgroundSoundld.loadFromFile("BackgroundSound.ogg");
	sf::Sound backgroundSound;
	backgroundSound.setBuffer(backgroundSoundld);
	backgroundSound.setLoop(true);

	sf::SoundBuffer winSoundld;
	winSoundld.loadFromFile("winsound.ogg");
	sf::Sound winSound;
	winSound.setBuffer(winSoundld);

	sf::SoundBuffer gameoverSoundld;
	gameoverSoundld.loadFromFile("gameoversound.ogg");
	sf::Sound gameoverSound;
	gameoverSound.setBuffer(gameoverSoundld);
	 
	sf::SoundBuffer bossFightSoundld;
	bossFightSoundld.loadFromFile("Bossfight.ogg");
	sf::Sound bossFightSound;
	bossFightSound.setBuffer(bossFightSoundld);

	sf::SoundBuffer shootSoundld;
	shootSoundld.loadFromFile("shoot.ogg");
	sf::Sound shootSound;
	shootSound.setBuffer(shootSoundld);

	/*#########################################################################################################

											gameoverScene

	###########################################################################################################*/

	sf::Texture gameover_tx;
	gameover_tx.loadFromFile("gameover.png");
	sf::RectangleShape gameover(sf::Vector2f(700.0f, 400.0f));
	gameover.setTexture(&gameover_tx);
	gameover.setOrigin(350, 200);
	gameover.setPosition(620, 360);

	sf::Text finalTime;
	finalTime.setFont(font);
	finalTime.setCharacterSize(40);
	finalTime.setFillColor(sf::Color::White);
	finalTime.setString("Final Time : ");
	finalTime.setPosition(700, 0);

	sf::Text finalTimerClockSec;
	finalTimerClockSec.setFont(font);
	finalTimerClockSec.setCharacterSize(40);
	finalTimerClockSec.setFillColor(sf::Color::White);

	sf::Text finalTimerClockMilliSec;
	finalTimerClockMilliSec.setFont(font);
	finalTimerClockMilliSec.setCharacterSize(40);
	finalTimerClockMilliSec.setFillColor(sf::Color::White);

	/*#########################################################################################################

											HIGHSCORE

	###########################################################################################################*/
	bool fileWrite = false;
	char intName[3];
	int NameCount = 0;
	//FILE* highscore;
	//highscore = fopen("Score.txt", "w");

	//fclose(highscore);
	/*ofstream myfile;
	myfile.open("Score.txt");*/

	sf::Text highscoretext("LEADERBOARD", font, 60);
	highscoretext.setOutlineThickness(3);
	highscoretext.setPosition(400, 100);
	sf::Text text[12];
	for (int s = 0; s < 12; s++)
	{
		text[s].setFont(font);
		text[s].setCharacterSize(50);
		text[s].setOutlineThickness(2);
	}
	for (int i = 0; i < 12; i += 2)
	{
		text[i].setPosition(200,200+ i * 30);
		text[i + 1].setPosition(800,200+ i * 30);
	}
	std::string str[12];
	text[0].setString("NAME");
	text[1].setString("TIME(second)");
	text[0].setFillColor(sf::Color(211, 211, 211));
	text[1].setFillColor(sf::Color(211, 211, 211));
	text[0].setPosition(200, 200);
	text[1].setPosition(800, 200);


	/*#########################################################################################################

											ENDINGPART

	###########################################################################################################*/
	

	sf::Texture ending_tx;
	ending_tx.loadFromFile("ending.png");
	sf::RectangleShape ending(sf::Vector2f(350.0f, 300.0f));
	ending.setTexture(&ending_tx);
	ending.setPosition(600, 260);
	ending.setOrigin(150, 150);
	sf::Text endingtx;
	endingtx.setFont(font);
	endingtx.setCharacterSize(40);
	endingtx.setFillColor(sf::Color::White);
	endingtx.setString("NOW YOU HAVE PS5 !");
	endingtx.setPosition(400, 460);
	ending.setOutlineThickness(2);

	/**********************************************************************************************************

	-----------------------------------------------------------------------------------------------------------

	-----------------------------------------> > Loop Zone < <-------------------------------------------------
	
	-----------------------------------------------------------------------------------------------------------

	***********************************************************************************************************/



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (lv1ch == true) {
			player.setPosition(20, 600);
			lv1ch = false;
			KeyLV1Check = false;
		}

		//printf("StageCount = %d\n", StageCount);
		
		if (n == 0) {
			millisec = 0;
			sec = 0;
			
			
		}
		if (pauseStatus == false&&n!=0&&n!=10) {
			if (millisec >= 100) {
				millisec = 0;
				sec += 1;
			}
			millisec += 3;
			//printf("millisec = %d\n", millisec);
			totalTime += 0.03;
			sprintf_s(millisecShow, "%d", millisec);
			sprintf_s(secShow, "%d", sec);
			timerClockMilliSec.setString(millisecShow);
			timerClockMilliSec.setPosition(1005, 0);
			timerClockSec.setString(secShow);
			timerClockSec.setPosition(960, 0);
		}
		if (sec >= 10) {
			timerClockSec.setPosition(940, 0);
		}
		if (sec >= 100) {
			timerClockSec.setPosition(920, 0);
		}

		//##############################################################################################//

		
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		mouseHitBox.setPosition(mousePos.x,mousePos.y);
		sf::Vector2f hitBox = mouseHitBox.getPosition();
		

		//###########################################Pause Button###################################################//
			if (mouseHitBox.getGlobalBounds().intersects(Pause.getGlobalBounds())) {
				mouseColPause = true;
				Pause.setScale(PauseScale.x * 1.2, PauseScale.y * 1.2);
			}
			else {
				mouseColPause = false;
				Pause.setScale(PauseScale.x, PauseScale.y);
			}

			if (pauseStatus == false && n != 0 && mouseColPause == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				countRound = 1;
				pauseStatus = true;
			}

			if (pauseStatus == true && mouseHitBox.getGlobalBounds().intersects(Resume.getGlobalBounds())) {
				mouseColResume = true;
				Resume.setScale(ResumeScale.x * 1.2, ResumeScale.y * 1.2);
			}
			else {
				mouseColResume = false;
				Resume.setScale(ResumeScale.x, ResumeScale.y);
			}
			if (pauseStatus == true && n != 0 && mouseColResume == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				pauseStatus = false;
			}

			if ((pauseStatus == true|| n == 99||n==10|| DemocracLv4Col == true) && mouseHitBox.getGlobalBounds().intersects(Mainmenu.getGlobalBounds())) {
				mouseColMainmenu = true;
				Mainmenu.setScale(MainmenuScale.x * 1.2, MainmenuScale.y * 1.2);
			}
			else {
				mouseColMainmenu = false;
				Mainmenu.setScale(MainmenuScale.x, MainmenuScale.y);
			}
			if ((pauseStatus == true || n == 99) && n != 0 && mouseColMainmenu == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				n = 0;
				pauseStatus = false;
			}

		
		//printf("timeShow = %f\ntimeUse", timeShow);
	if(pauseStatus == false){

		//Set Status//

		if (n == 0) {

			DemocracLV1.setPosition(50, 150);
			DemocracLV2.setPosition(1100, 150);
			DemocracLV3.setPosition(500, 550);
			DemocracLV4.setPosition(900, 350);

			Enemy3Shadow.setScale(Shadow3Scale);
			lifeCheck = false;
			DemocracLv4Col = false;
			bulletE3.setSize(sf::Vector2f(20.0f, 20.0f));
			bulletE3.setOrigin(10, 10);
			inputName.clear();
			totalTime = 0;
			fileWrite == false;
			Start.setPosition(200, 300);
			Mainmenu.setPosition(620, 400);
			backgroundSound.play();
			//backgroundSound.pause();
			num = 0;
			StageCount = 0;
			Stage[0] = 0;
			Stage[1] = 0;
			Stage[2] = 0;
			Stage[3] = 0;
			Stage[4] = 0;
			player.setPosition(20, 600);
			playerLife = 3;

			//LEVEL 1//
			enemy1Life = 3;
			enemy2Life = 3;
			fade.setScale(fadeScale);
			shieldStatusCheck = false;
			shieldCheck = false;
			DoorLV1Check = false;
			KeyLV1Check = false;
			
			//LEVEL 2//
			//stage 1//
			enemyLV201Life = 3;
			enemyLV202Life = 3;
			speedCheck = false;
			speedTimeCount = 0;
			speedStatus = false;
			//stage 2//
			enemyLV203Life = 3;
			enemyLV204Life = 3;
			enemyLV205Life = 3;
			DoorLV2Check = false;
			KeyLV2Check = false;

			//LEVEL 3//
			enemyLV301Life = 3;
			enemyLV302Life = 3;
			enemyLV303Life = 3;

			//LEVEL 4//
			//stage 1//
			enemyLV401Life = 3;
			enemyLV402Life = 3;
			enemyLV405Life = 3;
			imortalCheck = false;
			KeyLV4Check = false;
			//stage 2//
			imortalTimeCount = 0;
			enemyLV403Life = 3;
			enemyLV404Life = 3;
			enemyLV406Life = 6;
			fadeScaleTime = 1;
		}
		if (n == 10 || n == 99) {
			backgroundSound.play ();
		}
		if (n == 1) {
			if (enemy1SetState == true) {
				enemy1Life = 3;
				enemy1SetState = false;
			}
			if (enemy2SetState == true) {
				enemy2Life = 3;
				enemy2SetState = false;
			}
		}
		if (n == 2) {
			if (enemyLV201SetState == true) {
				enemyLV201Life = 3;
				enemyLV201SetState = false;
			}
			if (enemyLV201SetState == true) {
				enemyLV202Life = 3;
				enemyLV202SetState = false;
			}
		}

		/*------------------------------------------------------------------------------------------------------------------------

		-------------------------------------------- //Collision Check Zone// ----------------------------------------------------

		------------------------------------------------------------------------------------------------------------------------*/

		//mouse with botton//
		
		//with Start//
		if (mouseHitBox.getGlobalBounds().intersects(Start.getGlobalBounds())) {
			mouseColStart = true;
			
			Start.setScale(StartScale1.x * 1.2, StartScale1.y * 1.2);
		}
		if (!mouseHitBox.getGlobalBounds().intersects(Start.getGlobalBounds())) {
			mouseColStart = false;
			Start.setScale(StartScale1.x, StartScale1.y);
		}

		//with Leaderboard//
		if (mouseHitBox.getGlobalBounds().intersects(LeaderBoard.getGlobalBounds())) {
			mouseColLeaderboard = true;
			LeaderBoard.setScale(LeaderBoardScale.x * 1.2, LeaderBoardScale.y * 1.2);
		}
		if (!mouseHitBox.getGlobalBounds().intersects(LeaderBoard.getGlobalBounds())) {
			mouseColLeaderboard = false;
			LeaderBoard.setScale(LeaderBoardScale.x, LeaderBoardScale.y);
		}

		//with Exit//
		if (mouseHitBox.getGlobalBounds().intersects(Exit.getGlobalBounds())) {
			mouseColExit = true;
			Exit.setScale(ExitScale.x * 1.2, ExitScale.y * 1.2);
		}
		if (!mouseHitBox.getGlobalBounds().intersects(Exit.getGlobalBounds())) {
			mouseColExit = false;
			Exit.setScale(ExitScale.x, ExitScale.y);
		}

		sf::Vector2f playerPosition = player.getPosition();
		sf::Vector2f enemy01Position = enemy01.getPosition();
		sf::Vector2f enemy02Position = enemy02.getPosition();
		sf::Vector2f enemyLV201Position = enemyLV201.getPosition();
		sf::Vector2f enemyLV202Position = enemyLV202.getPosition();
		sf::Vector2f enemyLV203Position = enemyLV203.getPosition();
		sf::Vector2f enemyLV204Position = enemyLV204.getPosition();
		sf::Vector2f enemyLV205Position = enemyLV205.getPosition();
		sf::Vector2f enemyLV301Position = enemyLV301.getPosition();
		sf::Vector2f enemyLV302Position = enemyLV302.getPosition();
		sf::Vector2f enemyLV303Position = enemyLV303.getPosition();
		sf::Vector2f enemyLV401Position = enemyLV401.getPosition();
		sf::Vector2f enemyLV402Position = enemyLV402.getPosition();
		sf::Vector2f enemyLV403Position = enemyLV403.getPosition();
		sf::Vector2f enemyLV404Position = enemyLV404.getPosition();
		sf::Vector2f enemyLV405Position = enemyLV405.getPosition();
		sf::Vector2f enemyLV406Position = enemyLV406.getPosition();
		sf::Vector2f bull1Pos = bullet1.getPosition();
		sf::Vector2f bull2Pos = bullet2.getPosition();
		sf::Vector2f bull3Pos = bullet3.getPosition();
		sf::Vector2f bullE1Pos = bulletE1.getPosition();
		sf::Vector2f bullE2Pos = bulletE2.getPosition();
		sf::Vector2f bullE3Pos = bulletE3.getPosition();
		bool w = true, a = true, s = true, d = true;
		//fade//
		fade.setPosition(playerPosition);

		//shadow//
		playerShadow.setPosition(playerPosition);
		playerHitbox.setPosition(playerPosition.x+25,playerPosition.y+20);
		if (n == 6) {
			fadeScaleTime += 0.1;
			fade.setScale(fadeScale.x * fadeScaleTime, fadeScale.y * fadeScaleTime);
		}

		if (n == 1) {
			Enemy1Shadow.setPosition(enemy01Position);
			Enemy2Shadow.setPosition(enemy02Position);
		}
		if (n == 2) {
			Enemy1Shadow.setPosition(enemyLV201Position);
			Enemy2Shadow.setPosition(enemyLV202Position);
		}
		if (n == 3) {
			Enemy1Shadow.setPosition(enemyLV203Position);
			Enemy2Shadow.setPosition(enemyLV204Position);
			Enemy3Shadow.setPosition(enemyLV205Position);
		}
		if (n == 4) {
			Enemy1Shadow.setPosition(enemyLV301Position);
			Enemy2Shadow.setPosition(enemyLV302Position);
			Enemy3Shadow.setPosition(enemyLV303Position);
		}
		if (n == 5) {
			Enemy1Shadow.setPosition(enemyLV401Position);
			Enemy2Shadow.setPosition(enemyLV402Position);
			Enemy3Shadow.setPosition(enemyLV405Position);
		}
		if (n == 6) {
			Enemy1Shadow.setPosition(enemyLV403Position);
			Enemy2Shadow.setPosition(enemyLV404Position);
			Enemy3Shadow.setPosition(enemyLV406Position);
		}
		//enemybullet with player//
		if (imortalCheck == false) {
			
			if (bulletE1.getGlobalBounds().intersects(playerHitbox.getGlobalBounds())) {
				printf("hit 1\n");
				bullE1out = false;
				bulletE1.setPosition(0, 0);
				if (shieldStatusCheck == true) {
					shieldLife -= 1;
				}
				if (shieldStatusCheck == false) {
					playerLife -= 1;
				}
				if (shieldLife <= 0) {
					shieldStatusCheck = false;
				}
			}
			if (bulletE2.getGlobalBounds().intersects(playerHitbox.getGlobalBounds())) {
				printf("hit 2\n");
				bullE2out = false;
				bulletE2.setPosition(0, 0);
				if (shieldStatusCheck == true) {
					shieldLife -= 1;
				}
				if (shieldLife <= 0) {
					shieldStatusCheck = false;
					playerLife -= 1;
				}
			}
			if (bulletE3.getGlobalBounds().intersects(playerHitbox.getGlobalBounds())) {
				printf("hit 2\n");
				bullE3out = false;
				bulletE3.setPosition(0, 0);
				if (shieldStatusCheck == true) {
					shieldLife -= 1;
				}
				if (shieldLife <= 0) {
					shieldStatusCheck = false;
					playerLife -= 1;
				}
			}

			if (playerLife <= 0) {
				//printf("GameOver\n");
			}
		}
		if (imortalCheck == true) {
			imortalTimeCount++;
		}
		if (imortalTimeCount > 300) {
			imortalCheck = false;
		}
		
		//collison with edge//


		if (playerPosition.x <= -20) {
			a = false;
		}
		if (playerPosition.x > 1160 || bull1Pos.x > 1160 || bull2Pos.x > 1160 || bull3Pos.x > 1160) {
			d = false;
		}
		if (playerPosition.y >= 620) {
			s = false;
		}

		if (bull1Pos.x <= -20 || bull1Pos.x > 1240 || bull1Pos.y >= 720 || bull1Pos.y < 0) {
			bull1out = false;
			bull1Col = false;
			bullA[0] = 0;
			bullW[0] = 0;
			bullS[0] = 0;
			bullD[0] = 0;
			bulletNo[0] = 0;
			bullet1.setPosition(0, 0);
			bulletTimeOut[0] = 0;
		}

		if (bull2Pos.x <= -20 || bull2Pos.x > 1240 || bull2Pos.y >= 720 || bull2Pos.y < 0) {
			bull2out = false;
			bulletNo[1] = 0;
			bull2Col = false;
			bullA[1] = 0;
			bullW[1] = 0;
			bullS[1] = 0;
			bullD[1] = 0;
			bullet2.setPosition(0, 0);
			bulletTimeOut[1] = 0;
		}

		if (bull3Pos.x <= -20 || bull3Pos.x > 1240 || bull3Pos.y >= 720 || bull3Pos.y < 0) {
			bull3out = false;
			bulletNo[2] = 0;
			bullA[2] = 0;
			bullW[2] = 0;
			bullS[2] = 0;
			bullD[2] = 0;
			bull3Col = false;
			bullet3.setPosition(0, 0);
			bulletTimeOut[2] = 0;
		}
		
		//bulletE1 Level 1
		if (bullE1Pos.x <= -20 || bullE1Pos.x > 1240 || bullE1Pos.y >= 720 || bullE1Pos.y < 0) {
			bullE1out = false;
			bullE1TimeCount = 0;
			bulletE1.setPosition(0, 0);
		}
		if (bullE2Pos.x <= -20 || bullE2Pos.x > 1240 || bullE2Pos.y >= 720 || bullE2Pos.y < 0) {
			bullE2out = false;
			bullE2TimeCount = 0;
			bulletE2.setPosition(0, 0);
		}
		if (bullE3Pos.x <= -20 || bullE3Pos.x > 1240 || bullE3Pos.y >= 720 || bullE3Pos.y < 0) {
			bullE3out = false;
			animateBoss = false;
			bullE3TimeCount = 0;
			bulletE3.setPosition(0, 0);
		}
		//collision with walls check//



		if ((playerPosition.y < walltopPos.y + 20)) {
			w = false;
		}

		//LEVEL 1//

		if (n == 1) {

			//Level1 > > wall1//

			if ((playerPosition.y < wall1Pos.y + 75 && playerPosition.y>wall1Pos.y) && (playerPosition.x < wall1Pos.x + 570)) {
				w = false;
				//printf("w\n");
			}
			if ((playerPosition.y < wall1Pos.y + 40 && playerPosition.y > wall1Pos.y - 80) && (playerPosition.x < wall1Pos.x + 570)) {
				s = false;
				//printf("s\n");
			}
			if ((playerPosition.y<wall1Pos.y + 75 && playerPosition.y > wall1Pos.y - 80) && (playerPosition.x < wall1Pos.x + 580 && playerPosition.x > wall1Pos.x + 570)) {
				a = false;
				//printf("a\n");
			}

			//Level1 > > wall2//

			if ((playerPosition.y < wall2Pos.y + 75 && playerPosition.y > wall2Pos.y) && (playerPosition.x > wall2Pos.x - 70)) {
				w = false;
				//printf("w1\n");
			}
			if ((playerPosition.y < wall2Pos.y + 40 && playerPosition.y > wall2Pos.y - 80) && (playerPosition.x > wall2Pos.x - 70)) {
				s = false;
				//printf("s1\n");
			}
			if ((playerPosition.y<wall2Pos.y + 75 && playerPosition.y > wall2Pos.y - 80) && (playerPosition.x < wall2Pos.x - 70 && playerPosition.x > wall2Pos.x - 80)) {
				d = false;
				//printf("d1\n");
			}

			//Level1 > > wall3//

			if ((playerPosition.y < wall3Pos.y + 40 && playerPosition.y > wall3Pos.y - 80) && (playerPosition.x > wall3Pos.x - 70 && playerPosition.x < wall3Pos.x + 70)) {
				s = false;
				//printf("d2\n");
			}
			if ((playerPosition.y > wall3Pos.y - 80) && (playerPosition.x < wall3Pos.x - 70 && playerPosition.x > wall3Pos.x - 80)) {
				d = false;
				//printf("d2\n");
			}
			if ((playerPosition.y > wall3Pos.y - 80) && (playerPosition.x > wall3Pos.x + 70 && playerPosition.x < wall3Pos.x + 80)) {
				a = false;
				//printf("a2\n");
			}

			//Level1 > > wall4//

			if ((playerPosition.y < wall4Pos.y + 130) && (playerPosition.x > wall4Pos.x - 70 && playerPosition.x < wall4Pos.x + 70)) {
				w = false;
				//printf("w\n");
			}
			if ((playerPosition.y < wall4Pos.y + 130) && (playerPosition.x < wall4Pos.x - 70 && playerPosition.x > wall4Pos.x - 80)) {
				d = false;
				//printf("d\n");
			}
			if ((playerPosition.y < wall4Pos.y + 130) && (playerPosition.x > wall4Pos.x + 70 && playerPosition.x < wall4Pos.x + 80)) {
				a = false;
				//printf("a\n");
			}

			//Level1 > > wall5//

			if ((playerPosition.y < wall5Pos.y + 130) && (playerPosition.x > wall5Pos.x - 70 && playerPosition.x < wall5Pos.x + 70)) {
				w = false;
				//printf("w\n");
			}
			if ((playerPosition.y < wall5Pos.y + 130) && (playerPosition.x < wall5Pos.x - 70 && playerPosition.x > wall5Pos.x - 80)) {
				d = false;
				//printf("d\n");
			}
			if ((playerPosition.y < wall5Pos.y + 130) && (playerPosition.x > wall5Pos.x + 70 && playerPosition.x < wall5Pos.x + 80)) {
				a = false;
				//printf("a\n");
			}

			//Level1 > > Door//

			if (DoorLV1Check == false) {
				if ((playerPosition.y < DoorLV1Pos.y + 150) && (playerPosition.x < DoorLV1Pos.x + 40 && playerPosition.x > DoorLV1Pos.x + 30)) {
					a = false;
					//printf("d2\n");
				}
			}

			//Level1 > > Democrac//

			if (player.getGlobalBounds().intersects(DemocracLV1.getGlobalBounds())) {
				if (StageCount < 5) {
					num = (rand() % (5 - 1 + 1)) + 1;
					while (num == Stage[0] || num == Stage[1] || num == Stage[2] || num == Stage[3] || num == Stage[4]) {
						num = (rand() % (5 - 1 + 1)) + 1;
					}
					Stage[StageCount] = num;
					n = num;
					printf("num %d\n", num);
				}
				else if (StageCount == 5) {
					n = 6;
				}
				StageCount += 1;
					//n = 2;
				player.setPosition(20, 600);
			}

			//Level1 > > Key//

			if (KeyLV1Check == false) {
				if (player.getGlobalBounds().intersects(KeyLV1.getGlobalBounds())) {
					KeyLV1Check = true;
					DoorLV1Check = true;
				}
			}

			//Level1 > > Shield//

			if (shieldStatusCheck == false) {
				if (player.getGlobalBounds().intersects(shield.getGlobalBounds())) {
					shieldStatusCheck = true;
					shieldCheck = true;
					shieldLife += 3;
				}
			}

			//Level1 > > Enemy 1//
			/*if ((playerPosition.y + 100 >= enemyLV101Position.y || playerPosition.y <= enemyLV101Position.y + 100) && (playerPosition.x + 70 >= enemyLV101Position.x + 30 || playerPosition.x + 30 <= enemyLV101Position.y + 70)) {
				//printf("chonlaew");
			}*/

			// bullet collision //

			//bullet 1//

			if ((bullet1.getGlobalBounds().intersects(wall1forbull.getGlobalBounds()))
				|| (bullet1.getGlobalBounds().intersects(wall2forbull.getGlobalBounds()))
				|| (bullet1.getGlobalBounds().intersects(wall3forbull.getGlobalBounds()))
				|| (bullet1.getGlobalBounds().intersects(wall4forbull.getGlobalBounds()))
				|| (bullet1.getGlobalBounds().intersects(wall5forbull.getGlobalBounds()))
				) {
				bull1out = false;
				bull1Col = false;
				bulletNo[0] = 0;
				bulletTimeOut[0] = 0;
				bullet1.setPosition(0, 0);
			}
			if (DoorLV1Check == false) {
				if (bullet1.getGlobalBounds().intersects(DoorLV1.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
				}
			}

			//bullet 2//

			if ((bullet2.getGlobalBounds().intersects(wall1forbull.getGlobalBounds()))
				|| (bullet2.getGlobalBounds().intersects(wall2forbull.getGlobalBounds()))
				|| (bullet2.getGlobalBounds().intersects(wall3forbull.getGlobalBounds()))
				|| (bullet2.getGlobalBounds().intersects(wall4forbull.getGlobalBounds()))
				|| (bullet2.getGlobalBounds().intersects(wall5forbull.getGlobalBounds()))
				) {
				bull2out = false;
				bull2Col = false;
				bulletNo[1] = 0;
				bulletTimeOut[1] = 0;
				bullet2.setPosition(0, 0);
			}
			if (DoorLV1Check == false) {
				if (bullet2.getGlobalBounds().intersects(DoorLV1.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
				}
			}

			//bullet 3//

			if ((bullet3.getGlobalBounds().intersects(wall1forbull.getGlobalBounds()))
				|| (bullet3.getGlobalBounds().intersects(wall2forbull.getGlobalBounds()))
				|| (bullet3.getGlobalBounds().intersects(wall3forbull.getGlobalBounds()))
				|| (bullet3.getGlobalBounds().intersects(wall4forbull.getGlobalBounds()))
				|| (bullet3.getGlobalBounds().intersects(wall5forbull.getGlobalBounds()))
				) {
				bull3out = false;
				bulletNo[2] = 0;
				bull3Col = false;
				bulletTimeOut[2] = 0;
				bullet3.setPosition(0, 0);
			}
			if (DoorLV1Check == false) {
				if (bullet3.getGlobalBounds().intersects(DoorLV1.getGlobalBounds())) {
					bull3out = false;
					bulletNo[2] = 0;
					bull3Col = false;
					bulletTimeOut[1] = 0;
					bullet3.setPosition(0, 0);
				}
			}

			//bullet E1 
			if ((bulletE1.getGlobalBounds().intersects(wall1forbull.getGlobalBounds()))
				|| (bulletE1.getGlobalBounds().intersects(wall2forbull.getGlobalBounds()))
				|| (bulletE1.getGlobalBounds().intersects(wall3forbull.getGlobalBounds()))
				|| (bulletE1.getGlobalBounds().intersects(wall4forbull.getGlobalBounds()))
				|| (bulletE1.getGlobalBounds().intersects(wall5forbull.getGlobalBounds()))
				) {
				bullE1out = false;
				bullE1TimeCount = 0;
				bulletE1.setPosition(enemy01Position);
			}
			if (DoorLV1Check == false) {
				if (bulletE1.getGlobalBounds().intersects(DoorLV1.getGlobalBounds())) {
					bullE1out = false;
					bullE1TimeCount = 0;
					bulletE1.setPosition(enemy01Position);
					//bullet3.setPosition(0, 0);
				}
			}
			//bullet E2
			if ((bulletE2.getGlobalBounds().intersects(wall1forbull.getGlobalBounds()))
				|| (bulletE2.getGlobalBounds().intersects(wall2forbull.getGlobalBounds()))
				|| (bulletE2.getGlobalBounds().intersects(wall3forbull.getGlobalBounds()))
				|| (bulletE2.getGlobalBounds().intersects(wall4forbull.getGlobalBounds()))
				|| (bulletE2.getGlobalBounds().intersects(wall5forbull.getGlobalBounds()))
				) {
				bullE2out = false;
				bullE2TimeCount = 0;
				bulletE2.setPosition(enemy02Position);
			}
			if (DoorLV1Check == false) {
				if (bulletE2.getGlobalBounds().intersects(DoorLV1.getGlobalBounds())) {
					bullE2out = false;
					bullE2TimeCount = 0;
					bulletE2.setPosition(0, 0);
					//bullet3.setPosition(0, 0);
				}
			}

			//Level 1 > > bullet > > Enemy1 > > player > > enemy1Area//

			if (enemy1Life > 0) {

				//DetectionZone&Attack//
				enemy01Area.setPosition(enemy01Position.x, enemy01Position.y);
				if (player.getGlobalBounds().intersects(enemy01Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy01AreaCheck = true;
					enemy01AreaTimeCount = 0;
					if (bullE1out == false) {
						bullE1TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE1TimeCount >= 25) {
							AtkE1 = true;
							
						}
					}
				}
				
				if (bullet1.getGlobalBounds().intersects(enemy01.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemy01.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemy01.getGlobalBounds())) {
					enemy01AreaCheck = true;
				}

				if (enemy01AreaCheck == true && !(player.getGlobalBounds().intersects(enemy01Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy01AreaTimeCount > 50) {
						enemy01AreaCheck = false;
						enemy01AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy01AreaTimeCount += 1;
				}
			
				if (AtkE1 == true) {
					float dxE1 = playerPosition.x - enemy01Position.x, dyE1 = (playerPosition.y - enemy01Position.y);
					//Q1
					if (playerPosition.x > enemy01Position.x && playerPosition.y < enemy01Position.y) {
						//printf("1\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemy01Position.x - playerPosition.x) / abs(enemy01Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemy01Position.x -playerPosition.x) / abs(enemy01Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1Y =	spBullE1Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemy01Position.x && playerPosition.y < enemy01Position.y) {
						//printf("2\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemy01Position.x - playerPosition.x) / abs(enemy01Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemy01Position.x - playerPosition.x) / abs(enemy01Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1X = spBullE1X* -1;
						spBullE1Y = spBullE1Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemy01Position.x && playerPosition.y > enemy01Position.y) {
						 
						//printf("3\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemy01Position.x - playerPosition.x) / abs(enemy01Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemy01Position.x - playerPosition.x) / abs(enemy01Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1X = spBullE1X * -1;
						
					}
					//Q4
					else if (playerPosition.x > enemy01Position.x && playerPosition.y > enemy01Position.y) {
						float dxE1 = (playerPosition.x - enemy01Position.x), dyE1 = (playerPosition.y - enemy01Position.y);
						//printf("4\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemy01Position.x - playerPosition.x) / abs(enemy01Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemy01Position.x - playerPosition.x) / abs(enemy01Position.y - playerPosition.y)) * spBullE1Y;

					}
					AtkE1 = false;
					bullE1out = true;
					bulletE1.setPosition(enemy01Position.x + 50, enemy01Position.y + 50);
				}


				//bulletWithEnemy//


				if (bullet1.getGlobalBounds().intersects(enemy01.getGlobalBounds())) {
					bull1out = false;
					bulletNo[0] = 0;
					bull1Col = false;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemy1Life -= 1;
					printf("hit - enemyLife = %d\n", enemy1Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemy01.getGlobalBounds())) {
					bull2out = false;
					bulletNo[1] = 0;
					bull2Col = false;
					bulletTimeOut[1] = 0; 
					bullet2.setPosition(0, 0);
					enemy1Life -= 1;
					printf("hit - enemyLife = %d\n", enemy1Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemy01.getGlobalBounds())) {
					bull3out = false;
					bulletNo[2] = 0;
					bull3Col = false;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemy1Life -= 1;
					printf("hit - enemyLife = %d\n", enemy1Life);
				}
			}

			//Level 1 > > bullet > > Enemy2 > > player > > enemy2Area//

			if (enemy2Life > 0) {

				//DetectionZone&Attack//
				enemy02Area.setPosition(enemy02Position.x, enemy02Position.y);
				if (player.getGlobalBounds().intersects(enemy02Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy02AreaCheck = true;
					enemy02AreaTimeCount = 0;
					if (bullE2out == false) {
						bullE2TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE2TimeCount >= 25) {
							AtkE2 = true;
						}
					}
				} 
				if (bullet1.getGlobalBounds().intersects(enemy02.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemy02.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemy02.getGlobalBounds())) {
					enemy02AreaCheck = true;
				}
				if (enemy02AreaCheck == true && !(player.getGlobalBounds().intersects(enemy02Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy02AreaTimeCount > 50) {
						enemy02AreaCheck = false;
						enemy02AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy02AreaTimeCount += 1;
				}

				if (AtkE2 == true) {
					//Q1
					if (playerPosition.x > enemy02Position.x && playerPosition.y < enemy02Position.y) {
				
						spBullE2Y = sqrt(100 / (pow(abs(enemy02Position.x - playerPosition.x) / abs(enemy02Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemy02Position.x - playerPosition.x) / abs(enemy02Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2Y = spBullE2Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemy02Position.x && playerPosition.y < enemy02Position.y) {
				
						spBullE2Y = sqrt(100 / (pow(abs(enemy02Position.x - playerPosition.x) / abs(enemy02Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemy02Position.x - playerPosition.x) / abs(enemy02Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2X = spBullE2X * -1;
						spBullE2Y = spBullE2Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemy02Position.x && playerPosition.y > enemy02Position.y) {

						
						spBullE2Y = sqrt(100 / (pow(abs(enemy02Position.x - playerPosition.x) / abs(enemy02Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemy02Position.x - playerPosition.x) / abs(enemy02Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2X = spBullE2X * -1;

					}
					//Q4
					else if (playerPosition.x > enemy02Position.x && playerPosition.y > enemy02Position.y) {
						
						spBullE2Y = sqrt(100 / (pow(abs(enemy02Position.x - playerPosition.x) / abs(enemy02Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemy02Position.x - playerPosition.x) / abs(enemy02Position.y - playerPosition.y)) * spBullE2Y;

					}
					AtkE2 = false;
					bullE2out = true;
					bulletE2.setPosition(enemy02Position.x + 50, enemy02Position.y + 50);
				}

				// < <
				if (bullet1.getGlobalBounds().intersects(enemy02.getGlobalBounds())) {
					bull1out = false;
					bulletNo[0] = 0;
					bull1Col = false;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemy2Life -= 1;
					printf("hit - enemyLife = %d\n", enemy2Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemy02.getGlobalBounds())) {
					bull2out = false;
					bulletNo[1] = 0;
					bull2Col = false;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemy2Life -= 1;
					printf("hit - enemyLife = %d\n", enemy2Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemy02.getGlobalBounds())) {
					bull3out = false;
					bulletNo[2] = 0;
					bull3Col = false;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemy2Life -= 1;
					printf("hit - enemyLife = %d\n", enemy2Life);
				}
			}
		}
			

		//LEVEL 2//

		//stage 1//

		if (n == 2) {

			//Level2 > > wall2//

			if ((playerPosition.y < wallLV201Pos.y + 75 && playerPosition.y>wallLV201Pos.y) && (playerPosition.x < wallLV201Pos.x + 975)) {
				w = false;
				//printf("w\n");
			}
			if ((playerPosition.y < wallLV201Pos.y + 40 && playerPosition.y > wallLV201Pos.y - 80) && (playerPosition.x < wallLV201Pos.x + 975)) {
				s = false;
				//printf("s\n");
			}
			if ((playerPosition.y<wallLV201Pos.y + 75 && playerPosition.y > wallLV201Pos.y - 80) && (playerPosition.x < wallLV201Pos.x + 985 && playerPosition.x > wallLV201Pos.x + 975)) {
				a = false;
				//printf("a\n");
			}

			//Level2 > > wall2//

			if ((playerPosition.y < wallLV202Pos.y + 75 && playerPosition.y > wallLV202Pos.y) && (playerPosition.x > wallLV202Pos.x - 70)) {
				w = false;
				//printf("w1\n");
			}
			if ((playerPosition.y < wallLV202Pos.y + 40 && playerPosition.y > wallLV202Pos.y - 80) && (playerPosition.x > wallLV202Pos.x - 70)) {
				s = false;
				//printf("s1\n");
			}
			if ((playerPosition.y < wallLV202Pos.y + 75 && playerPosition.y > wallLV202Pos.y - 80) && (playerPosition.x < wallLV202Pos.x - 70 && playerPosition.x > wallLV202Pos.x - 80)) {
				d = false;
				//printf("d1\n");
			}

			//Level2 > > wall3//

			if ((playerPosition.y < wallLV203Pos.y + 40 && playerPosition.y > wallLV203Pos.y - 80) && (playerPosition.x > wallLV203Pos.x - 70 && playerPosition.x < wallLV203Pos.x + 70)) {
				s = false;
				//printf("d2\n");
			}
			if ((playerPosition.y > wallLV203Pos.y - 80) && (playerPosition.x < wallLV203Pos.x - 70 && playerPosition.x > wallLV203Pos.x - 80)) {
				d = false;
				//printf("d2\n");
			}
			if ((playerPosition.y > wallLV203Pos.y - 80) && (playerPosition.x > wallLV203Pos.x + 70 && playerPosition.x < wallLV203Pos.x + 80)) {
				a = false;
				//printf("a2\n");
			}

			//Level2 > > SpeedItem//

			if (player.getGlobalBounds().intersects(speed.getGlobalBounds())) {
				speedCheck = true;
				speedStatus = true;
			}
			
		

			//Level2 > > Gate//

			if (player.getGlobalBounds().intersects(GateLV2.getGlobalBounds())) {
				if (StageCount < 5) {
					num = (rand() % (5 - 1 + 1)) + 1;
					while (num == Stage[0] || num == Stage[1] || num == Stage[2] || num == Stage[3] || num == Stage[4]) {
						num = (rand() % (5 - 1 + 1)) + 1;
					}
					Stage[StageCount] = num;
					n = num;
					printf("num %d\n", num);
				}
				else if (StageCount == 5) {
					n = 6;
				}
				StageCount += 1;
				//n = 3;
				player.setPosition(20, 600);
			}

			// bullet collision //

			//bullet 1//

			if ((bullet1.getGlobalBounds().intersects(wallLV201forbull.getGlobalBounds()))
				|| (bullet1.getGlobalBounds().intersects(wallLV202forbull.getGlobalBounds()))
				|| (bullet1.getGlobalBounds().intersects(wallLV203.getGlobalBounds()))
				) {
				bull1out = false;
				bulletNo[0] = 0;
				bull1Col = false;
				bulletTimeOut[0] = 0;
				bullet1.setPosition(0, 0);
			}

			//bullet 2//

			if ((bullet2.getGlobalBounds().intersects(wallLV201forbull.getGlobalBounds()))
				|| (bullet2.getGlobalBounds().intersects(wallLV202forbull.getGlobalBounds()))
				|| (bullet2.getGlobalBounds().intersects(wallLV203.getGlobalBounds()))
				) {
				bull2out = false;
				bulletNo[1] = 0;
				bull2Col = false;
				bulletTimeOut[1] = 0;
				bullet2.setPosition(0, 0);
			}
			//bullet 3//

			if ((bullet3.getGlobalBounds().intersects(wallLV201forbull.getGlobalBounds()))
				|| (bullet3.getGlobalBounds().intersects(wallLV202forbull.getGlobalBounds()))
				|| (bullet3.getGlobalBounds().intersects(wallLV203.getGlobalBounds()))
				) {
				bull3out = false;
				bulletNo[2] = 0;
				bull3Col = false;
				bulletTimeOut[2] = 0;
				bullet3.setPosition(0, 0);
			}

			//bullet E1 

			if ((bulletE1.getGlobalBounds().intersects(wallLV201forbull.getGlobalBounds()))
				|| (bulletE1.getGlobalBounds().intersects(wallLV202forbull.getGlobalBounds()))
				|| (bulletE1.getGlobalBounds().intersects(wallLV203.getGlobalBounds()))
				) {
				bullE1out = false;
				bulletE1.setPosition(0, 0);
			}

			//bullet E2 

			if ((bulletE2.getGlobalBounds().intersects(wallLV201forbull.getGlobalBounds()))
				|| (bulletE2.getGlobalBounds().intersects(wallLV202forbull.getGlobalBounds()))
				|| (bulletE2.getGlobalBounds().intersects(wallLV203.getGlobalBounds()))
				) {
				bullE2out = false;
				bulletE2.setPosition(0, 0);
			}

			//Level 2 > > bullet > > Enemy1> > player > > enemy1Area//

			

			if (enemyLV201Life > 0) {

				//DetectionZone&Attack//
				enemy01Area.setPosition(enemyLV201Position.x, enemyLV201Position.y);
				if (player.getGlobalBounds().intersects(enemy01Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy01AreaCheck = true;
					enemy01AreaTimeCount = 0;
					if (bullE1out == false) {
						bullE1TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE1TimeCount >= 25) {
							AtkE1 = true;
						}
					}
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV201.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV201.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV201.getGlobalBounds())) {
					enemy01AreaCheck = true;
				}

				if (enemy01AreaCheck == true && !(player.getGlobalBounds().intersects(enemy01Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy01AreaTimeCount > 50) {
						enemy01AreaCheck = false;
						enemy01AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy01AreaTimeCount += 1;
				}

				if (AtkE1 == true) {
					//Q1
					if (playerPosition.x > enemyLV201Position.x && playerPosition.y < enemyLV201Position.y) {
						//printf("1\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV201Position.x - playerPosition.x) / abs(enemyLV201Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV201Position.x - playerPosition.x) / abs(enemyLV201Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1Y = spBullE1Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV201Position.x && playerPosition.y < enemyLV201Position.y) {
						//printf("2\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV201Position.x - playerPosition.x) / abs(enemyLV201Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV201Position.x - playerPosition.x) / abs(enemyLV201Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1X = spBullE1X * -1;
						spBullE1Y = spBullE1Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV201Position.x && playerPosition.y > enemyLV201Position.y) {

						//printf("3\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV201Position.x - playerPosition.x) / abs(enemyLV201Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV201Position.x - playerPosition.x) / abs(enemyLV201Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1X = spBullE1X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV201Position.x && playerPosition.y > enemyLV201Position.y) {
						float dxE1 = (playerPosition.x - enemyLV201Position.x), dyE1 = (playerPosition.y - enemyLV201Position.y);
						//printf("4\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV201Position.x - playerPosition.x) / abs(enemyLV201Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV201Position.x - playerPosition.x) / abs(enemyLV201Position.y - playerPosition.y)) * spBullE1Y;

					}
					AtkE1 = false;
					bullE1out = true;
					bulletE1.setPosition(enemyLV201Position.x + 50, enemyLV201Position.y + 50);
				}

				

				if (bullet1.getGlobalBounds().intersects(enemyLV201.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV201Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV201Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV201.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV201Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV201Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV201.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV201Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV201Life);
				}
			}

			//Level 2 > > bullet > > Enemy2 > > player > > enemy2Area//

	

			if (enemyLV202Life > 0) {
				
				//DetectionZone&Attack//
				enemy02Area.setPosition(enemyLV202Position.x, enemyLV202Position.y);
				if (player.getGlobalBounds().intersects(enemy02Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy02AreaCheck = true;
					enemy02AreaTimeCount = 0;
					if (bullE2out == false) {
						bullE2TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE2TimeCount >= 25) {
							AtkE2 = true;
						}
					}
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV202.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV202.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV202.getGlobalBounds())) {
					enemy02AreaCheck = true;
				}


				if (enemy02AreaCheck == true && !(player.getGlobalBounds().intersects(enemy02Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy02AreaTimeCount > 50) {
						enemy02AreaCheck = false;
						enemy02AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy02AreaTimeCount += 1;
				}

				if (AtkE2 == true) {
					//Q1
					if (playerPosition.x > enemyLV202Position.x && playerPosition.y < enemyLV202Position.y) {
						//printf("1\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV202Position.x - playerPosition.x) / abs(enemyLV202Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV202Position.x - playerPosition.x) / abs(enemyLV202Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2Y = spBullE2Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV202Position.x && playerPosition.y < enemyLV202Position.y) {
						//printf("2\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV202Position.x - playerPosition.x) / abs(enemyLV202Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV202Position.x - playerPosition.x) / abs(enemyLV202Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2X = spBullE2X * -1;
						spBullE2Y = spBullE2Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV202Position.x && playerPosition.y > enemyLV202Position.y) {

						//printf("3\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV202Position.x - playerPosition.x) / abs(enemyLV202Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV202Position.x - playerPosition.x) / abs(enemyLV202Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2X = spBullE2X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV202Position.x && playerPosition.y > enemyLV202Position.y) {
						//printf("4\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV202Position.x - playerPosition.x) / abs(enemyLV202Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV202Position.x - playerPosition.x) / abs(enemyLV202Position.y - playerPosition.y)) * spBullE2Y;

					}
					AtkE2 = false;
					bullE2out = true;
					bulletE2.setPosition(enemyLV202Position.x + 50, enemyLV202Position.y + 50);
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV202.getGlobalBounds())) {
					bull1out = false;
					bulletNo[0] = 0;
					bull1Col = false;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV202Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV202Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV202.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV202Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV202Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV202.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV202Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV202Life);
				}
			}

		}

		//stage 2//

		if (n == 3) {

			//Level1 > > wall3//

			if ((playerPosition.y < wallLV204Pos.y + 40 && playerPosition.y > wallLV204Pos.y - 80) && (playerPosition.x > wallLV204Pos.x - 70 && playerPosition.x < wallLV204Pos.x + 270)) {
				s = false;
				//printf("d2\n");
			}
			if ((playerPosition.y > wallLV204Pos.y - 80) && (playerPosition.x < wallLV204Pos.x - 70 && playerPosition.x > wallLV204Pos.x - 80)) {
				d = false;
				//printf("d2\n");
			}
			if ((playerPosition.y > wallLV204Pos.y - 80) && (playerPosition.x > wallLV204Pos.x + 270 && playerPosition.x < wallLV204Pos.x + 280)) {
				a = false;
				//printf("a2\n");
			}
			
			//Level2 > > Door//

			if (DoorLV2Check == false) {
				if ((playerPosition.y > DoorLV2Pos.y - 80) && (playerPosition.x < DoorLV2Pos.x - 70 && playerPosition.x > DoorLV2Pos.x - 80)) {
					d = false;
					//printf("d2\n");
				}
			}

			//Level2 > > Democrac//

			if (player.getGlobalBounds().intersects(DemocracLV2.getGlobalBounds())) {
				if (StageCount < 5) {
					num = (rand() % (5 - 1 + 1)) + 1;
					while (num == Stage[0] || num == Stage[1] || num == Stage[2] || num == Stage[3] || num == Stage[4]) {
						num = (rand() % (5 - 1 + 1)) + 1;
					}
					Stage[StageCount] = num;
					n = num;
					printf("num %d\n", num);
				}
				else if (StageCount == 5) {
					n = 6;
				}
				StageCount += 1;
				//n = 4;
				player.setPosition(20, 600);
			}

			//Level 2 >> Key//

			if (KeyLV2Check == false) {
				if (player.getGlobalBounds().intersects(KeyLV2.getGlobalBounds())) {
					KeyLV2Check = true;
					DoorLV2Check = true;
				}
			}

			//Level 2 >> life//

			if (player.getGlobalBounds().intersects(life.getGlobalBounds())) {
				lifeCheck = true;
				lifeStatus = true;
			}
			if (lifeStatus == true) {
				playerLife = 3;
				lifeStatus = false;
			}

			//level
			// bullet collision //

			//bullet 1//

			if ((bullet1.getGlobalBounds().intersects(wallLV204.getGlobalBounds()))
				) {
				bull1out = false;
				bull1Col = false;
				bulletNo[0] = 0;
				bulletTimeOut[0] = 0;
				bullet1.setPosition(0, 0);
			}
			if (DoorLV2Check == false) {
				if ((bullet1.getGlobalBounds().intersects(DoorLV2.getGlobalBounds()))) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bullet1.setPosition(0, 0);
				}
			}

			//bullet 2//

			if ((bullet2.getGlobalBounds().intersects(wallLV204.getGlobalBounds()))
				) {
				bull2out = false;
				bulletNo[1] = 0;
				bull2Col = false;
				bulletTimeOut[1] = 0;
				bullet2.setPosition(0, 0);
			}
			if (DoorLV2Check == false) {
				if ((bullet2.getGlobalBounds().intersects(DoorLV2.getGlobalBounds()))) {
					bull2out = false;
					bulletNo[1] = 0;
					bull2Col = false;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
				}
			}

			//bullet 3//

			if ((bullet3.getGlobalBounds().intersects(wallLV204.getGlobalBounds()))
				) {
				bull3out = false;
				bulletTimeOut[2] = 0;
				bull3Col = false;
				bulletNo[2] = 0;
				bullet3.setPosition(0, 0);
			}
			if (DoorLV2Check == false) {
				if ((bullet3.getGlobalBounds().intersects(DoorLV2.getGlobalBounds()))) {
					bull3out = false;
					bulletNo[2] = 0;
					bull3Col = false;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
				}
			}

			//bulletE1//

			if ((bulletE1.getGlobalBounds().intersects(wallLV204.getGlobalBounds()))
				) {
				bullE1out = false;
				bulletE1.setPosition(0, 0);
			}
			if (DoorLV2Check == false) {
				if ((bulletE1.getGlobalBounds().intersects(DoorLV2.getGlobalBounds()))) {
					bullE1out = false;
					bulletE1.setPosition(0, 0);
				}
			}

			if ((bulletE2.getGlobalBounds().intersects(wallLV204.getGlobalBounds()))
				) {
				bullE2out = false;
				bulletE2.setPosition(0, 0);
			}
			if (DoorLV2Check == false) {
				if ((bulletE2.getGlobalBounds().intersects(DoorLV2.getGlobalBounds()))) {
					bullE2out = false;
					bulletE2.setPosition(0,0);
				}
			}

			//bulletE3//

			if ((bulletE3.getGlobalBounds().intersects(wallLV204.getGlobalBounds()))
				) {
				bullE3out = false;
				bulletE3.setPosition(0,0);
			}
			if (DoorLV2Check == false) {
				if ((bulletE3.getGlobalBounds().intersects(DoorLV2.getGlobalBounds()))) {
					bullE3out = false;
					bulletE3.setPosition(0,0);
				}
			}

			//Level 2 > > bullet > > Enemy3 > > player > > enemy1Area//

			if (enemyLV203Life > 0) {

				//DetectionZone&Attack//
				enemy01Area.setPosition(enemyLV203Position.x, enemyLV203Position.y);
				if (player.getGlobalBounds().intersects(enemy01Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy01AreaCheck = true;
					enemy01AreaTimeCount = 0;
					if (bullE1out == false) {
						bullE1TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE1TimeCount >= 25) {
							AtkE1 = true;
						}
					}
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV203.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV203.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV203.getGlobalBounds())) {
					enemy01AreaCheck = true;
				}

				if (enemy01AreaCheck == true && !(player.getGlobalBounds().intersects(enemy01Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy01AreaTimeCount > 50) {
						enemy01AreaCheck = false;
						enemy01AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy01AreaTimeCount += 1;
				}

				if (AtkE1 == true) {
					//Q1
					if (playerPosition.x > enemyLV203Position.x && playerPosition.y < enemyLV203Position.y) {
						//printf("1\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV203Position.x - playerPosition.x) / abs(enemyLV203Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV203Position.x - playerPosition.x) / abs(enemyLV203Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1Y = spBullE1Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV203Position.x && playerPosition.y < enemyLV203Position.y) {
						//printf("2\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV203Position.x - playerPosition.x) / abs(enemyLV203Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV203Position.x - playerPosition.x) / abs(enemyLV203Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1X = spBullE1X * -1;
						spBullE1Y = spBullE1Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV203Position.x && playerPosition.y > enemyLV203Position.y) {

						//printf("3\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV203Position.x - playerPosition.x) / abs(enemyLV203Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV203Position.x - playerPosition.x) / abs(enemyLV203Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1X = spBullE1X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV203Position.x && playerPosition.y > enemyLV203Position.y) {
						//printf("4\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV203Position.x - playerPosition.x) / abs(enemyLV203Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV203Position.x - playerPosition.x) / abs(enemyLV203Position.y - playerPosition.y)) * spBullE1Y;

					}
					AtkE1 = false;
					bullE1out = true;
					bulletE1.setPosition(enemyLV203Position.x + 50, enemyLV203Position.y + 50);
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV203.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV203Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV203Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV203.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV203Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV203Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV203.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV203Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV203Life);
				}
			}

			//Level 2 > > bullet > > > > Enemy4 > > player > > enemy2Area//


			if (enemyLV204Life > 0) {

				//DetectionZone&Attack//
				enemy02Area.setPosition(enemyLV204Position.x, enemyLV204Position.y);
				if (player.getGlobalBounds().intersects(enemy02Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy02AreaCheck = true;
					enemy02AreaTimeCount = 0;
					if (bullE2out == false) {
						bullE2TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE2TimeCount >= 25) {
							AtkE2 = true;
						}
					}
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV204.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV204.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV204.getGlobalBounds())) {
					enemy02AreaCheck = true;
				}

				if (enemy02AreaCheck == true && !(player.getGlobalBounds().intersects(enemy02Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy02AreaTimeCount > 50) {
						enemy02AreaCheck = false;
						enemy02AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy02AreaTimeCount += 1;
				}

				if (AtkE2 == true) {
					//Q1
					if (playerPosition.x > enemyLV204Position.x && playerPosition.y < enemyLV204Position.y) {
						//printf("1\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV204Position.x - playerPosition.x) / abs(enemyLV204Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV204Position.x - playerPosition.x) / abs(enemyLV204Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2Y = spBullE2Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV204Position.x && playerPosition.y < enemyLV204Position.y) {
						//printf("2\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV204Position.x - playerPosition.x) / abs(enemyLV204Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV204Position.x - playerPosition.x) / abs(enemyLV204Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2X = spBullE2X * -1;
						spBullE2Y = spBullE2Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV204Position.x && playerPosition.y > enemyLV204Position.y) {

						//printf("3\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV204Position.x - playerPosition.x) / abs(enemyLV204Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV204Position.x - playerPosition.x) / abs(enemyLV204Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2X = spBullE2X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV204Position.x && playerPosition.y > enemyLV204Position.y) {
						//printf("4\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV204Position.x - playerPosition.x) / abs(enemyLV204Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV204Position.x - playerPosition.x) / abs(enemyLV204Position.y - playerPosition.y)) * spBullE2Y;

					}
					AtkE2 = false;
					bullE2out = true;
					bulletE2.setPosition(enemyLV204Position.x + 50, enemyLV204Position.y + 50);
				}


				if (bullet1.getGlobalBounds().intersects(enemyLV204.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV204Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV204Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV204.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV204Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV204Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV204.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV204Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV204Life);
				}
			}

			//Level 2 > > bullet > > > > Enemy5 > > player > > enemy3Area//


			if (enemyLV205Life > 0) {

				//DetectionZone&Attack//
				enemy03Area.setPosition(enemyLV205Position.x, enemyLV205Position.y);
				if (player.getGlobalBounds().intersects(enemy03Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy03AreaCheck = true;
					enemy03AreaTimeCount = 0;
					if (bullE3out == false) {
						bullE3TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE3TimeCount >= 25) {
							AtkE3 = true;
						}
					}
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV205.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV205.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV205.getGlobalBounds())) {
					enemy03AreaCheck = true;
				}

				if (enemy03AreaCheck == true && !(player.getGlobalBounds().intersects(enemy03Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy03AreaTimeCount > 50) {
						enemy03AreaCheck = false;
						enemy03AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy03AreaTimeCount += 1;
				}

				if (AtkE3 == true) {
					//Q1
					if (playerPosition.x > enemyLV205Position.x && playerPosition.y < enemyLV205Position.y) {
						//printf("1\n");
						spBullE3Y = sqrt(100 / (pow(abs(enemyLV205Position.x - playerPosition.x) / abs(enemyLV205Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV205Position.x - playerPosition.x) / abs(enemyLV205Position.y - playerPosition.y)) * spBullE3Y;
						spBullE3Y = spBullE3Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV205Position.x && playerPosition.y < enemyLV205Position.y) {
						//printf("2\n");
						spBullE3Y = sqrt(100 / (pow(abs(enemyLV205Position.x - playerPosition.x) / abs(enemyLV205Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV205Position.x - playerPosition.x) / abs(enemyLV205Position.y - playerPosition.y)) * spBullE3Y;
						spBullE3X = spBullE3X * -1;
						spBullE3Y = spBullE3Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV205Position.x && playerPosition.y > enemyLV205Position.y) {

						//printf("3\n");
						spBullE3Y = sqrt(100 / (pow(abs(enemyLV205Position.x - playerPosition.x) / abs(enemyLV205Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV205Position.x - playerPosition.x) / abs(enemyLV205Position.y - playerPosition.y)) * spBullE3Y;
						spBullE3X = spBullE3X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV205Position.x && playerPosition.y > enemyLV205Position.y) {
						//printf("4\n");
						spBullE3Y = sqrt(100 / (pow(abs(enemyLV205Position.x - playerPosition.x) / abs(enemyLV205Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV205Position.x - playerPosition.x) / abs(enemyLV205Position.y - playerPosition.y)) * spBullE3Y;

					}
					AtkE3 = false;
					bullE3out = true;
					bulletE3.setPosition(enemyLV205Position.x + 50, enemyLV205Position.y + 50);
				}


				if (bullet1.getGlobalBounds().intersects(enemyLV205.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV205Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV205Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV205.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV205Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV205Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV205.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV205Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV205Life);
				}
			}

		}

		//LEVEL 3//

		if (n == 4) {

			//Level3 > > wall1//

			if ((playerPosition.y < wallLV301Pos.y + 40 && playerPosition.y > wallLV301Pos.y - 80) && (playerPosition.x > wallLV301Pos.x - 70 && playerPosition.x < wallLV301Pos.x + 270)) {
				s = false;
				//printf("d2\n");
			}
			if ((playerPosition.y > wallLV301Pos.y - 80) && (playerPosition.x < wallLV301Pos.x - 70 && playerPosition.x > wallLV301Pos.x - 80)) {
				d = false;
				//printf("d2\n");
			}
			if ((playerPosition.y > wallLV301Pos.y - 80) && (playerPosition.x > wallLV301Pos.x + 170 && playerPosition.x < wallLV301Pos.x + 180)) {
				a = false;
				//printf("a2\n");

			}
			//Level3 > > wall2//

			if ((playerPosition.y < wallLV302Pos.y + 130) && (playerPosition.x > wallLV302Pos.x - 70 && playerPosition.x < wallLV302Pos.x + 70)) {
				w = false;
				//printf("w\n");
			}
			if ((playerPosition.y < wallLV302Pos.y + 130) && (playerPosition.x < wallLV302Pos.x - 70 && playerPosition.x > wallLV302Pos.x - 80)) {
				d = false;
				//printf("d\n");
			}
			if ((playerPosition.y < wallLV302Pos.y + 130) && (playerPosition.x > wallLV302Pos.x + 70 && playerPosition.x < wallLV302Pos.x + 80)) {
				a = false;
				//printf("a\n");
			}

			//Level3 > > wall3//

			if ((playerPosition.y < wallLV303Pos.y + 75 && playerPosition.y>wallLV303Pos.y) && (playerPosition.x < wallLV303Pos.x + 470 && playerPosition.x > wallLV303Pos.x - 70)) {
				w = false;
				//printf("w\n");
			}
			if ((playerPosition.y < wallLV303Pos.y + 40 && playerPosition.y > wallLV303Pos.y - 80) && (playerPosition.x < wallLV303Pos.x + 470 && playerPosition.x > wallLV303Pos.x - 70)) {
				s = false;
				//printf("s\n");
			}
			if ((playerPosition.y<wallLV303Pos.y + 75 && playerPosition.y > wallLV303Pos.y - 80) && (playerPosition.x < wallLV303Pos.x + 480 && playerPosition.x > wallLV303Pos.x + 470)) {
				a = false;
				//printf("a\n");
			}

			//Level3 > > Democradc//

			if (player.getGlobalBounds().intersects(DemocracLV3.getGlobalBounds())) {
				if (StageCount < 5) {
					num = (rand() % (5 - 1 + 1)) + 1;
					while (num == Stage[0] || num == Stage[1] || num == Stage[2] || num == Stage[3] || num == Stage[4]) {
						num = (rand() % (5 - 1 + 1)) + 1;
					}
					Stage[StageCount] = num;
					n = num;
					printf("num %d\n", num);
				}
				else if (StageCount == 5) {
					n = 6;
				}
				StageCount += 1;
				//n = 5;
				player.setPosition(20, 600);
			}

			// bullet collision //

			//bullet 1//

			if ((bullet1.getGlobalBounds().intersects(wallLV301.getGlobalBounds()))
				|| (bullet1.getGlobalBounds().intersects(wallLV302forbull.getGlobalBounds()))
				|| (bullet1.getGlobalBounds().intersects(wallLV303.getGlobalBounds()))
				) {
				bull1out = false;
				bull1Col = false;
				bulletNo[0] = 0;
				bulletTimeOut[0] = 0;
				bullet1.setPosition(0, 0);
			}

			//bullet 2//

			if ((bullet2.getGlobalBounds().intersects(wallLV301.getGlobalBounds()))
				|| (bullet2.getGlobalBounds().intersects(wallLV302forbull.getGlobalBounds()))
				|| (bullet2.getGlobalBounds().intersects(wallLV303forbull.getGlobalBounds()))
				) {
				bull2out = false;
				bull2Col = false;
				bulletNo[1] = 0;
				bulletTimeOut[1] = 0;
				bullet2.setPosition(0, 0);
			}

			//bullet 3//

			if ((bullet3.getGlobalBounds().intersects(wallLV301.getGlobalBounds()))
				|| (bullet3.getGlobalBounds().intersects(wallLV302forbull.getGlobalBounds()))
				|| (bullet3.getGlobalBounds().intersects(wallLV303forbull.getGlobalBounds()))
				) {
				bull3out = false;
				bull3Col = false;
				bulletNo[2] = 0;
				bulletTimeOut[2] = 0;
				bullet3.setPosition(0, 0);
			}

			//bulletE1//

			if ((bulletE1.getGlobalBounds().intersects(wallLV301.getGlobalBounds()))
				|| (bulletE1.getGlobalBounds().intersects(wallLV302forbull.getGlobalBounds()))
				|| (bulletE1.getGlobalBounds().intersects(wallLV303forbull.getGlobalBounds()))
				) {
				bullE1out = false;
				bulletE1.setPosition(0,0);
			}

			//bulletE2//

			if ((bulletE2.getGlobalBounds().intersects(wallLV301.getGlobalBounds()))
				|| (bulletE2.getGlobalBounds().intersects(wallLV302forbull.getGlobalBounds()))
				|| (bulletE2.getGlobalBounds().intersects(wallLV303forbull.getGlobalBounds()))
				) {
				bullE2out = false;
				bulletE2.setPosition(0, 0);;
			}

			//bulletE3//

			if ((bulletE3.getGlobalBounds().intersects(wallLV301.getGlobalBounds()))
				|| (bulletE3.getGlobalBounds().intersects(wallLV302forbull.getGlobalBounds()))
				|| (bulletE3.getGlobalBounds().intersects(wallLV303forbull.getGlobalBounds()))
				) {
				bullE3out = false;
				bulletE3.setPosition(0, 0);;
			}

			//Level 3 > > bullet > > Enemy1//

			if (enemyLV301Life > 0) {

				//DetectionZone&Attack//
				enemy01Area.setPosition(enemyLV301Position.x, enemyLV301Position.y);
				if (player.getGlobalBounds().intersects(enemy01Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy01AreaCheck = true;
					enemy01AreaTimeCount = 0;
					if (bullE1out == false) {
						bullE1TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE1TimeCount >= 25) {
							AtkE1 = true;
						}
					}
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV301.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV301.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV301.getGlobalBounds())) {
					enemy01AreaCheck = true;
				}

				if (enemy01AreaCheck == true && !(player.getGlobalBounds().intersects(enemy01Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy01AreaTimeCount > 50) {
						enemy01AreaCheck = false;
						enemy01AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy01AreaTimeCount += 1;
				}

				if (AtkE1 == true) {
					//Q1
					if (playerPosition.x > enemyLV301Position.x && playerPosition.y < enemyLV301Position.y) {
						//printf("1\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV301Position.x - playerPosition.x) / abs(enemyLV301Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV301Position.x - playerPosition.x) / abs(enemyLV301Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1Y = spBullE1Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV301Position.x && playerPosition.y < enemyLV301Position.y) {
						//printf("2\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV301Position.x - playerPosition.x) / abs(enemyLV301Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV301Position.x - playerPosition.x) / abs(enemyLV301Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1X = spBullE1X * -1;
						spBullE1Y = spBullE1Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV301Position.x && playerPosition.y > enemyLV301Position.y) {

						//printf("3\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV301Position.x - playerPosition.x) / abs(enemyLV301Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV301Position.x - playerPosition.x) / abs(enemyLV301Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1X = spBullE1X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV301Position.x && playerPosition.y > enemyLV301Position.y) {
						//printf("4\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV301Position.x - playerPosition.x) / abs(enemyLV301Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV301Position.x - playerPosition.x) / abs(enemyLV301Position.y - playerPosition.y)) * spBullE1Y;

					}
					AtkE1 = false;
					bullE1out = true;
					bulletE1.setPosition(enemyLV301Position.x + 50, enemyLV301Position.y + 50);
				}

			

				if (bullet1.getGlobalBounds().intersects(enemyLV301.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV301Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV301Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV301.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV301Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV301Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV301.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV301Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV301Life);
				}
			}

			//Level 3 > > bullet > > Enemy2//

			if (enemyLV302Life > 0) {

				//DetectionZone&Attack//
				enemy02Area.setPosition(enemyLV302Position.x, enemyLV302Position.y);
				if (player.getGlobalBounds().intersects(enemy02Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy02AreaCheck = true;
					enemy02AreaTimeCount = 0;
					if (bullE2out == false) {
						bullE2TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE2TimeCount >= 25) {
							AtkE2 = true;
						}
					}
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV302.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV302.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV302.getGlobalBounds())) {
					enemy02AreaCheck = true;
				}

				if (enemy02AreaCheck == true && !(player.getGlobalBounds().intersects(enemy02Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy02AreaTimeCount > 50) {
						enemy02AreaCheck = false;
						enemy02AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy02AreaTimeCount += 1;
				}

				if (AtkE2 == true) {
					//Q1
					if (playerPosition.x > enemyLV302Position.x && playerPosition.y < enemyLV302Position.y) {
						//printf("1\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV302Position.x - playerPosition.x) / abs(enemyLV302Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV302Position.x - playerPosition.x) / abs(enemyLV302Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2Y = spBullE2Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV302Position.x && playerPosition.y < enemyLV302Position.y) {
						//printf("2\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV302Position.x - playerPosition.x) / abs(enemyLV302Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV302Position.x - playerPosition.x) / abs(enemyLV302Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2X = spBullE2X * -1;
						spBullE2Y = spBullE2Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV302Position.x && playerPosition.y > enemyLV302Position.y) {

						//printf("3\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV302Position.x - playerPosition.x) / abs(enemyLV302Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV302Position.x - playerPosition.x) / abs(enemyLV302Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2X = spBullE2X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV302Position.x && playerPosition.y > enemyLV302Position.y) {
						//printf("4\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV302Position.x - playerPosition.x) / abs(enemyLV302Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV302Position.x - playerPosition.x) / abs(enemyLV302Position.y - playerPosition.y)) * spBullE2Y;

					}
					AtkE2 = false;
					bullE2out = true;
					bulletE2.setPosition(enemyLV302Position.x + 50, enemyLV302Position.y + 50);
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV302.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV302Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV302Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV302.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV302Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV302Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV302.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV302Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV302Life);
				}
			}

			//Level 3 > > bullet > > Enemy3//

			if (enemyLV303Life > 0) {

				//DetectionZone&Attack//
				enemy03Area.setPosition(enemyLV303Position.x, enemyLV303Position.y);
				if (player.getGlobalBounds().intersects(enemy03Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy03AreaCheck = true;
					enemy03AreaTimeCount = 0;
					if (bullE3out == false) {
						bullE3TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE3TimeCount >= 25) {
							AtkE3 = true;
						}
					}
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV303.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV303.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV303.getGlobalBounds())) {
					enemy03AreaCheck = true;
				}

				if (enemy03AreaCheck == true && !(player.getGlobalBounds().intersects(enemy03Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy03AreaTimeCount > 50) {
						enemy03AreaCheck = false;
						enemy03AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy03AreaTimeCount += 1;
				}

				if (AtkE3 == true) {
					//Q1
					if (playerPosition.x > enemyLV303Position.x && playerPosition.y < enemyLV303Position.y) {

						spBullE3Y = sqrt(100 / (pow(abs(enemyLV303Position.x - playerPosition.x) / abs(enemyLV303Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV303Position.x - playerPosition.x) / abs(enemyLV303Position.y - playerPosition.y)) * spBullE3Y;
						spBullE3Y = spBullE3Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV303Position.x && playerPosition.y < enemyLV303Position.y) {

						spBullE3Y = sqrt(100 / (pow(abs(enemyLV303Position.x - playerPosition.x) / abs(enemyLV303Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV303Position.x - playerPosition.x) / abs(enemyLV303Position.y - playerPosition.y)) * spBullE3Y;
						spBullE3X = spBullE3X * -1;
						spBullE3Y = spBullE3Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV303Position.x && playerPosition.y > enemyLV303Position.y) {


						spBullE3Y = sqrt(100 / (pow(abs(enemy02Position.x - playerPosition.x) / abs(enemy02Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV303Position.x - playerPosition.x) / abs(enemyLV303Position.y - playerPosition.y)) * spBullE3Y;
						spBullE3X = spBullE3X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV303Position.x && playerPosition.y > enemyLV303Position.y) {

						spBullE3Y = sqrt(100 / (pow(abs(enemyLV303Position.x - playerPosition.x) / abs(enemyLV303Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV303Position.x - playerPosition.x) / abs(enemyLV303Position.y - playerPosition.y)) * spBullE3Y;

					}
					AtkE3 = false;
					bullE3out = true;
					bulletE3.setPosition(enemyLV303Position.x + 50, enemyLV303Position.y + 50);
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV303.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV303Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV303Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV303.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV303Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV303Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV303.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV303Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV303Life);
				}
			}
		}

		//LEVEL 4//

		if (n == 5) {

			//Level4 > > wall1//

			if ((playerPosition.y < wallLV401Pos.y + 75 && playerPosition.y>wallLV401Pos.y) && (playerPosition.x < wallLV401Pos.x + 870)) {
				w = false;
				//printf("w\n");
			}
			if ((playerPosition.y < wallLV401Pos.y + 40 && playerPosition.y > wallLV401Pos.y - 80) && (playerPosition.x < wallLV401Pos.x + 870)) {
				s = false;
				//printf("s\n");
			}
			if ((playerPosition.y<wallLV401Pos.y + 75 && playerPosition.y > wallLV401Pos.y - 80) && (playerPosition.x < wallLV401Pos.x + 880 && playerPosition.x > wallLV401Pos.x + 870)) {
				a = false;
				//printf("a\n");
			}

			//Level4 > > wall2//

			if ((playerPosition.y < wallLV402Pos.y + 130) && (playerPosition.x > wallLV402Pos.x - 70 && playerPosition.x < wallLV402Pos.x + 70)) {
				w = false;
				//printf("w\n");
			}
			if ((playerPosition.y < wallLV402Pos.y + 130) && (playerPosition.x < wallLV402Pos.x - 70 && playerPosition.x > wallLV402Pos.x - 80)) {
				d = false;
				//printf("d\n");
			}
			if ((playerPosition.y < wallLV402Pos.y + 130) && (playerPosition.x > wallLV402Pos.x + 70 && playerPosition.x < wallLV402Pos.x + 80)) {
				a = false;
				//printf("a\n");
			}

			//Level4 > > Door//

			if (DoorLV4Check == false) {
				if ((playerPosition.y < DoorLV4Pos.y + 150) && (playerPosition.x < DoorLV4Pos.x + 40 && playerPosition.x > DoorLV4Pos.x + 30)) {
					a = false;
					//printf("d2\n");
				}
			}

			//Level4 > > ImortalPotion//

			if (imortalCheck == false && player.getGlobalBounds().intersects(ImortalPot.getGlobalBounds())) {
				imortalCheck = true;
			}
		
			
			//Level4 > > Key//

			if (KeyLV4Check == false) {
				if (player.getGlobalBounds().intersects(KeyLV4.getGlobalBounds())) {
					KeyLV4Check = true;
					DoorLV4Check = true;
				}
			}


			//Level4 > > Gate//

			if (player.getGlobalBounds().intersects(GateLV4.getGlobalBounds())) {
				if (StageCount < 5) {
					num = (rand() % (5 - 1 + 1)) + 1;
					while (num == Stage[0] || num == Stage[1] || num == Stage[2] || num == Stage[3] || num == Stage[4]) {
						num = (rand() % (5 - 1 + 1)) + 1;
					}
					Stage[StageCount] = num;
					n = num;
					printf("num %d\n", num);
				}
				else if (StageCount == 5) {
					n = 6;
				}
				StageCount += 1;
				//n = 6;
				player.setPosition(20, 600);
			}

			// bullet collision //

			//bullet 1//

			if ((bullet1.getGlobalBounds().intersects(wallLV401forbull.getGlobalBounds()))
				|| (bullet1.getGlobalBounds().intersects(wallLV402forbull.getGlobalBounds()))
				|| (bullet1.getGlobalBounds().intersects(DoorLV4.getGlobalBounds())))
				 {
				bull1out = false;
				bull1Col = false;
				bulletNo[0] = 0;
				bulletTimeOut[0] = 0;
				bullet1.setPosition(0, 0);
			}

			//bullet 2//

			if ((bullet2.getGlobalBounds().intersects(wallLV401forbull.getGlobalBounds()))
				|| (bullet2.getGlobalBounds().intersects(wallLV402forbull.getGlobalBounds())
				|| (bullet2.getGlobalBounds().intersects(DoorLV4.getGlobalBounds())))
				) {
				bull2out = false;
				bull2Col = false;
				bulletNo[1] = 0;
				bulletTimeOut[1] = 0;
				bullet2.setPosition(0, 0);
			}

			//bullet 3//

			if ((bullet3.getGlobalBounds().intersects(wallLV401forbull.getGlobalBounds()))
				|| (bullet3.getGlobalBounds().intersects(wallLV402forbull.getGlobalBounds())
				|| (bullet3.getGlobalBounds().intersects(DoorLV4.getGlobalBounds())))
				) {
				bull3out = false;
				bulletNo[2] = 0;
				bull3Col = false;
				bulletTimeOut[2] = 0;
				bullet3.setPosition(0, 0);
			}


			//bulletE1//

			if ((bulletE1.getGlobalBounds().intersects(wallLV401forbull.getGlobalBounds()))
				|| (bulletE1.getGlobalBounds().intersects(wallLV402forbull.getGlobalBounds()))
				|| (bullet3.getGlobalBounds().intersects(DoorLV4.getGlobalBounds()))
				) {
				bullE1out = false;
				bulletE1.setPosition(0, 0);
			}

			//bulletE2//

			if ((bulletE2.getGlobalBounds().intersects(wallLV401forbull.getGlobalBounds()))
				|| (bulletE2.getGlobalBounds().intersects(wallLV402forbull.getGlobalBounds()))
				|| (bullet3.getGlobalBounds().intersects(DoorLV4.getGlobalBounds()))
				) {
				bullE2out = false;
				bulletE2.setPosition(0, 0);
			}
			//bulletE3//

			if ((bulletE3.getGlobalBounds().intersects(wallLV401forbull.getGlobalBounds()))
				|| (bulletE3.getGlobalBounds().intersects(wallLV402forbull.getGlobalBounds()))
				|| (bullet3.getGlobalBounds().intersects(DoorLV4.getGlobalBounds()))
				) {
				bullE3out = false;
				bulletE3.setPosition(0, 0);
			}

			//Level 4 > > bullet > > Enemy1//

			if (enemyLV401Life > 0) {

				//DetectionZone&Attack//
				enemy01Area.setPosition(enemyLV401Position.x, enemyLV401Position.y);
				if (player.getGlobalBounds().intersects(enemy01Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy01AreaCheck = true;
					enemy01AreaTimeCount = 0;
					if (bullE1out == false) {
						bullE1TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE1TimeCount >= 25) {
							AtkE1 = true;
						}
					}
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV401.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV401.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV401.getGlobalBounds())) {
					enemy01AreaCheck = true;
				}

				if (enemy01AreaCheck == true && !(player.getGlobalBounds().intersects(enemy01Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy01AreaTimeCount > 50) {
						enemy01AreaCheck = false;
						enemy01AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy01AreaTimeCount += 1;
				}

				if (AtkE1 == true) {
					//Q1
					if (playerPosition.x > enemyLV401Position.x && playerPosition.y < enemyLV401Position.y) {
						//printf("1\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV401Position.x - playerPosition.x) / abs(enemyLV401Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV401Position.x - playerPosition.x) / abs(enemyLV401Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1Y = spBullE1Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV401Position.x && playerPosition.y < enemyLV401Position.y) {
						//printf("2\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV401Position.x - playerPosition.x) / abs(enemyLV401Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV401Position.x - playerPosition.x) / abs(enemyLV401Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1X = spBullE1X * -1;
						spBullE1Y = spBullE1Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV401Position.x && playerPosition.y > enemyLV401Position.y) {

						//printf("3\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV401Position.x - playerPosition.x) / abs(enemyLV401Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV401Position.x - playerPosition.x) / abs(enemyLV401Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1X = spBullE1X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV401Position.x && playerPosition.y > enemyLV401Position.y) {
						//printf("4\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV401Position.x - playerPosition.x) / abs(enemyLV401Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV401Position.x - playerPosition.x) / abs(enemyLV401Position.y - playerPosition.y)) * spBullE1Y;

					}
					AtkE1 = false;
					bullE1out = true;
					bulletE1.setPosition(enemyLV401Position.x + 50, enemyLV401Position.y + 50);
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV401.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV401Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV401Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV401.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV401Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV401Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV401.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV401Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV401Life);
				}
			}

			//Level 4 > > bullet > > Enemy2//

			if (enemyLV402Life > 0) {

				//DetectionZone&Attack//
				enemy02Area.setPosition(enemyLV402Position.x, enemyLV402Position.y);
				if (player.getGlobalBounds().intersects(enemy02Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy02AreaCheck = true;
					enemy02AreaTimeCount = 0;
					if (bullE2out == false) {
						bullE2TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE2TimeCount >= 25) {
							AtkE2 = true;
						}
					}
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV402.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV402.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV402.getGlobalBounds())) {
					enemy01AreaCheck = true;
				}

				if (enemy02AreaCheck == true && !(player.getGlobalBounds().intersects(enemy02Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy02AreaTimeCount > 50) {
						enemy02AreaCheck = false;
						enemy02AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy02AreaTimeCount += 1;
				}

				if (AtkE2 == true) {
					//Q1
					if (playerPosition.x > enemyLV402Position.x && playerPosition.y < enemyLV402Position.y) {
						//printf("1\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV402Position.x - playerPosition.x) / abs(enemyLV402Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV402Position.x - playerPosition.x) / abs(enemyLV402Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2Y = spBullE2Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV402Position.x && playerPosition.y < enemyLV402Position.y) {
						//printf("2\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV402Position.x - playerPosition.x) / abs(enemyLV402Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV402Position.x - playerPosition.x) / abs(enemyLV402Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2X = spBullE2X * -1;
						spBullE2Y = spBullE2Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV402Position.x && playerPosition.y > enemyLV402Position.y) {

						//printf("3\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV402Position.x - playerPosition.x) / abs(enemyLV402Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV402Position.x - playerPosition.x) / abs(enemyLV402Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2X = spBullE2X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV402Position.x && playerPosition.y > enemyLV402Position.y) {
						//printf("4\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV402Position.x - playerPosition.x) / abs(enemyLV402Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV402Position.x - playerPosition.x) / abs(enemyLV402Position.y - playerPosition.y)) * spBullE2Y;

					}
					AtkE2 = false;
					bullE2out = true;
					bulletE2.setPosition(enemyLV402Position.x + 50, enemyLV402Position.y + 50);
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV402.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV402Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV402Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV402.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV402Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV402Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV402.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV402Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV402Life);
				}
			}
			//Level 4 > > bullet > > Enemy3//

			if (enemyLV405Life > 0) {

				//DetectionZone&Attack//
				enemy03Area.setPosition(enemyLV405Position.x, enemyLV405Position.y);
				if (player.getGlobalBounds().intersects(enemy03Area.getGlobalBounds())) {
					//printf("Chonlaew NAAAAA 2\n");
					enemy03AreaCheck = true;
					enemy03AreaTimeCount = 0;
					if (bullE3out == false) {
						bullE3TimeCount++;
						//printf("%d", bullE1TimeCount);
						if (bullE3TimeCount >= 25) {
							AtkE3 = true;
						}
					}
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV405.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV405.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV405.getGlobalBounds())) {
					enemy03AreaCheck = true;
				}

				if (enemy03AreaCheck == true && !(player.getGlobalBounds().intersects(enemy03Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy03AreaTimeCount > 50) {
						enemy03AreaCheck = false;
						enemy03AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy03AreaTimeCount += 1;
				}

				if (AtkE3 == true) {
					//Q1
					if (playerPosition.x > enemyLV405Position.x && playerPosition.y < enemyLV405Position.y) {
						//printf("1\n");
						spBullE3Y = sqrt(100 / (pow(abs(enemyLV405Position.x - playerPosition.x) / abs(enemyLV405Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV405Position.x - playerPosition.x) / abs(enemyLV405Position.y - playerPosition.y)) * spBullE3Y;
						spBullE3Y = spBullE3Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV405Position.x && playerPosition.y < enemyLV405Position.y) {
						//printf("2\n");
						spBullE3Y = sqrt(100 / (pow(abs(enemyLV405Position.x - playerPosition.x) / abs(enemyLV405Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV405Position.x - playerPosition.x) / abs(enemyLV405Position.y - playerPosition.y)) * spBullE3Y;
						spBullE3X = spBullE3X * -1;
						spBullE3Y = spBullE3Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV405Position.x && playerPosition.y > enemyLV405Position.y) {

						//printf("3\n");
						spBullE3Y = sqrt(100 / (pow(abs(enemyLV405Position.x - playerPosition.x) / abs(enemyLV405Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV405Position.x - playerPosition.x) / abs(enemyLV405Position.y - playerPosition.y)) * spBullE3Y;
						spBullE3X = spBullE3X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV405Position.x && playerPosition.y > enemyLV405Position.y) {
						//printf("4\n");
						spBullE3Y = sqrt(100 / (pow(abs(enemyLV405Position.x - playerPosition.x) / abs(enemyLV405Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV405Position.x - playerPosition.x) / abs(enemyLV405Position.y - playerPosition.y)) * spBullE3Y;

					}
					AtkE3 = false;
					bullE3out = true;
					bulletE3.setPosition(enemyLV405Position.x + 50, enemyLV405Position.y + 50);
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV405.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV405Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV405Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV405.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV405Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV405Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV405.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV405Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV405Life);
				}
			}
			
		}
		if (n != 6) {
			bossFightSound.play();
		}
		if (n == 6) {
			//Level4 > > Democrac//
			backgroundSound.pause();
			if (DemocracLv4Col == false && player.getGlobalBounds().intersects(DemocracLV4.getGlobalBounds())) {
				DemocracLv4Col = true;
				winSound.play();
				bossFightSound.pause();
				std::string word;
				std::ifstream ReadFile("Score.txt");
				do {
					ReadFile >> word;
					std::string name = word.substr(0, word.find(','));
					float num = std::stof(word.substr(word.find(',') + 1, word.length()));
					vec.push_back(std::make_pair(name, num));
				} while (ReadFile.good());
				ReadFile.close();
				std::ofstream WriteFile("Score.txt");
				vec.push_back(std::make_pair(inputName, totalTime));
				std::sort(vec.begin(), vec.end(), sortbysecdesc);
				for (int i = 0; i < 5; i++)
				{
					WriteFile << vec[i].first << "," << vec[i].second << std::endl;
				}
				vec.clear();
				WriteFile.close();

			}

			// bullet collision //

			//Level 4 > > bullet > > Enemy3//

			if (enemyLV403Life > 0) {

				//DetectionZone&Attack//

					//printf("Chonlaew NAAAAA 2\n");
				enemy01AreaCheck = true;
				enemy01AreaTimeCount = 0;
				if (bullE1out == false) {
					bullE1TimeCount++;
					//printf("%d", bullE1TimeCount);
					if (bullE1TimeCount >= 25) {
						AtkE1 = true;
					}
				}


				if (bullet1.getGlobalBounds().intersects(enemyLV403.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV403.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV403.getGlobalBounds())) {
					enemy01AreaCheck = true;
				}

				if (enemy01AreaCheck == true && !(player.getGlobalBounds().intersects(enemy01Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy01AreaTimeCount > 50) {
						enemy01AreaCheck = false;
						enemy01AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy01AreaTimeCount += 1;
				}

				if (AtkE1 == true) {
					//Q1
					if (playerPosition.x > enemyLV403Position.x && playerPosition.y < enemyLV403Position.y) {
						//printf("1\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV403Position.x - playerPosition.x) / abs(enemyLV403Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV403Position.x - playerPosition.x) / abs(enemyLV403Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1Y = spBullE1Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV403Position.x && playerPosition.y < enemyLV403Position.y) {
						//printf("2\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV403Position.x - playerPosition.x) / abs(enemyLV403Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV403Position.x - playerPosition.x) / abs(enemyLV403Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1X = spBullE1X * -1;
						spBullE1Y = spBullE1Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV403Position.x && playerPosition.y > enemyLV403Position.y) {

						//printf("3\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV403Position.x - playerPosition.x) / abs(enemyLV403Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV403Position.x - playerPosition.x) / abs(enemyLV403Position.y - playerPosition.y)) * spBullE1Y;
						spBullE1X = spBullE1X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV403Position.x && playerPosition.y > enemyLV403Position.y) {
						//printf("4\n");
						spBullE1Y = sqrt(100 / (pow(abs(enemyLV403Position.x - playerPosition.x) / abs(enemyLV403Position.y - playerPosition.y), 2) + 1));
						spBullE1X = (abs(enemyLV403Position.x - playerPosition.x) / abs(enemyLV403Position.y - playerPosition.y)) * spBullE1Y;

					}
					AtkE1 = false;
					bullE1out = true;
					bulletE1.setPosition(enemyLV403Position.x + 50, enemyLV403Position.y + 50);
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV403.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV403Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV403Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV403.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV403Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV403Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV403.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV403Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV403Life);
				}
			}

			//Level 4 > > bullet > > Enemy4//

			if (enemyLV404Life > 0) {

				//DetectionZone&Attack//

					//printf("Chonlaew NAAAAA 2\n");
				enemy02AreaCheck = true;
				enemy02AreaTimeCount = 0;
				if (bullE2out == false) {
					bullE2TimeCount++;
					//printf("%d", bullE1TimeCount);
					if (bullE2TimeCount >= 25) {
						AtkE2 = true;
					}
				}


				if (bullet1.getGlobalBounds().intersects(enemyLV404.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV404.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV404.getGlobalBounds())) {
					enemy02AreaCheck = true;
				}

				if (enemy02AreaCheck == true && !(player.getGlobalBounds().intersects(enemy02Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy02AreaTimeCount > 50) {
						enemy02AreaCheck = false;
						enemy02AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy02AreaTimeCount += 1;
				}

				if (AtkE2 == true) {
					//Q1
					if (playerPosition.x > enemyLV404Position.x && playerPosition.y < enemyLV404Position.y) {
						//printf("1\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV404Position.x - playerPosition.x) / abs(enemyLV404Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV404Position.x - playerPosition.x) / abs(enemyLV404Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2Y = spBullE2Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV404Position.x && playerPosition.y < enemyLV404Position.y) {
						//printf("2\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV404Position.x - playerPosition.x) / abs(enemyLV404Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV404Position.x - playerPosition.x) / abs(enemyLV404Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2X = spBullE2X * -1;
						spBullE2Y = spBullE2Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV404Position.x && playerPosition.y > enemyLV404Position.y) {

						//printf("3\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV404Position.x - playerPosition.x) / abs(enemyLV404Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV404Position.x - playerPosition.x) / abs(enemyLV404Position.y - playerPosition.y)) * spBullE2Y;
						spBullE2X = spBullE2X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV404Position.x && playerPosition.y > enemyLV404Position.y) {
						//printf("4\n");
						spBullE2Y = sqrt(100 / (pow(abs(enemyLV404Position.x - playerPosition.x) / abs(enemyLV404Position.y - playerPosition.y), 2) + 1));
						spBullE2X = (abs(enemyLV404Position.x - playerPosition.x) / abs(enemyLV404Position.y - playerPosition.y)) * spBullE2Y;

					}
					AtkE2 = false;
					bullE2out = true;
					bulletE2.setPosition(enemyLV404Position.x + 50, enemyLV404Position.y + 50);
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV404.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV404Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV404Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV404.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV404Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV404Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV404.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV404Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV404Life);
				}
			}

			//Level 4 > > bullet > > Enemy6//

			if (enemyLV406Life > 0) {
				Enemy3Shadow.setScale(Shadow3Scale.x * 3, Shadow3Scale.y * 3);
				//DetectionZone&Attack//

				enemy03AreaCheck = true;
				enemy03AreaTimeCount = 0;
				if (bullE3out == false) {
					bulletE3.setSize(sf::Vector2f(20.0f, 20.0f));
					bulletE3.setOrigin(10, 10);
					bullE3TimeCount++;
					//printf("%d", bullE1TimeCount);
					if (bullE3TimeCount >= 25) {
						AtkE3 = true;
					}
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV406.getGlobalBounds())
					|| bullet2.getGlobalBounds().intersects(enemyLV406.getGlobalBounds())
					|| bullet3.getGlobalBounds().intersects(enemyLV406.getGlobalBounds())) {
					enemy03AreaCheck = true;
				}

				if (enemy03AreaCheck == true && !(player.getGlobalBounds().intersects(enemy03Area.getGlobalBounds()))) {
					//printf("%d\n", enemy01AreaTimeCount);
					if (enemy03AreaTimeCount > 50) {
						enemy03AreaCheck = false;
						enemy03AreaTimeCount = 0;
						//printf("maichonlaew 2\n");
					}
					enemy03AreaTimeCount += 1;
				}

				if (AtkE3 == true) {
					//Q1
					if (playerPosition.x > enemyLV406Position.x && playerPosition.y < enemyLV406Position.y) {
						//printf("1\n");
						spBullE3Y = sqrt(225 / (pow(abs(enemyLV406Position.x - playerPosition.x) / abs(enemyLV406Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV406Position.x - playerPosition.x) / abs(enemyLV406Position.y - playerPosition.y)) * spBullE3Y;
						spBullE3Y = spBullE3Y * -1;
					}
					//Q2
					else if (playerPosition.x < enemyLV406Position.x && playerPosition.y < enemyLV406Position.y) {
						//printf("2\n");
						spBullE3Y = sqrt(225 / (pow(abs(enemyLV406Position.x - playerPosition.x) / abs(enemyLV406Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV406Position.x - playerPosition.x) / abs(enemyLV406Position.y - playerPosition.y)) * spBullE3Y;
						spBullE3X = spBullE3X * -1;
						spBullE3Y = spBullE3Y * -1;
					}
					//Q3
					else if (playerPosition.x < enemyLV406Position.x && playerPosition.y > enemyLV406Position.y) {

						//printf("3\n");
						spBullE3Y = sqrt(225 / (pow(abs(enemyLV406Position.x - playerPosition.x) / abs(enemyLV406Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV406Position.x - playerPosition.x) / abs(enemyLV406Position.y - playerPosition.y)) * spBullE3Y;
						spBullE3X = spBullE3X * -1;

					}
					//Q4
					else if (playerPosition.x > enemyLV406Position.x && playerPosition.y > enemyLV406Position.y) {
						//printf("4\n");
						spBullE3Y = sqrt(225 / (pow(abs(enemyLV406Position.x - playerPosition.x) / abs(enemyLV406Position.y - playerPosition.y), 2) + 1));
						spBullE3X = (abs(enemyLV406Position.x - playerPosition.x) / abs(enemyLV406Position.y - playerPosition.y)) * spBullE3Y;

					}
					AtkE3 = false;
					bullE3out = true;
					bulletE3.setSize(sf::Vector2f(150.0f, 150.0f));
					bulletE3.setOrigin(75, 75);
					bulletE3.setPosition(enemyLV406Position.x + 150, enemyLV406Position.y + 150);
					animateBoss = true;
				}

				if (bullet1.getGlobalBounds().intersects(enemyLV406.getGlobalBounds())) {
					bull1out = false;
					bull1Col = false;
					bulletNo[0] = 0;
					bulletTimeOut[0] = 0;
					bullet1.setPosition(0, 0);
					enemyLV406Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV406Life);
				}
				if (bullet2.getGlobalBounds().intersects(enemyLV406.getGlobalBounds())) {
					bull2out = false;
					bull2Col = false;
					bulletNo[1] = 0;
					bulletTimeOut[1] = 0;
					bullet2.setPosition(0, 0);
					enemyLV406Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV406Life);
				}
				if (bullet3.getGlobalBounds().intersects(enemyLV406.getGlobalBounds())) {
					bull3out = false;
					bull3Col = false;
					bulletNo[2] = 0;
					bulletTimeOut[2] = 0;
					bullet3.setPosition(0, 0);
					enemyLV406Life -= 1;
					printf("hit - enemyLife = %d\n", enemyLV406Life);
				}
			}
		}

		// ---------------------------------Keyboard&MouseInput------------------------------------// 
		//printf("%d\n",n);
		if (n == 10 && mouseColStart == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//Random LEVEL//
			//myfile << intName;
			///*highscore = fopen("Score.txt", "a");
			//fprintf(highscore, "%s\n", intName);*/
			int num = (rand() % (5 - 1 + 1)) + 1;
			Stage[StageCount] = num;
			StageCount += 1;
			n = num;
			timerload = true;
		}

		if (n == 10 && mouseColMainmenu == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			n = 0;
		}

		if (n == 0 && mouseColStart == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//Random LEVEL//
			n = 10;
			inputName.clear();
			Start.setPosition(620, 360);
		}


		if (n==10&&event.type == sf::Event::TextEntered) {
			
			delay(100);
			if (event.text.unicode < 128 && inputName.getSize() < 5) {

				inputName += event.text.unicode;
			}
			else if (event.text.unicode == 8)//backspace
			{
				inputName = inputName.substring(0, inputName.getSize() - 1);
			}
				delay(100);
				////std::string intName = inputName;
				//inputName.operator std::string = 
				//strcpy(intName, &(inputName.operator std::string).c_str());
				//NameCount += 1;
				//printf("%d\n", event.text.unicode);
				Name.setString("Enter name : ____");
				
				Name.setString("Enter name : " + inputName);
		}
		

		if (n == 0 && mouseColExit == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			window.close();
		}

		if (n == 0 && mouseColLeaderboard == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			n = 99;
			std::string word;
			std::ifstream ReadFile("Score.txt");
			do {
				ReadFile >> word;
				std::string name = word.substr(0, word.find(','));
				float num = std::stof(word.substr(word.find(',') + 1, word.length()));
				vec.push_back(std::make_pair(name, num));
			} while (ReadFile.good());
			ReadFile.close();
			std::sort(vec.begin(), vec.end(), sortbysecdesc);
			for (int i = 0; i < 5; i++)
			{
				text[2 * i + 2].setString(std::to_string(i + 1) + ". " + vec[i].first);
				text[2 * i + 3].setString(std::to_string(vec[i].second));
			}
			vec.clear();
		}
		
		int initialFrame = 0;

		if (speedStatus == true) {
			speedTimeCount++;
			//printf("speedTimeCount : %d \n", speedTimeCount);
		}
		if (speedTimeCount > 250) {
			speedStatus = false;
		}

		if (KeyD == true) {

			initialFrame = 3;
		}
		else if (KeyA == true) {
			initialFrame = 1;
		}
		else if (KeyW == true) {
			initialFrame = 0;
		}
		else if (KeyS == true) {
			initialFrame = 2;
		}
		player.setTextureRect(sf::IntRect(playerSizeX * 0, playerSizeY * initialFrame, playerSizeX, playerSizeY));

		
		if (d == true) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				if (speedStatus == false) {
					player.move(4.5f, 0.0f);
				}
				else{
					player.move(10.0f, 0.0f);
				}
				player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 11, playerSizeX, playerSizeY));
				//printf("Keypress : D\n");
				KeyW = false;
				KeyA = false;
				KeyS = false;
				KeyD = true;

			}
		}
		if (a == true) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				if (speedStatus == false) {
					player.move(-4.5f, 0.0f);
				}
				else {
					player.move(-10.0f, 0.0f);
				}
				player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 9, playerSizeX, playerSizeY));
				//printf("Keypress : A\n");
				KeyW = false;
				KeyA = true;
				KeyS = false;
				KeyD = false;
			}
		}
		if (w == true) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				if (speedStatus == false) {
					player.move(0.0f, -4.5f);
				}
				else {
					player.move(0.0f, -10.0f);
				}
				player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 8, playerSizeX, playerSizeY));
				//printf("Keypress : W\n");
				KeyW = true;
				KeyA = false;
				KeyS = false;
				KeyD = false;
			}
		}
		if (s == true) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if (speedStatus == false) {
					player.move(0.0f, 4.5f);
				}
				else {
					player.move(0.0f, 10.0f);
				}
				player.setTextureRect(sf::IntRect(playerSizeX * animationFrame, playerSizeY * 10, playerSizeX, playerSizeY));
				//printf("Keypress : S\n");
				KeyW = false;
				KeyA = false;
				KeyS = true;
				KeyD = false;
			}
		}

		if (bullOrder > 2) {
			bullOrder = 0;
			//if (spaceEnable >= 30) {
			spaceEnable = 0;
			//}
		}
		
		if (bulletTimeOut[0] >= 30) {
			bulletTimeOut[0] = 0;
			bull1out = false;
			bull1Col = false;
			bulletNo[0] = 0;

			bullet1.setPosition(0, 0);
		}
		if (bulletTimeOut[1] >= 30) {
			bulletTimeOut[1] = 0;
			bull2out = false;
			bull2Col = false;
			bulletNo[1] = 0;

			bullet1.setPosition(0, 0);
		}
		if (bulletTimeOut[2] >= 30) {
			bulletTimeOut[2] = 0;
			bull3out = false;
			bull3Col = false;
			bulletNo[2] = 0;

			bullet1.setPosition(0, 0);
		}
		if (spaceCheck == false) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				shootSound.play();
				spaceEnable += 1;
				spaceCheck = true;
				//printf("Keypress : Space %d\n", spaceEnable);
			}
		}

		if (spaceCheck == true) {
			skillFrame++;
			player.setTextureRect(sf::IntRect(playerSizeX * skillFrame, playerSizeY * 2, playerSizeX, playerSizeY));
			delay(40);
			
			if (skillFrame >= 6) {
				skillFrame = 0;
				spaceCheck = false;
				if ((bull1Col == false && bulletNo[0] == 0) || (bull2Col == false&&bulletNo[1] == 0) || (bull3Col == false&&bulletNo[2] == 0)) {
					//bulletNo[bullOrder] = 1;
					switch (bullOrder) {
					case 0: {bull1State = true; bullet1.setPosition(playerPosition.x + 50, playerPosition.y + 60); break; }
					case 1: {bull2State = true; bullet2.setPosition(playerPosition.x + 50, playerPosition.y + 60); break; }
					case 2: {bull3State = true; bullet3.setPosition(playerPosition.x + 50, playerPosition.y + 60); break; }
					}
					
					bullOrder++;
					
				}
				continue;
			}

		}
		else {
			animationFrame++;
			delay(40);
			if (animationFrame >= 9) {
				animationFrame = 0;
			}
		}



		//--------------------------------------Bullet 1------------------------------------------//
		
		if (bull1State == true && bulletNo[0] == 0) {
			if (bull1Col == false) {
				//Q1
				if (hitBox.x > playerPosition.x && hitBox.y < playerPosition.y) {
					//printf("1\n");
					spBull1Y = sqrt(625 / (pow(abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y), 2) + 1));
					spBull1X = (abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y)) * spBull1Y;
					spBull1Y = spBull1Y * -1;
				}
				//Q2
				else if (hitBox.x < playerPosition.x && hitBox.y < playerPosition.y) {
					//printf("2\n");
					spBull1Y = sqrt(625 / (pow(abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y), 2) + 1));
					spBull1X = (abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y)) * spBull1Y;
					spBull1X = spBull1X * -1;
					spBull1Y = spBull1Y * -1;
				}
				//Q3
				else if (hitBox.x < playerPosition.x && hitBox.y > playerPosition.y) {

					//printf("3\n");
					spBull1Y = sqrt(625 / (pow(abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y), 2) + 1));
					spBull1X = (abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y)) * spBull1Y;
					spBull1X = spBull1X * -1;

				}
				//Q4
				else if (hitBox.x > playerPosition.x && hitBox.y > playerPosition.y) {
					//printf("4\n");
					spBull1Y = sqrt(625 / (pow(abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y), 2) + 1));
					spBull1X = (abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y)) * spBull1Y;

				}
				bullet1.setPosition(playerPosition.x + 50, playerPosition.y + 50);
			}
				bull1Col = true;
				bull1out = true;
				bull1State = false;
				bulletNo[0] = 1;
			
		}
			//printf("X %f\nY %f", spBull1X, spBull1Y);
		if (bulletNo[0] == 1) {
			bullet1.move(spBull1X, spBull1Y);
			bulletTimeOut[0]++;
		}
		//printf("bulletNO[0] = %d\n", bulletNo[0]);
	
		

		//--------------------------------------Bullet 2------------------------------------------//

		
		if (bull2State == true && bulletNo[1] == 0) {
			if (bull2Col == false) {
				//Q1
				if (hitBox.x > playerPosition.x && hitBox.y < playerPosition.y) {
					//printf("1\n");
					spBull2Y = sqrt(625 / (pow(abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y), 2) + 1));
					spBull2X = (abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y)) * spBull2Y;
					spBull2Y = spBull2Y * -1;
				}
				//Q2
				else if (hitBox.x < playerPosition.x && hitBox.y < playerPosition.y) {
					//printf("2\n");
					spBull2Y = sqrt(625 / (pow(abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y), 2) + 1));
					spBull2X = (abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y)) * spBull2Y;
					spBull2X = spBull2X * -1;
					spBull2Y = spBull2Y * -1;
				}
				//Q3
				else if (hitBox.x < playerPosition.x && hitBox.y > playerPosition.y) {

					//printf("3\n");
					spBull2Y = sqrt(625 / (pow(abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y), 2) + 1));
					spBull2X = (abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y)) * spBull2Y;
					spBull2X = spBull2X * -1;

				}
				//Q4
				else if (hitBox.x > playerPosition.x && hitBox.y > playerPosition.y) {
					//printf("4\n");
					spBull2Y = sqrt(625 / (pow(abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y), 2) + 1));
					spBull2X = (abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y)) * spBull2Y;

				}
				bullet2.setPosition(playerPosition.x + 50, playerPosition.y + 50);
			}
				bull2Col = true;
				bull2out = true;
				bull2State = false;
				bulletNo[1] = 1;
		}

		if (bulletNo[1] == 1) {
			bulletTimeOut[1]++;
			bullet2.move(spBull2X, spBull2Y);
		}

		//--------------------------------------Bullet 3------------------------------------------//

		
		if (bull3State == true && bulletNo[2] == 0) {
			if (bull3Col == false) {
				//Q1
				if (hitBox.x > playerPosition.x && hitBox.y < playerPosition.y) {
					//printf("1\n");
					spBull3Y = sqrt(625 / (pow(abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y), 2) + 1));
					spBull3X = (abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y)) * spBull3Y;
					spBull3Y = spBull3Y * -1;
				}
				//Q2
				else if (hitBox.x < playerPosition.x && hitBox.y < playerPosition.y) {
					//printf("2\n");
					spBull3Y = sqrt(625 / (pow(abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y), 2) + 1));
					spBull3X = (abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y)) * spBull3Y;
					spBull3X = spBull3X * -1;
					spBull3Y = spBull3Y * -1;
				}
				//Q3
				else if (hitBox.x < playerPosition.x && hitBox.y > playerPosition.y) {

					//printf("3\n");
					spBull3Y = sqrt(625 / (pow(abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y), 2) + 1));
					spBull3X = (abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y)) * spBull3Y;
					spBull3X = spBull3X * -1;

				}
				//Q4
				else if (hitBox.x > playerPosition.x && hitBox.y > playerPosition.y) {
					//printf("4\n");
					spBull3Y = sqrt(625 / (pow(abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y), 2) + 1));
					spBull3X = (abs(playerPosition.x - hitBox.x) / abs(playerPosition.y - hitBox.y)) * spBull3Y;

				}
				bullet3.setPosition(playerPosition.x + 50, playerPosition.y + 50);
			}
				bull3Col = true;
				bull3out = true;
				bull3State = false;
				bulletNo[2] = 1;
			
		}
		if (bulletNo[2] == 1) {
			bulletTimeOut[2]++;
			bullet3.move(spBull2X, spBull2Y);
		}
		
		//--------------------------------------ENEMY BULLET---------------------------------------------//

		if (bullE1out == true) {
			bulletE1.move(spBullE1X, spBullE1Y);
		}

		if (bullE2out == true) {
			bulletE2.move(spBullE2X, spBullE2Y);
		}

		if (bullE3out == true) {
			bulletE3.move(spBullE3X, spBullE3Y);
		}
		
		//printf("Bulleet Col1 %d\nBulleet Col2 %d\nBulleet Col3 %d\n", bull1Col, bull2Col, bull3Col);
		//--------------------------------------Democrac LEVEL1------------------------------------------//

		DemocracLV1.setTextureRect(sf::IntRect(democracSizeX * animateDemocracFrame, democracSizeY * 0, democracSizeX, democracSizeY));
		animateDemocracFrame++;

		if (animateDemocracFrame > 6) {
			animateDemocracFrame=0;
		}

		//--------------------------------------Democrac LEVEL2------------------------------------------//

		DemocracLV2.setTextureRect(sf::IntRect(democracLV2SizeX* animateDemocracLV2Frame, democracLV2SizeY * 0, democracLV2SizeX, democracLV2SizeY));
		animateDemocracLV2Frame++;

		if (animateDemocracLV2Frame > 7) {
			animateDemocracLV2Frame = 0;
		}

		//--------------------------------------Democrac LEVEL3------------------------------------------//

		DemocracLV3.setTextureRect(sf::IntRect(democracLV3SizeX* animateDemocracLV3Frame, democracLV3SizeY * 0, democracLV3SizeX, democracLV3SizeY));
		animateDemocracLV3Frame++;

		if (animateDemocracLV3Frame > 5) {
			animateDemocracLV3Frame = 0;
		}

		//--------------------------------------Democrac LEVEL4------------------------------------------//

		DemocracLV4.setTextureRect(sf::IntRect(democracLV4SizeX* animateDemocracLV4Frame, democracLV4SizeY * 0, democracLV4SizeX, democracLV4SizeY));
		animateDemocracLV4Frame++;

		if (animateDemocracLV4Frame > 8) {
			animateDemocracLV4Frame = 0;
		}

		//--------------------------------------Gate LEVEL2------------------------------------------//

		GateLV2.setTextureRect(sf::IntRect(GateLV2SizeX * animateGateLV2Frame, GateLV2SizeY * 0, GateLV2SizeX, GateLV2SizeY));
		animateGateLV2Frame++;

		if (animateGateLV2Frame >= 8) {
			animateGateLV2Frame = 0;
		}
		//--------------------------------------Gate LEVEL4------------------------------------------//

		GateLV4.setTextureRect(sf::IntRect(GateLV4SizeX* animateGateLV4Frame, GateLV4SizeY * 0, GateLV4SizeX, GateLV4SizeY));
		animateGateLV4Frame++;

		if (animateGateLV4Frame >= 8) {
			animateGateLV4Frame = 0;
		}

		//--------------------------------------Key LEVEL1------------------------------------------//

		KeyLV1.setTextureRect(sf::IntRect(KeyLV1SizeX* animateKeyLV1Frame, KeyLV1SizeY * 0, KeyLV1SizeX, KeyLV1SizeY));
		animateKeyLV1Frame++;

		if (animateKeyLV1Frame >= 13) {
			animateKeyLV1Frame = 0;
		}
		KeyLV1.rotate(10.0f);

		//--------------------------------------Key LEVEL2------------------------------------------//

		KeyLV2.setTextureRect(sf::IntRect(KeyLV2SizeX * animateKeyLV2Frame, KeyLV2SizeY * 0, KeyLV2SizeX, KeyLV2SizeY));
		animateKeyLV2Frame++;

		if (animateKeyLV2Frame >= 13) {
			animateKeyLV2Frame = 0;
		}
		KeyLV2.rotate(10.0f);
		
		//--------------------------------------Key LEVEL4------------------------------------------//

		KeyLV4.setTextureRect(sf::IntRect(KeyLV4SizeX* animateKeyLV4Frame, KeyLV4SizeY * 0, KeyLV4SizeX, KeyLV4SizeY));
		animateKeyLV4Frame++;

		if (animateKeyLV4Frame >= 13) {
			animateKeyLV4Frame = 0;
		}
		KeyLV4.rotate(10.0f);


		//--------------------------------------Shield LEVEL1------------------------------------------//

		shield.setTextureRect(sf::IntRect(shieldSizeX* shieldAnimateFrame, shieldSizeY * 0, shieldSizeX, shieldSizeY));
		shieldAnimateFrame++;

		if (shieldAnimateFrame >= 15) {
			shieldAnimateFrame = 0;
		}
		//shield.rotate(10.0f);

		//--------------------------------------Speed LEVEL2------------------------------------------//

		speed.setTextureRect(sf::IntRect(speedSizeX* speedanimateFrame, speedSizeY * 0, speedSizeX, speedSizeY));
		if (speedanimateTimeCount >= 20) {
			speedanimateFrame++;
			speedanimateTimeCount = 0;
		}
		else {
			speedanimateTimeCount++;
		}
		if (speedanimateFrame >= 4) {
			speedanimateFrame = 0;
		}

		//--------------------------------------Life Item LEVEL2------------------------------------------//
		
		lifeAnimateTimeDelay++;
		if (lifeAnimateTimeDelay < 25) {
			life.move(0.0f, 1.0f);
		}
		if (lifeAnimateTimeDelay >= 25 && lifeAnimateTimeDelay < 50) {
			life.move(0.0f, -1.0f);
		}
		if (lifeAnimateTimeDelay > 50) {
			lifeAnimateTimeDelay = 0;
		}

		//--------------------------------------Imortal LEVEL4------------------------------------------//

		ImortalPot.setTextureRect(sf::IntRect(ImortalSizeX * animateImortalFrame, ImortalSizeY * 0, ImortalSizeX, ImortalSizeY));
		animateImortalFrame++;
		animateImortalTimeCount++;
		if (animateImortalTimeCount < 25) {
			ImortalPot.move(0.0f, 1.0f);
		}
		if (animateImortalTimeCount > 25 && animateImortalTimeCount < 50) {
			ImortalPot.move(0.0f, -1.0f);
		}
		if (animateImortalTimeCount >= 50) {
			animateImortalTimeCount = 0;
		}
		if (animateImortalFrame >= 7) {
			animateImortalFrame = 0;
		}

		//--------------------------------------ENEMY LEVEL1------------------------------------------//



		//**********enemy01 animation**********//

		enemy01.move(enemyPosX, 0.0f);
		enemy01.setTextureRect(sf::IntRect(enemy01SizeX * enemy01FrameX, enemy01SizeY * enemy01FrameY, enemy01SizeX, enemy01SizeY));
		enemy01FrameX++;
		if (enemy01FrameX >= 9) {
			enemy01FrameX = 0;
		}

		//Check Enemy 01 Position//
		//ประกาศนอก loop enemyMaxX = 0, enemyPosX = 0
		if (enemyMaxX < 100) {  //เดินไปทางซ้ายโดยให้ enemyPosX = -4.5 ใช้ในบรรทัด2669 แล้วเพิ่มค่า enemyMaxX ทีละ 15ถ้าถึง 100 แล้วไปทำ else if ต่อ
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
		
		enemy01Heart1.setPosition(enemy01Position.x + 25, enemy01Position.y-10);
		enemy01Heart2.setPosition(enemy01Position.x + 50, enemy01Position.y-10);
		enemy01Heart3.setPosition(enemy01Position.x + 75, enemy01Position.y-10);
		

		//**********enemy02 animation**********//

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
		
		enemy02Heart1.setPosition(enemy02Position.x + 25, enemy02Position.y - 10);
		enemy02Heart2.setPosition(enemy02Position.x + 50, enemy02Position.y - 10);
		enemy02Heart3.setPosition(enemy02Position.x + 75, enemy02Position.y - 10);
		

		//--------------------------------------ENEMY LEVEL2------------------------------------------//



		//**********enemy01 animation**********//

		enemyLV201.move(enemyLV201PosX, 0.0f);
		enemyLV201.setTextureRect(sf::IntRect(enemyLV201SizeX * enemyLV201FrameX, enemyLV201SizeY * enemyLV201FrameY, enemyLV201SizeX, enemyLV201SizeY));
		enemyLV201FrameX++;
		if (enemyLV201FrameX >= 9) {
			enemyLV201FrameX = 0;
		}

		//Check Enemy 01 Position//

		if (enemyLV201MaxX < 100) {
			enemyLV201PosX = -4.5;
			enemyLV201MaxX++;
		}
		else if (enemyLV201MaxX >= 100 && enemyLV201MaxX < 200) {
			enemyLV201FrameY = 11;
			enemyLV201PosX = 4.5;
			enemyLV201MaxX++;
		}
		else {
			enemyLV201MaxX = 0;
			enemyLV201PosX = 0;
			enemyLV201FrameY = 9;
		}
		
		enemy201Heart1.setPosition(enemyLV201Position.x + 25, enemyLV201Position.y - 10);
		enemy201Heart2.setPosition(enemyLV201Position.x + 50, enemyLV201Position.y - 10);
		enemy201Heart3.setPosition(enemyLV201Position.x + 75, enemyLV201Position.y - 10);

		//**********enemy02 animation**********//

		enemyLV202.move(enemyLV202PosX, 0.0f);
		enemyLV202.setTextureRect(sf::IntRect(enemyLV202SizeX* enemyLV202FrameX, enemyLV202SizeY* enemyLV202FrameY, enemyLV202SizeX, enemyLV202SizeY));
		enemyLV202FrameX++;
		if (enemyLV202FrameX >= 9) {
			enemyLV202FrameX = 0;
		}

		//Check Enemy 02 Position//

		if (enemyLV202MaxX < 200) {
			enemyLV202PosX = -4.5;
			enemyLV202MaxX++;
		}
		else if (enemyLV202MaxX >= 200 && enemyLV202MaxX < 400) {
			enemyLV202FrameY = 11;
			enemyLV202PosX = 4.5;
			enemyLV202MaxX++;
		}
		else {
			enemyLV202MaxX = 0;
			enemyLV202PosX = 0;
			enemyLV202FrameY = 9;
		}
		
		enemy202Heart1.setPosition(enemyLV202Position.x + 25, enemyLV202Position.y - 10);
		enemy202Heart2.setPosition(enemyLV202Position.x + 50, enemyLV202Position.y - 10);
		enemy202Heart3.setPosition(enemyLV202Position.x + 75, enemyLV202Position.y - 10);

		//**********enemy03 animation**********//

		enemyLV203.move(0.0f,enemyLV203PosY);
		enemyLV203.setTextureRect(sf::IntRect(enemyLV203SizeX* enemyLV203FrameX, enemyLV203SizeY* enemyLV203FrameY, enemyLV203SizeX, enemyLV203SizeY));
		enemyLV203FrameX++;
		if (enemyLV203FrameX >= 9) {
			enemyLV203FrameX = 0;
		}

		//Check Enemy 03 Position//

		if (enemyLV203MaxY < 100) {
			enemyLV203PosY = -4.5;
			enemyLV203MaxY++;
		}
		else if (enemyLV203MaxY >= 100 && enemyLV203MaxY < 200) {
			enemyLV203FrameY = 10;
			enemyLV203PosY = 4.5;
			enemyLV203MaxY++;
		}
		else {
			enemyLV203MaxY = 0;
			enemyLV203PosY = 0;
			enemyLV203FrameY = 8;
		}

		enemy203Heart1.setPosition(enemyLV203Position.x + 25, enemyLV203Position.y - 10);
		enemy203Heart2.setPosition(enemyLV203Position.x + 50, enemyLV203Position.y - 10);
		enemy203Heart3.setPosition(enemyLV203Position.x + 75, enemyLV203Position.y - 10);

		//**********enemy04 animation**********//

		enemyLV204.move(0.0f, enemyLV204PosY);
		enemyLV204.setTextureRect(sf::IntRect(enemyLV204SizeX* enemyLV204FrameX, enemyLV204SizeY* enemyLV204FrameY, enemyLV204SizeX, enemyLV204SizeY));
		enemyLV204FrameX++;
		if (enemyLV204FrameX >= 9) {
			enemyLV204FrameX = 0;
		}

		//Check Enemy 04 Position//

		if (enemyLV204MaxY < 100) {
			enemyLV204PosY = 4.5;
			enemyLV204MaxY++;
		}
		else if (enemyLV204MaxY >= 100 && enemyLV204MaxY < 200) {
			enemyLV204FrameY = 8;
			enemyLV204PosY = -4.5;
			enemyLV204MaxY++;
		}
		else {
			enemyLV204MaxY = 0;
			enemyLV204PosY = 0;
			enemyLV204FrameY = 10;
		}
		
		enemy204Heart1.setPosition(enemyLV204Position.x + 25, enemyLV204Position.y - 10);
		enemy204Heart2.setPosition(enemyLV204Position.x + 50, enemyLV204Position.y - 10);
		enemy204Heart3.setPosition(enemyLV204Position.x + 75, enemyLV204Position.y - 10);

		//**********enemy05 animation**********//

		enemyLV205.move(enemyLV205PosX, 0.0f);
		enemyLV205.setTextureRect(sf::IntRect(enemyLV205SizeX * enemyLV205FrameX, enemyLV205SizeY * enemyLV205FrameY, enemyLV205SizeX, enemyLV205SizeY));
		enemyLV205FrameX++;
		if (enemyLV205FrameX >= 9) {
			enemyLV205FrameX = 0;
		}

		//Check Enemy 01 Position//
		if (enemyLV205MaxX < 100) { 
			enemyLV205PosX = -4.5;
			enemyLV205MaxX++;
		}
		else if (enemyLV205MaxX >= 100 && enemyLV205MaxX < 200) {
			enemyLV205FrameY = 11;
			enemyLV205PosX = 4.5;
			enemyLV205MaxX++;
		}
		else {
			enemyLV205MaxX = 0;
			enemyLV205PosX = 0;
			enemyLV205FrameY = 9;
		}

		enemy205Heart1.setPosition(enemyLV205Position.x + 25, enemyLV205Position.y - 10);
		enemy205Heart2.setPosition(enemyLV205Position.x + 50, enemyLV205Position.y - 10);
		enemy205Heart3.setPosition(enemyLV205Position.x + 75, enemyLV205Position.y - 10);

		//--------------------------------------ENEMY LEVEL3------------------------------------------//



		//**********enemy01 animation**********//

		enemyLV301.move(enemyLV301PosX, 0.0f);
		enemyLV301.setTextureRect(sf::IntRect(enemyLV301SizeX * enemyLV301FrameX, enemyLV301SizeY * enemyLV301FrameY, enemyLV301SizeX, enemyLV301SizeY));
		enemyLV301FrameX++;
		if (enemyLV301FrameX >= 9) {
			enemyLV301FrameX = 0;
		}

		//Check Enemy 01 Position//

		if (enemyLV301MaxX < 100) {
			enemyLV301PosX = -4.5;
			enemyLV301MaxX++;
		}
		else if (enemyLV301MaxX >= 100 && enemyLV301MaxX < 200) {
			enemyLV301FrameY = 11;
			enemyLV301PosX = 4.5;
			enemyLV301MaxX++;
		}
		else {
			enemyLV301MaxX = 0;
			enemyLV301PosX = 0;
			enemyLV301FrameY = 9;
		}
		enemy301Heart1.setPosition(enemyLV301Position.x + 25, enemyLV301Position.y - 10);
		enemy301Heart2.setPosition(enemyLV301Position.x + 50, enemyLV301Position.y - 10);
		enemy301Heart3.setPosition(enemyLV301Position.x + 75, enemyLV301Position.y - 10);

		//**********enemy02 animation**********//

		enemyLV302.move(0.0f, enemyLV302PosY);
		enemyLV302.setTextureRect(sf::IntRect(enemyLV302SizeX* enemyLV302FrameX, enemyLV302SizeY* enemyLV302FrameY, enemyLV302SizeX, enemyLV302SizeY));
		enemyLV302FrameX++;
		if (enemyLV302FrameX >= 9) {
			enemyLV302FrameX = 0;
		}

		//Check Enemy 02 Position//

		if (enemyLV302MaxY < 100) {
			enemyLV302PosY = -4.5;
			enemyLV302MaxY++;
		}
		else if (enemyLV302MaxY >= 100 && enemyLV302MaxY < 200) {
			enemyLV302FrameY = 10;
			enemyLV302PosY = 4.5;
			enemyLV302MaxY++;
		}
		else {
			enemyLV302MaxY = 0;
			enemyLV302PosY = 0;
			enemyLV302FrameY = 8;
		}
		
		enemy302Heart1.setPosition(enemyLV302Position.x + 25, enemyLV302Position.y - 10);
		enemy302Heart2.setPosition(enemyLV302Position.x + 50, enemyLV302Position.y - 10);
		enemy302Heart3.setPosition(enemyLV302Position.x + 75, enemyLV302Position.y - 10);


		//**********enemy03 animation**********//

		enemyLV303.move(0.0f, enemyLV303PosY);
		enemyLV303.setTextureRect(sf::IntRect(enemyLV303SizeX* enemyLV303FrameX, enemyLV303SizeY* enemyLV303FrameY, enemyLV303SizeX, enemyLV303SizeY));
		enemyLV303FrameX++;
		if (enemyLV303FrameX >= 9) {
			enemyLV303FrameX = 0;
		}

		//Check Enemy 03 Position//

		if (enemyLV303MaxY < 25) {
			enemyLV303PosY = -4.5;
			enemyLV303MaxY++;
		}
		else if (enemyLV303MaxY >= 25 && enemyLV303MaxY < 50) {
			enemyLV303FrameY = 10;
			enemyLV303PosY = 4.5;
			enemyLV303MaxY++;
		}
		else {
			enemyLV303MaxY = 0;
			enemyLV303PosY = 0;
			enemyLV303FrameY = 8;
		}
		

		enemy303Heart1.setPosition(enemyLV303Position.x + 25, enemyLV303Position.y - 10);
		enemy303Heart2.setPosition(enemyLV303Position.x + 50, enemyLV303Position.y - 10);
		enemy303Heart3.setPosition(enemyLV303Position.x + 75, enemyLV303Position.y - 10);

		//--------------------------------------ENEMY LEVEL4------------------------------------------//


		//**********enemy01 animation**********//

		enemyLV401.move(enemyLV401PosX, 0.0f);
		enemyLV401.setTextureRect(sf::IntRect(enemyLV401SizeX* enemyLV401FrameX, enemyLV401SizeY* enemyLV401FrameY, enemyLV401SizeX, enemyLV401SizeY));
		enemyLV401FrameX++;
		if (enemyLV401FrameX >= 9) {
			enemyLV401FrameX = 0;
		}

		//Check Enemy 01 Position//

		if (enemyLV401MaxX < 100) {
			enemyLV401PosX = -4.5;
			enemyLV401MaxX++;
		}
		else if (enemyLV401MaxX >= 100 && enemyLV401MaxX < 200) {
			enemyLV401FrameY = 11;
			enemyLV401PosX = 4.5;
			enemyLV401MaxX++;
		}
		else {
			enemyLV401MaxX = 0;
			enemyLV401PosX = 0;
			enemyLV401FrameY = 9;
		}
		

		enemy401Heart1.setPosition(enemyLV401Position.x + 25, enemyLV401Position.y - 10);
		enemy401Heart2.setPosition(enemyLV401Position.x + 50, enemyLV401Position.y - 10);
		enemy401Heart3.setPosition(enemyLV401Position.x + 75, enemyLV401Position.y - 10);

		//**********enemy02 animation**********//

		enemyLV402.move(0.0f, enemyLV402PosY);
		enemyLV402.setTextureRect(sf::IntRect(enemyLV402SizeX* enemyLV402FrameX, enemyLV402SizeY* enemyLV402FrameY, enemyLV402SizeX, enemyLV402SizeY));
		enemyLV402FrameX++;
		if (enemyLV402FrameX >= 9) {
			enemyLV402FrameX = 0;
		}

		//Check Enemy 02 Position//

		if (enemyLV402MaxY < 80) {
			enemyLV402PosY = -4.5;
			enemyLV402MaxY++;
		}
		else if (enemyLV402MaxY >= 80 && enemyLV402MaxY < 160) {
			enemyLV402FrameY = 10;
			enemyLV402PosY = 4.5;
			enemyLV402MaxY++;
		}
		else {
			enemyLV402MaxY = 0;
			enemyLV402PosY = 0;
			enemyLV402FrameY = 8;
		}

		enemy402Heart1.setPosition(enemyLV402Position.x + 25, enemyLV402Position.y - 10);
		enemy402Heart2.setPosition(enemyLV402Position.x + 50, enemyLV402Position.y - 10);
		enemy402Heart3.setPosition(enemyLV402Position.x + 75, enemyLV402Position.y - 10);
		

		//**********enemy03 animation**********//

		enemyLV403.move(0.0f, enemyLV403PosY);
		enemyLV403.setTextureRect(sf::IntRect(enemyLV403SizeX * enemyLV403FrameX, enemyLV403SizeY * enemyLV403FrameY, enemyLV403SizeX, enemyLV403SizeY));
		enemyLV403FrameX++;
		if (enemyLV403FrameX >= 9) {
			enemyLV403FrameX = 0;
		}

		//Check Enemy 03 Position//

		if (enemyLV403MaxY < 100) {
			enemyLV403PosY = -4.5;
			enemyLV403MaxY++;
		}
		else if (enemyLV403MaxY >= 100 && enemyLV403MaxY < 200) {
			enemyLV403FrameY = 10;
			enemyLV403PosY = 4.5;
			enemyLV403MaxY++;
		}
		else {
			enemyLV403MaxY = 0;
			enemyLV403PosY = 0;
			enemyLV403FrameY = 8;
		}

		enemy403Heart1.setPosition(enemyLV403Position.x + 25, enemyLV403Position.y - 10);
		enemy403Heart2.setPosition(enemyLV403Position.x + 50, enemyLV403Position.y - 10);
		enemy403Heart3.setPosition(enemyLV403Position.x + 75, enemyLV403Position.y - 10);
		

		//**********enemy04 animation**********//

		enemyLV404.move(0.0f, enemyLV404PosY);
		enemyLV404.setTextureRect(sf::IntRect(enemyLV404SizeX* enemyLV404FrameX, enemyLV404SizeY* enemyLV404FrameY, enemyLV404SizeX, enemyLV404SizeY));
		enemyLV404FrameX++;
		if (enemyLV404FrameX >= 9) {
			enemyLV404FrameX = 0;
		}

		//Check Enemy 04 Position//

		if (enemyLV404MaxY < 100) {
			enemyLV404PosY = 4.5;
			enemyLV404MaxY++;
		}
		else if (enemyLV404MaxY >= 100 && enemyLV404MaxY < 200) {
			enemyLV404FrameY = 8;
			enemyLV404PosY = -4.5;
			enemyLV404MaxY++;
		}
		else {
			enemyLV404MaxY = 0;
			enemyLV404PosY = 0;
			enemyLV404FrameY = 10;
		}
		enemy404Heart1.setPosition(enemyLV404Position.x + 25, enemyLV404Position.y - 10);
		enemy404Heart2.setPosition(enemyLV404Position.x + 50, enemyLV404Position.y - 10);
		enemy404Heart3.setPosition(enemyLV404Position.x + 75, enemyLV404Position.y - 10);

		/**********enemy05 animation**********/

		enemyLV405.move(enemyLV405PosX, 0.0f);
		enemyLV405.setTextureRect(sf::IntRect(enemyLV405SizeX* enemyLV405FrameX, enemyLV405SizeY* enemyLV405FrameY, enemyLV405SizeX, enemyLV405SizeY));
		enemyLV405FrameX++;
		if (enemyLV405FrameX >= 9) {
			enemyLV405FrameX = 0;
		}

		//Check Enemy 05 Position//
		
		if (enemyLV405MaxX < 100) { 
			enemyLV405PosX = -4.5;
			enemyLV405MaxX++;
		}
		else if (enemyLV405MaxX >= 100 && enemyLV405MaxX < 200) {
			enemyLV405FrameY = 11;
			enemyLV405PosX = 4.5;
			enemyLV405MaxX++;
		}
		else {
			enemyLV405MaxX = 0;
			enemyLV405PosX = 0;
			enemyLV405FrameY = 9;
		}

		enemy405Heart1.setPosition(enemyLV405Position.x + 25, enemyLV405Position.y - 10);
		enemy405Heart2.setPosition(enemyLV405Position.x + 50, enemyLV405Position.y - 10);
		enemy405Heart3.setPosition(enemyLV405Position.x + 75, enemyLV405Position.y - 10);

		/**********enemy06 animation**********/

		//enemyLV406.move(enemyLV405PosX, 0.0f);
		if (animateBoss == true) {
			enemyLV406.setTextureRect(sf::IntRect(enemyLV406SizeX * enemyLV406FrameX, enemyLV406SizeY * 1, enemyLV406SizeX, enemyLV406SizeY));
			enemyLV406FrameX++;
			if (enemyLV406FrameX >= 7) {
				animateBoss = false;
				enemyLV406FrameX = 0;
			}
		}
		else {
			enemyLV406.setTextureRect(sf::IntRect(enemyLV406SizeX * 0, enemyLV406SizeY * 1, enemyLV406SizeX, enemyLV406SizeY));
		}
		enemy406Heart1.setPosition(enemyLV406Position.x + 100, enemyLV406Position.y - 10);
		enemy406Heart2.setPosition(enemyLV406Position.x + 125, enemyLV406Position.y - 10);
		enemy406Heart3.setPosition(enemyLV406Position.x + 150, enemyLV406Position.y - 10);
		enemy406Heart4.setPosition(enemyLV406Position.x + 175, enemyLV406Position.y - 10);
		enemy406Heart5.setPosition(enemyLV406Position.x + 200, enemyLV406Position.y - 10);
		enemy406Heart6.setPosition(enemyLV406Position.x + 225, enemyLV406Position.y - 10);

		
		/***********************************************************************************************************

		------------------------------------------------------------------------------------------------------------

		-----------------------------------------> > Render Zone < <------------------------------------------------
		
		------------------------------------------------------------------------------------------------------------
		
		***********************************************************************************************************/




		window.clear();
		window.draw(background);
		window.draw(walltop);

		//Render:MainMenu//
		if (n == 0) {
			window.draw(Logo1);
			window.draw(Logo2);
			window.draw(Start);
			window.draw(LeaderBoard);
			window.draw(Exit);
		}
		else if (n == 10) {
			window.draw(Name);
			window.draw(Start);
			window.draw(Mainmenu);
			Mainmenu.setPosition(620, 600);
		}
		else if (n == 99) {
			Mainmenu.setPosition(620, 650);
			window.draw(Mainmenu);
			window.draw(highscoretext);
			for (int i = 0; i < 12; i++)
				window.draw(text[i]);
		}
		//window.draw(playerHitbox);
		else {
			//Render:LEVEL 1//
			window.draw(playerShadow);
			if (n == 1) {
				if(enemy1Life>0)
				window.draw(Enemy1Shadow);
				if (enemy2Life > 0)
				window.draw(Enemy2Shadow);
				//window.draw(enemy01Area);
				//window.draw(enemy02Area);
				window.draw(wall5);
				if (DoorLV1Check == false) {
					window.draw(KeyLV1);
					window.draw(DoorLV1);
				}
				window.draw(wall4);
				window.draw(wall1);
				window.draw(wall2);
				window.draw(player);
				if (enemy1Life > 0) {
					window.draw(enemy01);
				}
				if (enemy2Life > 0) {
					window.draw(enemy02);
				}
				window.draw(DemocracLV1);

				if (playerPosition.y < 300 && playerPosition.y > 200) {
					if (enemy1Life > 0) {
						window.draw(enemy01);
					}
					window.draw(player);
					window.draw(wall1);
					window.draw(wall2);
					if (enemy2Life > 0) {
						window.draw(enemy02);
					}
				}
				if (!playerPosition.y < 300 && !playerPosition.y > 200) {
					if (enemy1Life > 0) {
						window.draw(enemy01);
					}
					window.draw(player);
					window.draw(wall1);
					window.draw(wall2);
					if (enemy2Life > 0) {
						window.draw(enemy02);
					}
				}
				if (enemy02Position.y < playerPosition.y) {
					if (enemy2Life > 0) {
						window.draw(enemy02);
					}
					window.draw(player);
				}
				if (!enemy02Position.y < !playerPosition.y) {
					window.draw(player);
					if (enemy2Life > 0) {
						window.draw(enemy02);
					}
				}
				if (enemy1Life > 0 && enemy01AreaCheck == true) {
					if (enemy1Life == 3) {
						window.draw(enemy01Heart3);
						window.draw(enemy01Heart2);
						window.draw(enemy01Heart1);
					}
					if (enemy1Life == 2) {
						window.draw(enemy01Heart2);
						window.draw(enemy01Heart1);
					}
					if (enemy1Life == 1) {
						window.draw(enemy01Heart1);
					}
				}
				if (enemy2Life > 0 && enemy02AreaCheck == true) {
					if (enemy2Life == 3) {
						window.draw(enemy02Heart3);
						window.draw(enemy02Heart2);
						window.draw(enemy02Heart1);
					}
					if (enemy2Life == 2) {
						window.draw(enemy02Heart2);
						window.draw(enemy02Heart1);
					}
					if (enemy2Life == 1) {
						window.draw(enemy02Heart1);
					}
				}
				if (shieldStatusCheck == true) {
					window.draw(shieldStatus);
				}
				if (shieldCheck == false) {
					window.draw(shield);
				}
				window.draw(wall3);
				if (bullE1out == true) {
					window.draw(bulletE1);
				}
				else {
					bulletE1.setPosition(0, 0);
				}
				if (bullE2out == true) {
					window.draw(bulletE2);
				}
				else {
					bulletE2.setPosition(0, 0);
				}
			}

			//RENDER:LEVEL 2//

			else if (n == 2) {
				if (enemyLV201Life > 0)
					window.draw(Enemy1Shadow);
				if (enemyLV202Life > 0)
					window.draw(Enemy2Shadow);
				window.draw(GateLV2);
				if (playerPosition.y <= 350 && playerPosition.y > 250) {
					window.draw(wallLV202);
					if (enemyLV202Life > 0) {
						window.draw(enemyLV202);
					}
					window.draw(player);
					if (enemyLV201Life > 0) {
						window.draw(enemyLV201);
					}
					window.draw(wallLV201);
				}
				else if (playerPosition.y <= 250 && playerPosition.y > 100) {
					window.draw(wallLV202);
					window.draw(player);
					if (enemyLV202Life > 0) {
						window.draw(enemyLV202);
					}
					if (enemyLV201Life > 0) {
						window.draw(enemyLV201);
					}
					window.draw(wallLV201);
				}
				else if (playerPosition.y <= 100) {
					window.draw(player);
					window.draw(wallLV202);
					if (enemyLV202Life > 0) {
						window.draw(enemyLV202);
					}
					if (enemyLV201Life > 0) {
						window.draw(enemyLV201);
					}
					window.draw(wallLV201);
				}
				else if (playerPosition.y >= 600) {
					window.draw(wallLV202);
					if (enemyLV202Life > 0) {
						window.draw(enemyLV202);
					}
					if (enemyLV201Life > 0) {
						window.draw(enemyLV201);
					}
					window.draw(player);
					window.draw(wallLV201);
				}
				else {
					window.draw(wallLV201);
					window.draw(wallLV202);
					window.draw(player);
					if (enemyLV202Life > 0) {
						window.draw(enemyLV202);
					}
					if (enemyLV201Life > 0) {
						window.draw(enemyLV201);
					}
				}

				window.draw(wallLV203);
				if (enemyLV201Life > 0 && enemy01AreaCheck == true) {
					if (enemyLV201Life == 3) {
						window.draw(enemy201Heart3);
						window.draw(enemy201Heart2);
						window.draw(enemy201Heart1);
					}
					if (enemyLV201Life == 2) {
						window.draw(enemy201Heart3);
						window.draw(enemy201Heart2);
					}
					if (enemyLV201Life == 1) {
						window.draw(enemy201Heart3);
					}
				}
				if (enemyLV202Life > 0 && enemy02AreaCheck == true) {
					if (enemyLV202Life == 3) {
						window.draw(enemy202Heart3);
						window.draw(enemy202Heart2);
						window.draw(enemy202Heart1);
					}
					if (enemyLV202Life == 2) {
						window.draw(enemy202Heart3);
						window.draw(enemy202Heart2);
					}
					if (enemyLV202Life == 1) {
						window.draw(enemy202Heart3);
					}

				}
				if (bullE1out == true) {
					window.draw(bulletE1);
				}
				if (bullE2out == true) {
					window.draw(bulletE2);
				}
				if (speedCheck == false) {
					window.draw(speed);
				}
			}

			else if (n == 3) {
			if (enemyLV203Life > 0)
				window.draw(Enemy1Shadow);
			if (enemyLV204Life > 0)
				window.draw(Enemy2Shadow);
			if (enemyLV205Life > 0)
				window.draw(Enemy3Shadow);
				window.draw(player);
				if (enemyLV203Life > 0) {
					if (enemyLV203Position.y < playerPosition.y) {
						window.draw(enemyLV203);
						window.draw(player);
					}
					else {
						window.draw(player);
						window.draw(enemyLV203);
					}
				}
				if (enemyLV204Life > 0) {
					if (enemyLV204Position.y < playerPosition.y) {
						window.draw(enemyLV204);
						window.draw(player);
					}
					else {
						window.draw(player);
						window.draw(enemyLV204);
					}
				}
				if (enemyLV205Life > 0) {
					if (enemyLV205Position.y < playerPosition.y) {
						window.draw(enemyLV205);
						window.draw(player);
					}
					else {
						window.draw(player);
						window.draw(enemyLV205);
					}
				}
				window.draw(wallLV204);
				if (DoorLV2Check == false) {
					window.draw(KeyLV2);
					window.draw(DoorLV2);
				}
				window.draw(DemocracLV2);
				if (enemyLV203Life > 0 && enemy01AreaCheck == true) {
					if (enemyLV203Life == 3) {
						window.draw(enemy203Heart3);
						window.draw(enemy203Heart2);
						window.draw(enemy203Heart1);
					}
					if (enemyLV203Life == 2) {
						window.draw(enemy203Heart3);
						window.draw(enemy203Heart2);
					}
					if (enemyLV203Life == 1) {
						window.draw(enemy203Heart3);
					}

				}
				if (enemyLV203Life > 0 && bullE1out == true) {
					window.draw(bulletE1);
				}
				if (enemyLV204Life > 0 && enemy02AreaCheck == true) {
					if (enemyLV204Life == 3) {
						window.draw(enemy204Heart3);
						window.draw(enemy204Heart2);
						window.draw(enemy204Heart1);
					}
					if (enemyLV204Life == 2) {
						window.draw(enemy204Heart3);
						window.draw(enemy204Heart2);
					}
					if (enemyLV204Life == 1) {
						window.draw(enemy204Heart3);
					}
				}
				if ( bullE2out == true) {
					window.draw(bulletE2);
				}
				if (enemyLV205Life > 0 && enemy03AreaCheck == true) {
					if (enemyLV205Life == 3) {
						window.draw(enemy205Heart3);
						window.draw(enemy205Heart2);
						window.draw(enemy205Heart1);
					}
					if (enemyLV205Life == 2) {
						window.draw(enemy205Heart3);
						window.draw(enemy205Heart2);
					}
					if (enemyLV205Life == 1) {
						window.draw(enemy205Heart3);
					}

				}
				if (bullE3out == true) {
					window.draw(bulletE3);
				}
				if (lifeCheck == false) {
					window.draw(life);
				}
			}

			//RENDER:LEVEL3//

			else if (n == 4) {
			if (enemyLV301Life > 0)
				window.draw(Enemy1Shadow);
			if (enemyLV302Life > 0)
				window.draw(Enemy2Shadow);
			if (enemyLV303Life > 0)
				window.draw(Enemy3Shadow);
				window.draw(wallLV302);
				window.draw(wallLV303);
				if (enemyLV301Life > 0) {
					window.draw(enemyLV301);
				}
				if (enemyLV303Life > 0) {
					if (enemyLV303Position.y < playerPosition.y) {
						window.draw(enemyLV303);
						window.draw(player);
					}
					else {
						window.draw(player);
						window.draw(enemyLV303);
					}
				}
				else {
					window.draw(player);
				}
				if (enemyLV302Life > 0) {
					if (enemyLV302Position.y < playerPosition.y) {
						window.draw(enemyLV302);
						window.draw(player);
					}
					else {
						window.draw(player);
						window.draw(enemyLV302);
					}
				}
				else {
					window.draw(player);
				}

				if (playerPosition.y < 250 && playerPosition.y >= 200) {
					if (enemyLV301Life > 0) {
						window.draw(enemyLV301);
					}
					if (enemyLV302Position.y < playerPosition.y) {
						if (enemyLV302Life > 0) {
							if (enemyLV302Position.y < playerPosition.y) {
								window.draw(enemyLV302);
								//window.draw(player);
							}
						}
						window.draw(player);
						window.draw(wallLV303);
					}
					if (enemyLV302Position.y > playerPosition.y) {
						window.draw(player);
						if (enemyLV302Life > 0) {
							if (enemyLV302Position.y < playerPosition.y) {
								window.draw(enemyLV302);
								//window.draw(player);
							}
						}
						window.draw(wallLV303);
					}
				}
				if (playerPosition.y < 200) {
					window.draw(player);
					if (enemyLV302Position.y < playerPosition.y) {
						if (enemyLV302Life > 0) {
							if (enemyLV302Position.y < playerPosition.y) {
								window.draw(enemyLV302);
								//window.draw(player);
							}
						}
						window.draw(player);
						window.draw(wallLV303);
					}
					if (enemyLV302Position.y > playerPosition.y) {
						window.draw(player);
						if (enemyLV302Life > 0) {
							if (enemyLV302Position.y < playerPosition.y) {
								window.draw(enemyLV302);
								//window.draw(player);
							}
						}
						window.draw(wallLV303);
					}
					if (enemyLV301Life > 0) {
						window.draw(enemyLV301);
					}
				}
				window.draw(DemocracLV3);
				window.draw(wallLV301);

				if (enemyLV301Life > 0 && enemy01AreaCheck == true) {
					if (enemyLV301Life == 3) {
						window.draw(enemy301Heart3);
						window.draw(enemy301Heart2);
						window.draw(enemy301Heart1);
					}
					if (enemyLV301Life == 2) {
						window.draw(enemy301Heart3);
						window.draw(enemy301Heart2);
					}
					if (enemyLV301Life == 1) {
						window.draw(enemy301Heart3);
					}
				}
				if (enemyLV302Life > 0 && enemy02AreaCheck == true) {
					if (enemyLV302Life == 3) {
						window.draw(enemy302Heart3);
						window.draw(enemy302Heart2);
						window.draw(enemy302Heart1);
					}
					if (enemyLV302Life == 2) {
						window.draw(enemy302Heart3);
						window.draw(enemy302Heart2);
					}
					if (enemyLV302Life == 1) {
						window.draw(enemy302Heart3);
					}
				}
				if (enemyLV303Life > 0 && enemy03AreaCheck == true) {
					if (enemyLV303Life == 3) {
						window.draw(enemy303Heart3);
						window.draw(enemy303Heart2);
						window.draw(enemy303Heart1);
					}
					if (enemyLV303Life == 2) {
						window.draw(enemy303Heart3);
						window.draw(enemy303Heart2);
					}
					if (enemyLV303Life == 1) {
						window.draw(enemy303Heart3);
					}
				}
				if (bullE1out == true) {
					window.draw(bulletE1);
				}
				if (bullE2out == true) {
					window.draw(bulletE2);
				}
				if (bullE3out == true) {
					window.draw(bulletE3);
				}

			}

			//RENDER:LEVEL4//

			else if (n == 5) {
			if (enemyLV401Life > 0)
				window.draw(Enemy1Shadow);
			if (enemyLV402Life > 0)
				window.draw(Enemy2Shadow);
			if (enemyLV405Life > 0)
				window.draw(Enemy3Shadow);
				if (enemyLV402Life > 0) {
					window.draw(enemyLV402);
				}
				window.draw(wallLV402);
				window.draw(wallLV401);
				if (enemyLV401Life > 0) {
					window.draw(enemyLV401);
				}
				if (playerPosition.y < 350) {
					if (playerPosition.y < enemyLV401Position.y) {
						window.draw(player);
						if (enemyLV401Life > 0) {
							window.draw(enemyLV401);
						}
					}
					if (!(playerPosition.y < enemyLV401Position.y)) {
						if (enemyLV401Life > 0) {
							window.draw(enemyLV401);
						}
						window.draw(player);

					}
					if (playerPosition.y < enemyLV402Position.y) {
						window.draw(player);
						if (enemyLV402Life > 0) {
							window.draw(enemyLV402);
						}
					}
					if (!(playerPosition.y < enemyLV402Position.y)) {
						if (enemyLV402Life > 0) {
							window.draw(enemyLV402);
						}
						window.draw(player);
					}

					window.draw(wallLV401);

				}
				if (!(playerPosition.y < 350)) {
					window.draw(wallLV401);
					if (playerPosition.y < enemyLV401Position.y) {
						window.draw(player);
						if (enemyLV401Life > 0) {
							window.draw(enemyLV401);
						}
					}
					if (!(playerPosition.y < enemyLV401Position.y)) {
						if (enemyLV401Life > 0) {
							window.draw(enemyLV401);
						}
						window.draw(player);

					}
				}
				if (enemyLV405Life > 0) {
					if (enemyLV405Position.y < playerPosition.y) {
						window.draw(enemyLV405);
						window.draw(player);
					}
					else {

						window.draw(player);
						window.draw(wallLV401);
						window.draw(enemyLV405);
					}
				}
				window.draw(GateLV4);
				if (enemyLV401Life > 0 && enemy01AreaCheck == true) {
					if (enemyLV401Life == 3) {
						window.draw(enemy401Heart3);
						window.draw(enemy401Heart2);
						window.draw(enemy401Heart1);
					}
					if (enemyLV401Life == 2) {
						window.draw(enemy401Heart3);
						window.draw(enemy401Heart2);
					}
					if (enemyLV401Life == 1) {
						window.draw(enemy401Heart3);
					}
				}
				if (enemyLV402Life > 0 && enemy02AreaCheck == true) {
					if (enemyLV402Life == 3) {
						window.draw(enemy402Heart3);
						window.draw(enemy402Heart2);
						window.draw(enemy402Heart1);
					}
					if (enemyLV402Life == 2) {
						window.draw(enemy402Heart3);
						window.draw(enemy402Heart2);
					}
					if (enemyLV402Life == 1) {
						window.draw(enemy402Heart3);
					}
				}
				if (enemyLV405Life > 0 && enemy03AreaCheck == true) {
					if (enemyLV405Life == 3) {
						window.draw(enemy405Heart3);
						window.draw(enemy405Heart2);
						window.draw(enemy405Heart1);
					}
					if (enemyLV405Life == 2) {
						window.draw(enemy405Heart3);
						window.draw(enemy405Heart2);
					}
					if (enemyLV405Life == 1) {
						window.draw(enemy405Heart3);
					}
				}
				if (bullE1out == true) {
					window.draw(bulletE1);
				}
				if (bullE2out == true) {
					window.draw(bulletE2);
				}
				if (bullE3out == true) {
					window.draw(bulletE3);
				}
				if (KeyLV4Check == false) {
					window.draw(KeyLV4);
					window.draw(DoorLV4);
				}
				if (imortalCheck == false) {
					window.draw(ImortalPot);
				}
				window.draw(wallLV401forbull);
			}

			else if (n == 6) {
				window.draw(player);
				if (enemyLV403Life > 0) {
					window.draw(enemyLV403);
				}
				if (enemyLV404Life > 0) {
					window.draw(enemyLV404);
				}

				if (player.getGlobalBounds().intersects(enemyLV403.getGlobalBounds())) {
					if (enemyLV403Position.y > playerPosition.y) {
						window.draw(player);
						if (enemyLV403Life > 0) {
							window.draw(enemyLV403);
						}
						if (enemyLV404Life > 0) {
							window.draw(enemyLV404);
						}
					}
					else if (enemyLV403Position.y <= playerPosition.y) {
						if (enemyLV403Life > 0) {
							window.draw(enemyLV403);
						}
						if (enemyLV404Life > 0) {
							window.draw(enemyLV404);
						}
						window.draw(player);
					}
				}
				if (player.getGlobalBounds().intersects(enemyLV404.getGlobalBounds())) {
					if (enemyLV404Position.y > playerPosition.y) {
						window.draw(player);
						if (enemyLV404Life > 0) {
							window.draw(enemyLV404);
						}
						if (enemyLV403Life > 0) {
							window.draw(enemyLV403);
						}
					}
					else if (enemyLV404Position.y <= playerPosition.y) {
						if (enemyLV404Life > 0) {
							window.draw(enemyLV404);
						}
						if (enemyLV403Life > 0) {
							window.draw(enemyLV403);
						}
						window.draw(player);
					}
				}
				window.draw(DemocracLV4);
				if (enemyLV403Life > 0 && enemy01AreaCheck == true) {
					window.draw(Enemy1Shadow);
					if (enemyLV403Life == 3) {
						window.draw(enemy403Heart3);
						window.draw(enemy403Heart2);
						window.draw(enemy403Heart1);
					}
					if (enemyLV403Life == 2) {
						window.draw(enemy403Heart3);
						window.draw(enemy403Heart2);
					}
					if (enemyLV403Life == 1) {
						window.draw(enemy403Heart3);
					}
				}
				if (enemyLV404Life > 0 && enemy02AreaCheck == true) {
					window.draw(Enemy2Shadow);
					if (enemyLV404Life == 3) {
						window.draw(enemy404Heart3);
						window.draw(enemy404Heart2);
						window.draw(enemy404Heart1);
					}
					if (enemyLV404Life == 2) {
						window.draw(enemy404Heart3);
						window.draw(enemy404Heart2);
					}
					if (enemyLV404Life == 1) {
						window.draw(enemy404Heart3);
					}
				}
				if (enemyLV406Life > 0) {
					window.draw(enemyLV406);
				}
				if (enemyLV406Life > 0 && enemy03AreaCheck == true) {
					window.draw(Enemy3Shadow);
					if (enemyLV406Life == 6) {
						window.draw(enemy406Heart6);
						window.draw(enemy406Heart5);
						window.draw(enemy406Heart4);
						window.draw(enemy406Heart3);
						window.draw(enemy406Heart2);
						window.draw(enemy406Heart1);
					}
					if (enemyLV406Life == 5) {
						window.draw(enemy406Heart5);
						window.draw(enemy406Heart4);
						window.draw(enemy406Heart3);
						window.draw(enemy406Heart2);
						window.draw(enemy406Heart1);
					}
					if (enemyLV406Life == 4) {
						window.draw(enemy406Heart4);
						window.draw(enemy406Heart3);
						window.draw(enemy406Heart2);
						window.draw(enemy406Heart1);
					}
					if (enemyLV406Life == 3) {
						window.draw(enemy406Heart3);
						window.draw(enemy406Heart2);
						window.draw(enemy406Heart1);
					}
					if (enemyLV406Life == 2) {
						window.draw(enemy406Heart2);
						window.draw(enemy406Heart1);
					}
					if (enemyLV406Life == 1) {
						window.draw(enemy406Heart1);
					}
				}
				if (bullE1out == true) {
					window.draw(bulletE1);
				}
				if (bullE2out == true) {
					window.draw(bulletE2);
				}
				if (bullE3out == true) {
					window.draw(bulletE3);
				}

			}

			//Render::Bullet//

			if (bulletNo[0] == 1) {
				window.draw(bullet1);
			}
			if (bulletNo[1] == 1) {
				window.draw(bullet2);
			}
			if (bulletNo[2] == 1) {
				window.draw(bullet3);
			}
			
			window.draw(fade);
			window.draw(timerClockSec);
			window.draw(timerClockMilliSec);
			window.draw(dot);
			window.draw(time);
			window.draw(unit);
			window.draw(Pause);
			//Render:Imortal//
			if (imortalCheck == true) {
				window.draw(imortalStatus);
			}
			//Render:Heart//
			if (playerLife >= 1) {
				if (heart1Check == true) {
					window.draw(heart1);
				}
			}
			if (playerLife >= 2) {
				if (heart2Check == true) {
					window.draw(heart2);
				}
			}
			if (playerLife >= 3) {
				if (heart3Check == true) {
					window.draw(heart3);
				}
			}
			if (shieldStatusCheck == true) {
				window.draw(shieldStatus);
			}
		}

	}
	
	if (pauseStatus == true) {
		backgroundSound.play();
		bossFightSound.play();
		window.clear();
		window.draw(Resume);
		window.draw(Mainmenu);
		Mainmenu.setPosition(620, 400);
	}
	if (playerLife <= 0) {
		pauseStatus = true;
		window.clear();
		bossFightSound.pause();
		backgroundSound.pause();
		window.draw(gameover);
		finalTimerClockMilliSec.setString(millisecShow);
		finalTimerClockMilliSec.setPosition(1005, 0);
		finalTimerClockSec.setString(secShow);
		if (sec >= 10) {
			finalTimerClockSec.setPosition(940, 0);
		}
		if (sec >= 100) {
			finalTimerClockSec.setPosition(920, 0);
		}

		window.draw(finalTimerClockMilliSec);
		window.draw(finalTimerClockSec);
		window.draw(finalTime);
		window.draw(unit);
		window.draw(dot);
		Mainmenu.setPosition(620, 600);
		window.draw(Mainmenu);
	}
	else {
		gameoverSound.play();
	}
	if (DemocracLv4Col == true) {
	
		backgroundSound.pause();
		pauseStatus = true;
		window.clear();
		//window.draw(gameover);
		finalTimerClockMilliSec.setString(millisecShow);
		finalTimerClockMilliSec.setPosition(1005, 0);
		finalTimerClockSec.setString(secShow);
		if (sec >= 10) {
			finalTimerClockSec.setPosition(940, 0);
		}
		if (sec >= 100) {
			finalTimerClockSec.setPosition(920, 0);
		}

		window.draw(finalTimerClockMilliSec);
		window.draw(finalTimerClockSec);
		window.draw(finalTime);
		window.draw(unit);
		window.draw(dot);
		Mainmenu.setPosition(620, 600);
		window.draw(Mainmenu);
		window.draw(ending);
		window.draw(endingtx);
	}
		//window.draw(mouseHitBox);
		//window.draw(enemy01Area);
		window.display();

	}
	return 0;
	/*----------------------------------------------------------------------------------------------------------

	--------------------------------------------- Loop END -----------------------------------------------------

	----------------------------------------------------------------------------------------------------------*/
}
