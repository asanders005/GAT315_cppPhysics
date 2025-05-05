#include "PolarScene.h"
#include "Coordinates/Polar.h"

void PolarScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void PolarScene::Update()
{
}

void PolarScene::Draw()
{
	m_camera->BeginMode();

	m_camera->EndMode();
}

void PolarScene::DrawGUI()
{
}

void PolarScene::DrawArchimedeanSpiral(float startRadius, float spacing, float theta)
{
	m_camera->BeginMode();

	for (float i = -theta; i < theta; i += 0.2f)
	{
		float r = startRadius + (spacing * i);
		Polar p{ i, r };

		DrawCircle((Vector2)p, 0.1f, BLUE);
	}

	m_camera->EndMode();
}

void PolarScene::DrawCardioid(float size, float theta)
{
	m_camera->BeginMode();

	for (float i = -theta; i < theta; i += 0.2f)
	{
		float r = size * (1 + cosf(i));
		Polar p{ i, r };

		DrawCircle((Vector2)p, 0.1f, BLUE);
	}

	m_camera->EndMode();
}

void PolarScene::DrawLimacon(float loop, float dimple, float theta)
{
	m_camera->BeginMode();
	for (float i = -theta; i < theta; i += 0.2f)
	{
		float r = loop + (dimple * cosf(i));
		Polar p{ i, r };
		DrawCircle((Vector2)p, 0.1f, BLUE);
	}
	m_camera->EndMode();
}

void PolarScene::DrawRose(float size, float petalCount, float theta)
{
	m_camera->BeginMode();
	for (float i = -theta; i < theta; i += 0.2f)
	{
		float r = size * cosf(petalCount * i);
		Polar p{ i, r };
		DrawCircle((Vector2)p, 0.1f, BLUE);
	}
	m_camera->EndMode();
}
