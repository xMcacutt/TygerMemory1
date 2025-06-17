#pragma once
struct Vector4f
{
	float x, y, z, w;

	Vector4f operator*(Vector4f const rhs) const {
		return { x * rhs.x,
				 y * rhs.y,
				 z * rhs.z,
				 w };
	};
	Vector4f operator+(Vector4f const rhs) const {
		return { x + rhs.x,
				 y + rhs.y,
				 z + rhs.z,
				 w };
	};
	Vector4f operator-(Vector4f const rhs) const {
		return { x - rhs.x,
				 y - rhs.y,
				 z - rhs.z,
				 w };
	};
	Vector4f operator/(Vector4f const rhs) const {
		return { x / rhs.x,
				 y / rhs.y,
				 z / rhs.z,
				 w };
	};
	Vector4f operator*(float const rhs) const {
		return { x * rhs,
				 y * rhs,
				 z * rhs,
				 w };
	};
};

