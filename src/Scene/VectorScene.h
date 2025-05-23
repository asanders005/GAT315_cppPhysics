#pragma once
#include "scene.h"

class VectorScene : public Scene
{
public:
	VectorScene(const std::string& title, int width, int height, const Color& background = BLACK) : Scene(title, width, height, background)
	{

	}

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;

private:
	enum class FireworkType
	{
		Circle,
		Cone,
		End
	};

	enum class ColorType
	{
		Single,
		Gradient,
		Multi,
		End
	};

private:
	FireworkType m_fireworkType{ FireworkType::Circle };
	ColorType m_colorType{ ColorType::Single };

	bool m_isPaused{ false };
};