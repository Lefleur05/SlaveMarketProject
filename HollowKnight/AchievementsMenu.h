#pragma once
#include "Menu.h"
#include "Button.h"
#include "ScrollBar.h"
#include "Canvas.h"

struct AchievementData
{
	string title;
	string description;
};


struct Achievement
{
	ShapeWidget* widget;
	vector<Label*> labels;
	void SetVisible(bool _visible)
	{
		widget->SetVisible(_visible);
	}

	Achievement(ShapeWidget* _widget, const vector<Label*>& _labels)
	{
		widget = _widget;
		labels = _labels;
	}
};

class AchievementsMenu : public Menu
{
	ScrollBar* handle;
	Canvas* canvas;
	vector<AchievementData> allData;
	vector<Achievement*> achievements;

	ShapeWidget* boxOfView;

public:
	Canvas* GetAchievementCanvas() { return canvas; }
	ShapeWidget* GetBoxOfView() { return boxOfView; }

public:
	AchievementsMenu(Menu* _owner);

public:
	virtual void Init() override;

	void ComputeScroll(const vector<AchievementData>& _data, const bool _scrollType);
};