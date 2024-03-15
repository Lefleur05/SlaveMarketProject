#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Canvas.h"
#include "Button.h"
#include "ScrollBar.h"

class HUD : public Singleton<HUD>, public IManager<string, Canvas>
{
	vector<Button*> buttons;
	int indexHorveredButton;
	vector<ScrollBar*> scrollBars;

public:
	void AddButton(Button* _button)
	{
		buttons.push_back(_button);
	}
	void AddScrollBar(ScrollBar* _scrollBar)
	{
		scrollBars.push_back(_scrollBar);
	}

public:
	void Interact(const Vector2f& _worldPosition, const Event& _event);
	Button* GetHoveredButton(const vector<Button*>& _buttons);
	int GetHoveredButtonIndex(const vector<Button*>& _buttons);
	Button* GetPressedButton(const vector<Button*>& _buttons);
	int GetIndexHorveredButton() const
	{
		return indexHorveredButton;
	}
	void SetIndexHorveredButton(const int _index)
	{
		indexHorveredButton = _index;
	}
};