#include "Game.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "ActorManager.h"
#include "HUD.h"
#include "Widget.h"


#define PATH_PLAYER "Player.png"
#define FONT "Assets/Fonts/Font.ttf"

Game::Game()
{
	//map = new Map();
	//player = new Player();
	//camera = new Camera();
	//playerInfo = new PlayerInfo(10, 10, 20, 20, 1000)
}

Game::~Game()
{
	//delete map;
	//delete player;
	// delete camera;
}


void Game::Start()
{
	window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SparklingSprings");
	TimerManager::GetInstance().SetRenderCallback(bind(&Game::UpdateWindow, this));
	new Timer(this, &Game::Init, seconds(1.0f), true, false);
}

void Game::Init()
{
	
}

void Game::Update()
{
	while (window.isOpen())
	{
		playerInfo->SetMaxHealth(playerInfo->GetMaxHealth() +1);
		cout << playerInfo->GetMaxHealth() << endl;
		TimerManager::GetInstance().Update();
		if (!InputManager::GetInstance().Update(window)) break;
		ActorManager::GetInstance().Update();
	}
}

void Game::UpdateWindow()
{
	window.clear();

	// Game
	// const View& _defaultView = window.getDefaultView();
	//Deux fa�on de suivre le Player
	//1:
	const View& _defaultView =  camera->FollowPlayer();
	//2:
	// const View& _defaultView = camera->GetView();

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
	// Camera
	// 
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