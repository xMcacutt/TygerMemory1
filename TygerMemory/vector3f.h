#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif

#include <cstddef>  // For std::size_t
#include <cstring>  // For memcpy
#include <cmath>    // For sqrt

class TYGERMEM Vector3f {
public:
	float x, y, z;

	// Constructor
	Vector3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);

	// Implicit conversion to bytes
	operator const void* () const;

	// Distance between two vectors
	float distance(const Vector3f& other) const;

	// Convert the vector to a byte array
	std::size_t toBytes(unsigned char* buffer) const;

	// Create a Vector3 from bytes
	static Vector3f fromBytes(const unsigned char* buffer);
};
