#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Player.h"
#include "Camera.h"

#include "Merchand.h"

using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game
{
	static RenderWindow window;
	Menu* menu;
	static Player* player;
	Camera* camera;

	//TODO move
	Merchand* merchand;

public:
	static Vector2f GetWindowSize()
	{
		return Vector2f(window.getSize());
	}
	static Player* GetPlayer()
	{
		return player;
	}

public:
	Game();
	~Game();

public:
	void Start();
	void Init();
	void Update();
	void UpdateWindow();
	void Stop();

public:
	void Launch();
	static void Close();
};