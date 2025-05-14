#pragma once
#include "scene.h"
#include <array>

class PolarScene : public Scene
{
public:
	PolarScene(const std::string& title, int width, int height, const Color& background = BLACK) : Scene(title, width, height, background)
	{}

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;

private:
	void DrawArchimedeanSpiral(float startRadius, float spacing, float theta);
	void DrawCardioid(float size, float theta);
	void DrawLimacon(float loop, float dimple, float theta);
	void DrawRose(float size, int petalCount, float theta);
	void DrawLemniscate(float size, float theta);

private:
	enum class polarType
	{
		ARCHIMEDEAN_SPIRAL,
		CARDIOID,
		LIMACON,
		ROSE,
		USER_DEFINED
	};
	polarType m_currentPolarType = polarType::ARCHIMEDEAN_SPIRAL;

private:
	float m_size{ 2 };
	float m_unique{ 2 };
	float m_theta{ 20 };
	float m_rate{ 1 };

	std::array<Color, 9> m_colors{ WHITE, PINK, RED, ORANGE, YELLOW, GREEN, BLUE, VIOLET, DARKGRAY};
};