#include "pch.h"
#include "vector3f.h"

Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3f::operator const void* () const {
    return static_cast<const void*>(this);
}

float Vector3f::distance(const Vector3f& other) const {
    return sqrt((other.x - x) * (other.x - x) +
        (other.y - y) * (other.y - y) +
        (other.z - z) * (other.z - z));
}

std::size_t Vector3f::toBytes(unsigned char* buffer) const {
    std::memcpy(buffer, this, sizeof(Vector3f));
    return sizeof(Vector3f);
}

Vector3f Vector3f::fromBytes(const unsigned char* buffer) {
    Vector3f vec;
    std::memcpy(&vec, buffer, sizeof(Vector3f));
    return vec;
}