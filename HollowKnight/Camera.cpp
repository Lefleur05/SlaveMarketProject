#include "Camera.h"
#include "Game.h"

Camera::Camera()
{
	target = TARGET_NONE;
	const FloatRect& _rect = Game::GetPlayer()->GetDrawable()->getGlobalBounds();
	center = Vector2f(_rect.left, _rect.top /* rectPlayer.left , rectPlayer.top */);
	size = Vector2f(1000 , 1000);
	view = View(center , size);
}

Camera::Camera(View _view)
{
	view = _view;
}

Camera::Camera(const Target& _target)
{
	target = _target;
	const FloatRect& _rect = Game::GetPlayer()->GetDrawable()->getGlobalBounds();
	center = Vector2f(_rect.left, _rect.top /* rectPlayer.left , rectPlayer.top */);
	size = Vector2f(1000, 1000);
	view = View(center, size);
}

View Camera::FollowPlayer()
{
	view.setCenter(GetPlayerRect().left, GetPlayerRect().top);
	return view;
}

FloatRect Camera::GetPlayerRect()
{
	Player* _player = Game::GetPlayer();   // Ne pas creer de player mais le recuperer 
	const FloatRect& _rectPlayer = _player->GetDrawable()->getGlobalBounds();
	return _rectPlayer;
}
