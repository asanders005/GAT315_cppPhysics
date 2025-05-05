#include "trig_scene.h"
#include "raymath.h"

void TrigScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void TrigScene::Update()
{
}

float DegToRad(float degrees)
{
	return degrees * (PI / 180.0f);
}

float RadToDeg(float radians)
{
	return radians * (180.0f / PI);
}

//Vector2& Vector2Normalize(const Vector2& v)
//{
//	float length = sqrtf(v.x * v.x + v.y * v.y);
//	if (length > 0.0f)
//	{
//		return { v.x / length, v.y / length };
//	}
//	return { 0.0f, 0.0f };
//}

void TrigScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);
	//DrawCircle(Vector2{ 0, 0 }, 1, PURPLE);

	// Circle
	float radius = 3;
	float rate = 0.75f;
	float time = (float)GetTime() * rate;

	int steps = 40;
	for (int i = 0; i < steps; i++)
	{
		float t = (static_cast<float>(i) / steps) * (2 * PI);
		float x = cosf(t) * radius;
		float y = sinf(t) * radius * 0.5f;

		DrawCircle(Vector2{ x, y }, 0.25f, PINK);
	}

	// sin / cos
	for (float x = -9; x < 9; x += 0.2f)
	{
		float t = time + ((x / 6) * (2 * PI));
		float c = cosf(t) * radius;
		float s = sinf(t) * radius;

		DrawCircle(Vector2{ x, c }, 0.25f, BLUE);
		DrawCircle(Vector2{ x, s }, 0.25f, GREEN);
	}

	float t = time;
	float x = cosf(t) * radius;
	float y = sinf(t) * radius;

	DrawCircle(Vector2{ x, y }, 0.5f, RED);

	float angle = atan2f(y, x);

	m_camera->EndMode();
}

void TrigScene::DrawGUI()
{
}