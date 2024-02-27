#include "Game.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "ActorManager.h"
#include "HUD.h"
#include "Widget.h"
#include "Player.h"

#define PATH_PLAYER "Player.png"
#define FONT "Assets/Fonts/Font.ttf"

RenderWindow Game::window;
Player* Game::player;

Game::Game()
{
	player = new Player("Player", ShapeData(Vector2f(0.0f, 0.0f), Vector2f(100.0f, 100.0f), ""));
	menu = new Menu();
}

Game::~Game()
{
	delete camera;
}


void Game::Start()
{
	window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "HollowKnight");
	TimerManager::GetInstance().SetRenderCallback(bind(&Game::UpdateWindow, this));
	new Timer(this, &Game::Init, seconds(1.0f), true, false);
}

void Game::Init()
{
	player->Init();
	menu->Init();
}

void Game::Update()
{
	while (window.isOpen())
	{
		TimerManager::GetInstance().Update();
		if (!InputManager::GetInstance().Update(window)) break;
		ActorManager::GetInstance().Update();
	}
}

void Game::UpdateWindow()
{
	window.clear();

	// const View& _defaultView = window.getDefaultView();
	//Deux fa�on de suivre le Player
	//1:
	//const View& _defaultView =  camera->FollowPlayer();
	////2:
	//const View& _defaultView = camera->GetView();

	const View& _defaultView = window.getDefaultView();
	window.setView(_defaultView);

	for (Actor* _actor : ActorManager::GetInstance().GetAllValues())
	{
		window.draw(*_actor->GetDrawable());
	}

	// UI
	View _view = _defaultView;
	for (Canvas* _canvas : HUD::GetInstance().GetAllValues())
	{
		if (!_canvas->IsVisible()) continue;

		_view.setViewport(_canvas->GetRect());
		window.setView(_view);

		for (Widget* _widget : _canvas->GetWidgets()) 
		{
			if (!_widget->IsVisible()) continue;
			window.draw(*_widget->GetDrawable());
		}
	}

	// camera->FollowPlayer;

	window.display();
}

void Game::Stop()
{
	cout << "A bient�t !" << endl;
}


void Game::Launch()
{
	Start();
	Update();
	Stop();
}

void Game::Close()
{
	window.close();
}