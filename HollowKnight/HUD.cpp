#include "HUD.h"
#include "InputManager.h"
#include "Widget.h"
#include "Button.h"

void HUD::Interact(const Vector2f& _worldPosition, const Event& _event)
{
	vector<int> _allIndexesVisibleButtons;

	for (int _i = 0; _i < buttons.size(); _i++)
	{
		if (buttons[_i]->IsVisible())
		{
			_allIndexesVisibleButtons.push_back(_i);
		}
	}
	for (Button* _button : buttons)
	{
		if (!_button->IsVisible())	continue;

		_button->OnHovered();
		if (_button->GetDrawable()->getGlobalBounds().contains(_worldPosition))
		{
			if (_event.type == Event::MouseButtonPressed)
			{
				if (_button->OnPressed()) return;
			}
		}
		else
		{
			_button->OnUnhovered();
		}
		if (_event.type == Event::EventType::MouseButtonReleased)
		{
			_button->OnReleased();
		}

		_button->OnHeld();
	}


	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		cout << "Up" << endl;
		indexHorveredButton--;
		if (indexHorveredButton <= 0)indexHorveredButton = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		cout << "Down" << endl;
		indexHorveredButton++;
		if (indexHorveredButton >= _allIndexesVisibleButtons.size())
		{
			indexHorveredButton = _allIndexesVisibleButtons.size() - 1;
		}
	}
	// TODO appuye aussi sur le bouton suivant ( donc appuye 2 fois de suite)
	else if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		if (buttons.size() > 0 && _allIndexesVisibleButtons.size() > 0 && _event.type== Event::KeyReleased)
		{
			if (buttons[_allIndexesVisibleButtons[indexHorveredButton]]->OnPressed())
			{
				indexHorveredButton = 0;
				return;
			}
		}
	}




	for (ScrollBar* _scrollBar : scrollBars)
	{
		if (!_scrollBar->IsVisible()) continue;

		if (_event.type == Event::MouseWheelScrolled)
		{
			_scrollBar->UpdateScroll(_event);
		}
		//else if (_scrollBar->GetDrawable()->getGlobalBounds().contains(_worldPosition))
		//{
		//	if (_event.type == Event::MouseButtonPressed)
		//	{
		//		if (_event.mouseButton.button == Mouse::Left)
		//		{
		//			const Vector2f& _position = static_cast<Vector2f>(Vector2i(_event.mouseButton.x, _event.mouseButton.y));
		//			_scrollBar->ComputeClickOnBar(_position);
		//		}
		//	}
		//}
	}
}

Button* HUD::GetHoveredButton(const vector<Button*>& _buttons)
{
	const Vector2f& _worldPosition = InputManager::GetInstance().GetWorldPosition();

	for (Button* _button : _buttons)
	{
		if (_button->IsVisible() && _button->GetDrawable()->getGlobalBounds().contains(_worldPosition))
		{
			return _button;
		}
	}

	return nullptr;
}

int HUD::GetHoveredButtonIndex(const vector<Button*>& _buttons)
{
	const Vector2f& _worldPosition = InputManager::GetInstance().GetWorldPosition();

	for (int _i = 0; _i < _buttons.size(); _i++)
	{
		if (_buttons[_i]->IsVisible() && _buttons[_i]->GetDrawable()->getGlobalBounds().contains(_worldPosition))
		{
			return _i;
		}
	}

	return -1;
}

Button* HUD::GetPressedButton(const vector<Button*>& _buttons)
{
	const Vector2f& _worldPosition = InputManager::GetInstance().GetWorldPosition();

	for (Button* _button : _buttons)
	{
		if (_button->IsVisible() && _button->GetDrawable()->getGlobalBounds().contains(_worldPosition))
		{
			return _button;
		}
	}

	return nullptr;
}
