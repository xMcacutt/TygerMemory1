#pragma once
#include <cmath>

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

	static inline Vector4f Normalize(const Vector4f& vector) {
		float length = std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		if (length == 0.0f) // Avoid division by zero
			return { 0.0f, 0.0f, 0.0f, 1.0f };
		return { vector.x / length, vector.y / length, vector.z / length, vector.w };
	}

	static inline Vector4f Cross(const Vector4f& a, const Vector4f& b) {
		return {
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x,
			a.w
		};
	}
};

