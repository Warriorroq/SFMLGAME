#pragma once
#include "SFML/System.hpp"

namespace sf
{
	Vector2f Normalize(const Vector2f& vector);

	float SqrtLength(const Vector2f& vector);

	float Length(const Vector2f& vector);

	float Distance(Vector2f vector, Vector2f vector2);
}