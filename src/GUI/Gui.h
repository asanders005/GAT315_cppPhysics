#pragma once
#include "Objects/World.h"
#include "Scene/Scene.h"
#include "raylib.h"

class Gui
{
public:
	static void Update();
	static void Draw();

	static struct Body* GetBodyIntersect(const Vector2& position, bodies_t& bodies, const SceneCamera& camera);

public:
	inline static bool mouseOverGUI{ false };
	inline static bool PhysicsWindowActive{ true };
	inline static bool TypeDropdownEditMode{ false };
	
	inline static int bodyType{ 0 };
	inline static float bodySize{ 0.25f };
	inline static float bodyMass{ 1 };
	inline static float bodyGravityScale{ 1 };
	inline static float bodyDamping{ 0.5f };
	inline static float bodyRestitution{ 0.5f };
};