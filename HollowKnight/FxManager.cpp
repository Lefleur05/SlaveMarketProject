#include "FxManager.h"
#include"Game.h"
#include"Fx.h"

#define PATH_FX "Animations/Fx.png"

FxManager::FxManager()
{
	index = 0;
}

void FxManager::Run(const string& _runningAnimation)
{
	index++;
	Vector2f _pos = Game::GetPlayer()->GetPosition();
	float _direction = Game::GetPlayer()->GetPlayerMovement()->GetDashDirection();

	if (_runningAnimation == "FxDash")
	{
		if (_direction == -1)
		{
			Fx* _fxdash1 = new Fx("fx" + to_string(index), ShapeData(_pos - Vector2f(200.0f, 0.0f), Vector2f(250.0f, 250.0f), PATH_FX));
			FxData _fxdata = FxData(_fxdash1, "");
			_fxdata.GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
			_fxdash1->Destroy(1.0f);
		}
		else if (_direction == 1)
		{
			Fx* _fxdash2 = new Fx("fx" + to_string(index), ShapeData(_pos + Vector2f(200.0f, 0.0f), Vector2f(250.0f, 250.0f), PATH_FX));
			FxData _fxdata = FxData(_fxdash2, "");
			_fxdata.GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
			_fxdash2->Destroy(1.0f);
		}
	}
	else if (_runningAnimation == "FxDoubleJump")
	{
		Fx* _fxJump = new Fx("fx" + to_string(index), ShapeData(_pos + Vector2f(0.0f, -100.0f), Vector2f(250.0f, 250.0f), PATH_FX));
		FxData _fxdata = FxData(_fxJump, "");
		_fxdata.GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
		_fxJump->Destroy(1.0f);
	}
	else
	{
		Fx* _fx = new Fx("fx" + to_string(index), ShapeData(_pos, Vector2f(250.0f, 250.0f), PATH_FX));
		FxData _fxdata = FxData(_fx, "");
		_fxdata.GetCurrentAnimation()->RunAnimation(_runningAnimation, -_direction);
		_fx->Destroy(1.0f);
	}
	
}
