#pragma once
#include "Enemy.h"
#include "AnimationComponent.h"
#include "MobMovementComponent.h"
#include "MobAttackComponent.h"
#include "MobLifeComponent.h"
#include "Game.h"

class Mob : public Enemy
{
	Vector2f startPosition;
	Vector2f goalPosition;

protected:
	bool isPatrolling;
	bool cooldownAttack;

	AnimationComponent* animation;
	MobMovementComponent* movement;
	MobAttackComponent* attack;

public:

public:
	Mob(const ShapeData& _data);

private:
	void InitTimerPatrol();
	void InitTimerCooldownAttack();
	void CooldownAttack();
	void RunLinkedAnimation(const string& _linkedAnimation, AnimationComponent* _animationComponent);

public:
	void Move();
	void Patrol();
	virtual void Attack(Player* _player) = 0;
	virtual void Death() = 0;
	virtual void Update(const float _deltaTime) override;
};