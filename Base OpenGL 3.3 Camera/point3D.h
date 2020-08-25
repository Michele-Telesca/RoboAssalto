#pragma once

struct point3D
{
	float		x, y, z;

	point3D() = default;

	point3D(float a, float b, float c) { x = a; y = b; z = c; }

	float& operator [](int i)
	{
		return ((&x)[i]);
	}

	const float& operator [](int i) const
	{
		return ((&x)[i]);
	}
};

