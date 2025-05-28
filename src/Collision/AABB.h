#pragma once
#include "raylib.h"

struct AABB
{
	Vector2 center;
	Vector2 size;

	AABB(const Vector2& center, const Vector2& size) :
		center{ center },
		size{ size }
	{}

	Vector2 extents() const { return { size.x / 2.0f, size.y / 2.0f }; }

	Vector2 min() const { return { center.x - extents().x, center.y - extents().y }; }

	Vector2 max() const { return { center.x + extents().x, center.y + extents().y }; }
};