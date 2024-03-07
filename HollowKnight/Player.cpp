#include "Player.h"
#include "Game.h"

// Mobs
#include "Mob.h"
#include "DeathMob.h"

// System
#include "Macro.h"
#include "Kismet.h"

// Managers
#include "ActorManager.h"
#include "InputManager.h"
#include "Timer.h"

#define PATH_ITEM "UIs/Inventory/Item.png"
#define PATH_ITEM2 "test.png"
#define PATH_DEATHMOB "Animations/DeathMob.png"

Player::Player(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	animation = new PlayerAnimationComponent(this);
	components.push_back(animation);

	movement = new PlayerMovementComponent(this);
	components.push_back(movement);

	attack = new PlayerAttackComponent(this, 1);
	components.push_back(attack);
	
	inventory = new Inventory(); // before interaction

	interaction = new InteractionComponent(this);
	components.push_back(interaction);

	stats = new PlayerStat(this);

	charmsMenu = new CharmsMenu();
	pauseMenu = new PauseMenu();

	//components.push_back(stats);

	light = new CircleShape(55.0f);
	light->setFillColor(Color(255, 255, 255, 20)); 
	light->setOrigin(100.0f, 100.0f);

}


void Player::InitAnimations()
{
	animation->Init();
}

void Player::SetupPlayerInput()
{
	new ActionMap("Stats", {
		ActionData("ConvertManaToLife", [&]() {
			stats->UseMana(-10.0f);
			stats->UpdateLife(1);
		}, InputData({ActionType::KeyPressed, Keyboard::A})),
	});

	new ActionMap("Movements", {
		ActionData("Right", [&]() { movement->SetDirectionX(1.0f, "Right"); }, InputData({ActionType::KeyPressed, Keyboard::D})/*,  InputData({ActionType::JoystickMoved, GameControllerAxes::LeftStickX})*/),
		ActionData("StopRight", [&]() { movement->SetDirectionX(0.0f, "StopRight"); }, InputData({ ActionType::KeyReleased, Keyboard::D })),
		ActionData("Left", [&]() { movement->SetDirectionX(-1.0f, "Left"); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("StopLeft", [&]() { movement->SetDirectionX(0.0f, "StopLeft"); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),
		ActionData ("Jump", [&]() { movement->Jump(); }, InputData({ ActionType::KeyPressed, Keyboard::Space }), InputData({ActionType::JoystickButtonPressed, Joystick::isButtonPressed(0, static_cast<unsigned int>(GameControllerButtons::Cross))})),
		ActionData("Dash", [&]() { movement->Dash(); }, InputData({ ActionType::KeyPressed,Keyboard::LControl })/*, InputData({ActionType::JoystickButtonPressed, Joystick::isButtonPressed(0, static_cast<unsigned int>(GameControllerButtons::R2))})*/),
		ActionData("Sit", [&]() {
			movement->SitDown();
			attack->SetCanAttack(false);
		}, InputData({ ActionType::KeyPressed, Keyboard::Z })),
		ActionData("Stand", [&]() {
			movement->StandUp();
			attack->SetCanAttack(true);
		}, InputData({ ActionType::KeyPressed, Keyboard::S }))
	});

	new ActionMap("Attack", {
		ActionData("Special", [&]() { attack->SpecialAttack(); }, InputData({ActionType::MouseButtonPressed, Mouse::Left})),
		ActionData("StopSlash", [&]() { movement->SetDirectionX(0.0f, "Right"); }, InputData({ ActionType::MouseButtonReleased, Mouse::Left })),
	});

	new ActionMap("Menu", {
		ActionData("Pause", [&]() { TryToOpen(pauseMenu); }, InputData({ ActionType::KeyPressed, Keyboard::Escape })),
		ActionData("Inventory", [&]() { TryToOpen(inventory); }, InputData({ ActionType::KeyPressed, Keyboard::B })),
		ActionData("CharmsMenu", [&]() {
			if (!movement->IsStanding())
			{
				TryToOpen(charmsMenu);
			}
		}, InputData({ ActionType::KeyPressed, Keyboard::P })),
		ActionData("Interact", [&]() { interaction->TryToInteract(); }, InputData({ ActionType::KeyPressed, Keyboard::E })),
	});
}

void Player::TryToOpen(Menu* _menu)
{
	const bool _isActive = _menu->IsActive();
	CloseAllMenus();

	if (!_isActive)
	{
		_menu->SetStatus(true);
		stats->SetStatus(false);
	}
}

void Player::CloseAllMenus()
{
	charmsMenu->SetStatus(false);
	stats->SetStatus(true);
	inventory->SetStatus(false);
	interaction->StopInteract();
}


void Player::Init()
{
	movement->SetCanMove(true);
	stats->Init();
	inventory->Init();
	charmsMenu->Init();

	InitAnimations();
	SetupPlayerInput();
}