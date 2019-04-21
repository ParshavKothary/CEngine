#include "CEMath.h"

#ifndef SIMD_TRUE

Vector2::~Vector2() {}
Vector2::Vector2() : Vector2(0, 0) {}
Vector2::Vector2(const Vector2& B) : Vector2(B.x, B.y) {}
Vector2::Vector2(const Vector3& B) : Vector2(B.x, B.y) {}
Vector2::Vector2(float inX, float inY) : x(inX), y(inY) {}
Vector2::Vector2(float inX) : Vector2(inX, 0) {}

Vector3::~Vector3() {}
Vector3::Vector3() : Vector3(0, 0, 0) {}
Vector3::Vector3(const Vector3& B) : Vector3(B.x, B.y, B.z) {}
Vector3::Vector3(const Vector2& B) : Vector3(B.x, B.y, 0) {}
Vector3::Vector3(const Vector2& B, float inZ) : Vector3(B.x, B.y, inZ) {}
Vector3::Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {}
Vector3::Vector3(float inX, float inY) : Vector3(inX, inY, 0) {}
Vector3::Vector3(float inX) : Vector3(inX, 0, 0) {}

#endif // !SIMD_TRUE

