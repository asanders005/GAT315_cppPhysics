#include "VectorScene.h"
#include "Objects/Body.h"

#include "raymath.h"
#include <time.h>

float Random()
{
	return rand() / (float)RAND_MAX;
}

void VectorScene::Initialize()
{
	srand(time(0));

	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	Body* body = new Body(Vector2{ (Random() * 10) - 5, (Random() * 10) - 5}, Vector2{ 0, 0 }, 0.25f, VIOLET);
	m_head = body;
	m_player = body;

	for (int i = 0; i < 10; i++)
	{
		Color color;
		float r = Random();
		if (r < 0.1f)
			color = BLUE;
		else if (r < 0.2f)
			color = GREEN;
		else if (r < 0.3f)
			color = YELLOW;
		else if (r < 0.4f)
			color = RED;
		else if (r < 0.5f)
			color = ORANGE;
		else if (r < 0.6f)
			color = WHITE;
		else if (r < 0.7f)
			color = DARKGRAY;
		else if (r < 0.8f)
			color = BROWN;
		else if (r < 0.9f)
			color = PINK;
		else
			color = LIGHTGRAY;

		body->next = new Body(Vector2{ (Random() * 10) - 5, (Random() * 10) - 5}, Vector2{ 0, 0 }, 0.25f, color);
		body->next->prev = body;
		body = body->next;
	}

}

void VectorScene::Update()
{
	Body* current = m_head;
	
	// Update the player
	Vector2 direction{ 0, 0 };
	direction.x = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
	direction.y = (IsKeyDown(KEY_W) - IsKeyDown(KEY_S));

	m_player->velocity = Vector2Normalize(direction) * 5;

	while (current)
	{
		if (current != m_player)
		{
			Vector2 direction = Vector2Normalize(m_player->position - current->position);
			current->velocity = direction * 2;
		}

		current->Step(GetFrameTime());
		current = current->next;
	}
}

void VectorScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);

	Body* current = m_head;
	while (current)
	{
		current->Draw(*this);
		current = current->next;
	}

	m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
}
