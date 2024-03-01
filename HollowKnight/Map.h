#pragma once
#include <SFML/Graphics.hpp>
#include "ShapeObject.h"
#include "Bench.h"
#include "Merchand.h"
#include "InteractableActor.h"

using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

struct WallData
{
	Vector2f position;
	Vector2f size;
	string path;
};

struct MapData
{
	string backgroundPath;
	Vector2f backgroundPos;
	Vector2f backgroundSize;

	Vector2f clampCamMin;
	Vector2f clampCamMax;

	vector<WallData> walls;
};

class Map
{
	Bench* bench;
	Merchand* merchand;
	InteractableActor* pnj;
	ShapeObject* background;
	ShapeObject* barrack;
	vector<ShapeObject*> drawables;

public:
	Bench* GetBench() const
	{
		return bench;
	}
	vector<ShapeObject*> GetAllDrawables() const
	{
		return drawables;
	}

public:
	Map();

private:
	MapData LoadMapData(const string& _path);

public:
	void Init();
};