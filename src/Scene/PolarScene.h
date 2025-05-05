#pragma once
#include "scene.h"

class PolarScene : public Scene
{
public:
	PolarScene(const std::string& title, int width, int height, const Color& background = BLACK) : Scene(title, width, height, background)
	{

	}

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void DrawGUI() override;

	void DrawArchimedeanSpiral(float startRadius, float spacing, float theta);
	void DrawCardioid(float size, float theta);
	void DrawLimacon(float loop, float dimple, float theta);
	void DrawRose(float size, float petalCount, float theta);
};