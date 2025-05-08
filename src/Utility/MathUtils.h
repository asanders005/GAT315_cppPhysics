#pragma once
#include <cstdlib>
#include <algorithm>

namespace EMath
{
	inline float randomf()
	{
		return rand() / (float)RAND_MAX;
	}

	inline float randomf(float max)
	{
		return randomf() * max;
	}

	inline float randomf(float min, float max)
	{
		if (min > max) std::swap(min, max);
		return min + (randomf() * (max - min));
	}

	inline float DegToRad(float degrees)
	{
		return degrees * (PI / 180.0f);
	}

	inline float RadToDeg(float radians)
	{
		return radians * (180.0f / PI);
	}

	template <typename T>
	inline T Clamp(T value, T min, T max)
	{
		return (value < min) ? min : (value > max) ? max : value;
	}

	template <typename T>
	inline T Lerp(T a, T b, float t)
	{
		return a + t * (b - a);
	}
}