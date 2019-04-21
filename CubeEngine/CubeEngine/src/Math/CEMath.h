#pragma once

#ifndef CEngineMATH_H
#define CEngineMATH_H

#include <math.h>

#define DEG2RAD(x) (x * 3.141592653589793 / 180.0)

//#define SIMD_TRUE

class Vector2;
class Vector3;

#ifdef SIMD_TRUE

#include <smmintrin.h>

class Vector2
{
public:
	__m128 _vec;
	Vector2() : Vector2(0, 0) {}
	Vector2(float x) : Vector2(x, 0) {}
	Vector2(const Vector3& other) : Vector2(other.getX(), other.getY()) {}

	Vector2(float x, float y)
	{
		this->_vec = _mm_setr_ps(x, y, 0, 0);
	}

	Vector2(const __m128 _otherVec)
	{
		this->_vec = _otherVec;
	}

	Vector2(const Vector2 & other)
	{
		this->_vec = other._vec;
	}

	~Vector2() {}

	_forceinline float getX() const { return this->_vec.m128_f32[0]; }
	_forceinline float getY() const { return this->_vec.m128_f32[1]; }

	_forceinline void setX(float val)
	{
		float y = this->_vec.m128_f32[1];
		this->_vec = _mm_setr_ps(val, y, 0, 0);
	}

	_forceinline void setY(float val)
	{
		float x = this->_vec.m128_f32[0];
		this->_vec = _mm_setr_ps(x, val, 0, 0);
	}

	_forceinline void setVec(float x, float y)
	{
		this->_vec = _mm_setr_ps(x, y, 0, 0);
	}


	_forceinline Vector2 operator+(const Vector2& other) const
	{
		return Vector2(_mm_add_ps(this->_vec, other._vec));
	}

	_forceinline Vector2 operator-(const Vector2& other) const
	{
		return Vector2(_mm_sub_ps(this->_vec, other._vec));
	}

	_forceinline Vector2 operator-() const
	{
		return Vector2(-this->_vec.m128_f32[0], -this->_vec.m128_f32[1]);
	}

	_forceinline Vector2 operator*(const Vector2& other) const
	{
		return Vector2(_mm_mul_ps(this->_vec, other._vec));
	}

	_forceinline Vector2 operator/(const Vector2& other) const
	{
		return Vector2(_mm_div_ps(this->_vec, other._vec));
	}

	_forceinline Vector2 operator*(float mult) const
	{
		__m128 temp = _mm_set1_ps(mult);
		return Vector2(_mm_mul_ps(this->_vec, temp));
	}

	_forceinline Vector2 operator/(float mult) const
	{
		__m128 temp = _mm_set1_ps(1 / mult);
		return Vector2(_mm_mul_ps(this->_vec, temp));
	}

	_forceinline float dot(const Vector2& rhs) const
	{
		__m128 temp = _mm_mul_ps(this->_vec, rhs._vec); // [x y z] * [x y z]
		Vector2 tempV(temp);

		return Vector2(tempV).getX() + Vector2(tempV).getY();
	}

	_forceinline Vector2 cross(const Vector2& rhs) const
	{
		__m128 shuffleL1 = _mm_shuffle_ps(this->_vec, this->_vec, _MM_SHUFFLE(3, 0, 2, 1)); // create vec4 that is [y z x w] of lhs(to later multiply)
		__m128 shuffleL2 = _mm_shuffle_ps(this->_vec, this->_vec, _MM_SHUFFLE(3, 1, 0, 2)); // [z x y w] of lhs
		__m128 shuffleR1 = _mm_shuffle_ps(rhs._vec, rhs._vec, _MM_SHUFFLE(3, 1, 0, 2));  // [z x y w] of rhs
		__m128 shuffleR2 = _mm_shuffle_ps(rhs._vec, rhs._vec, _MM_SHUFFLE(3, 0, 2, 1));  // [y z x w] of rhs

		return Vector2(_mm_sub_ps(_mm_mul_ps(shuffleL1, shuffleR1), _mm_mul_ps(shuffleL2, shuffleR2))); // [y z x] * [z x y] - [z x y] * [y z x]
	}

	_forceinline Vector2& operator=(const Vector2& other)
	{
		this->_vec = other._vec;
		return *this;
	}

	_forceinline Vector2& operator+=(const Vector2& other)
	{
		this->_vec = _mm_add_ps(this->_vec, other._vec);
		return *this;
	}

	_forceinline Vector2& operator-=(const Vector2& other)
	{
		this->_vec = _mm_sub_ps(this->_vec, other._vec);
		return *this;
	}

	_forceinline Vector2& operator*=(const Vector2& other)
	{
		this->_vec = _mm_mul_ps(this->_vec, other._vec);
		return *this;
	}

	_forceinline Vector2& operator/=(const Vector2& other)
	{
		this->_vec = _mm_div_ps(this->_vec, other._vec);
		return *this;
	}

	_forceinline Vector2& operator*=(float mult)
	{
		__m128 temp = _mm_set1_ps(mult);
		this->_vec = _mm_mul_ps(this->_vec, temp);
		return *this;
	}

	_forceinline Vector2& operator/=(float mult)
	{
		__m128 temp = _mm_set1_ps(1 / mult);
		this->_vec = _mm_mul_ps(this->_vec, temp);
		return *this;
	}

};

class Vector3
{
public:
	__m128 _vec;

	Vector3() : Vector3(0, 0, 0) {}
	Vector3(float x) : Vector3(x, 0, 0) {}
	Vector3(float x, float y) : Vector3(x, y, 0) {}
	Vector3(const Vector2& other) : Vector3(other.getX(), other.getY(), 0) {}
	Vector3(const Vector2& other, float z) : Vector3(other.getX(), other.getY(), z) {}

	Vector3(float x, float y, float z)
	{
		this->_vec = _mm_setr_ps(x, y, z, 0);
	}

	Vector3(const __m128 _otherVec)
	{
		this->_vec = _otherVec;
	}

	Vector3(const Vector3 & other)
	{
		this->_vec = other._vec;
	}

	~Vector3() {}

	
	_forceinline float getX() const { return this->_vec.m128_f32[0]; }
	_forceinline float getY() const { return this->_vec.m128_f32[1]; }
	_forceinline float getZ() const { return this->_vec.m128_f32[2]; }

	_forceinline void setX(float val)
	{
		float y = this->_vec.m128_f32[1];
		float z = this->_vec.m128_f32[2];
		this->_vec = _mm_setr_ps(val, y, z, 0);
	}

	_forceinline void setY(float val)
	{
		float x = this->_vec.m128_f32[0];
		float z = this->_vec.m128_f32[2];
		this->_vec = _mm_setr_ps(x, val, z, 0);
	}

	_forceinline void setZ(float val)
	{
		float x = this->_vec.m128_f32[0];
		float y = this->_vec.m128_f32[1];
		this->_vec = _mm_setr_ps(x, y, val, 0);
	}

	_forceinline void setVec(float x, float y, float z)
	{
		this->_vec = _mm_setr_ps(x, y, z, 0);
	}

	_forceinline Vector3 operator+(const Vector3& other) const
	{
		return Vector3(_mm_add_ps(this->_vec, other._vec));
	}

	_forceinline Vector3 operator-(const Vector3& other) const
	{
		return Vector3(_mm_sub_ps(this->_vec, other._vec));
	}

	_forceinline Vector3 operator-() const
	{
		return Vector3(-this->_vec.m128_f32[0], -this->_vec.m128_f32[1], -this->_vec.m128_f32[2]);
	}

	_forceinline Vector3 operator*(const Vector3& other) const
	{
		return Vector3(_mm_mul_ps(this->_vec, other._vec));
	}

	_forceinline Vector3 operator/(const Vector3& other) const
	{
		return Vector3(_mm_div_ps(this->_vec, other._vec));
	}

	_forceinline Vector3 operator*(float mult) const
	{
		__m128 temp = _mm_set1_ps(mult);
		return Vector3(_mm_mul_ps(this->_vec, temp));
}

	_forceinline Vector3 operator/(float mult) const
	{
		__m128 temp = _mm_set1_ps(1 / mult);
		return Vector3(_mm_mul_ps(this->_vec, temp));
	}

	_forceinline float dot(const Vector3& rhs) const
	{
		__m128 temp = _mm_mul_ps(this->_vec, rhs._vec); // [x y z] * [x y z]
		temp = _mm_hadd_ps(temp, temp); // [x + y, y + z
		temp = _mm_hadd_ps(temp, temp);

		return Vector3(temp).getX();
	}

	_forceinline Vector3 cross(const Vector3& rhs) const
	{
		__m128 shuffleL1 = _mm_shuffle_ps(this->_vec, this->_vec, _MM_SHUFFLE(3, 0, 2, 1)); // create vec4 that is [y z x w] of lhs(to later multiply)
		__m128 shuffleL2 = _mm_shuffle_ps(this->_vec, this->_vec, _MM_SHUFFLE(3, 1, 0, 2)); // [z x y w] of lhs
		__m128 shuffleR1 = _mm_shuffle_ps(rhs._vec, rhs._vec, _MM_SHUFFLE(3, 1, 0, 2));  // [z x y w] of rhs
		__m128 shuffleR2 = _mm_shuffle_ps(rhs._vec, rhs._vec, _MM_SHUFFLE(3, 0, 2, 1));  // [y z x w] of rhs

		return Vector3(_mm_sub_ps(_mm_mul_ps(shuffleL1, shuffleR1), _mm_mul_ps(shuffleL2, shuffleR2))); // [y z x] * [z x y] - [z x y] * [y z x]
	}

	_forceinline Vector3& operator=(const Vector3& other)
	{
		this->_vec = other._vec;
		return *this;
	}

	_forceinline Vector3& operator+=(const Vector3& other)
	{
		this->_vec = _mm_add_ps(this->_vec, other._vec);
		return *this;
	}

	_forceinline Vector3& operator-=(const Vector3& other)
	{
		this->_vec = _mm_sub_ps(this->_vec, other._vec);
		return *this;
	}

	_forceinline Vector3& operator*=(const Vector3& other)
	{
		this->_vec = _mm_mul_ps(this->_vec, other._vec);
		return *this;
	}

	_forceinline Vector3& operator/=(const Vector3& other)
	{
		this->_vec = _mm_div_ps(this->_vec, other._vec);
		return *this;
	}

	_forceinline Vector3& operator*=(float mult)
	{
		__m128 temp = _mm_set1_ps(mult);
		this->_vec = _mm_mul_ps(this->_vec, temp);
		return *this;
	}

	_forceinline Vector3& operator/=(float mult)
	{
		__m128 temp = _mm_set1_ps(1 / mult);
		this->_vec = _mm_mul_ps(this->_vec, temp);
		return *this;
	}

};

class Transform2D {
	
};

#else

class Vector2
{
public:
	float x;
	float y;

	~Vector2();
	Vector2();
	Vector2(const Vector2& B);
	Vector2(const Vector3& B);
	Vector2(float inX, float inY);
	Vector2(float inX);

	Vector2 operator+(const Vector2& B) const { return Vector2(x + B.x, y + B.y); }
	Vector2 operator-(const Vector2& B) const { return Vector2(x - B.x, y - B.y); }
	Vector2 operator-() const { return Vector2(-x, -y); }
	Vector2 operator*(const Vector2& B) const { return Vector2(x * B.x, y * B.y); }
	Vector2 operator/(const Vector2& B) const { return Vector2(x / B.x, y / B.y); }
	Vector2 operator*(float mult) const { return Vector2(x * mult, y * mult); }
	Vector2 operator/(float mult) const { return Vector2(x / mult, y / mult); }
	float cross(const Vector2& B) const { return ((x * B.y) - (y * B.x)); }
	float dot(const Vector2& B) const { return ((x * B.x) + (y * B.y)); }

	Vector2& operator=(const Vector2& B)
	{
		x = B.x;
		y = B.y;
		return *this;
	}
	Vector2& operator+=(const Vector2& B)
	{
		x += B.x;
		y += B.y;
		return *this;
	}
	Vector2& operator-=(const Vector2& B)
	{
		x -= B.x;
		y -= B.y;
		return *this;
	}
	Vector2& operator*=(const Vector2& B)
	{
		x *= B.x;
		y *= B.y;
		return *this;
	}
	Vector2& operator/=(const Vector2& B)
	{
		x /= B.x;
		y /= B.y;
		return *this;
	}
	Vector2& operator*=(float mult)
	{
		x *= mult;
		y *= mult;
		return *this;
	}
	Vector2& operator/=(float mult)
	{
		mult = 1 / mult;
		x *= mult;
		y *= mult;
		return *this;
	}

};

class Vector3
{
public:
	float x;
	float y;
	float z;

	~Vector3();
	Vector3();
	Vector3(const Vector3& B);
	Vector3(const Vector2& B);
	Vector3(const Vector2& B, float inZ);
	Vector3(float inX, float inY, float inZ);
	Vector3(float inX, float inY);
	Vector3(float inX);

	Vector3 operator+(const Vector3& B) const { return Vector3(x + B.x, y + B.y, z + B.z); }
	Vector3 operator-(const Vector3& B) const { return Vector3(x - B.x, y - B.y, z - B.z); }
	Vector3 operator-() const { return Vector3(-x, -y, -z); }
	Vector3 operator*(const Vector3& B) const { return Vector3(x * B.x, y * B.y, z * B.z); }
	Vector3 operator/(const Vector3& B) const { return Vector3(x / B.x, y / B.y, z / B.z); }
	Vector3 operator*(float mult) const { return Vector3(x * mult, y * mult, z * mult); }
	Vector3 operator/(float mult) const { return Vector3(x / mult, y / mult, z / mult); }
	Vector3 cross(const Vector3& B) const { return Vector3((y * B.z) - (z * B.y), (z * B.x) - (x * B.z), (x * B.y) - (y * B.x)); }
	float dot(const Vector3& B) const  { return ((x * B.x) + (y * B.y) + (z * B.z)); }

	Vector3& operator=(const Vector3& B)
	{
		x = B.x;
		y = B.y;
		z = B.z;
		return *this;
	}
	Vector3& operator+=(const Vector3& B)
	{
		x += B.x;
		y += B.y;
		z += B.z;
		return *this;
	}
	Vector3& operator-=(const Vector3& B)
	{
		x -= B.x;
		y -= B.y;
		z -= B.z;
		return *this;
	}
	Vector3& operator*=(const Vector3& B)
	{
		x *= B.x;
		y *= B.y;
		z *= B.z;
		return *this;
	}
	Vector3& operator/=(const Vector3& B)
	{
		x /= B.x;
		y /= B.y;
		z /= B.z;
		return *this;
	}
	Vector3& operator*=(float mult)
	{
		x *= mult;
		y *= mult;
		z *= mult;
		return *this;
	}
	Vector3& operator/=(float mult)
	{
		mult = 1 / mult;
		x *= mult;
		y *= mult;
		z *= mult;
		return *this;
	}

};

class Transform2D
{
private:
	Vector3 row1;
	Vector3 row2;

	void recalculate()
	{
		float radRot = DEG2RAD(rotation);
		float cosRot = cosf(radRot);
		float sinRot = sinf(radRot);

		row1.x = cosRot * scale.x;
		row1.y = -sinRot * scale.y;
		row1.z = position.x;
		
		row2.x = sinRot * scale.x;
		row2.y = cosRot * scale.y;
		row2.z = position.y;
	}

public:
	Vector2 position;
	Vector2 scale;
	float rotation; // z rotation in degrees

	Transform2D() : position(0, 0), scale(1, 1), rotation(0) {}
	Transform2D(Vector2 translation) : position(translation), scale(1, 1), rotation(0) {}
	Transform2D(Vector2 translation, Vector2 inScale) : position(translation), scale(inScale), rotation(0) {}
	Transform2D(Vector2 translation, Vector2 inScale, float inRot) : position(translation), scale(inScale), rotation(inRot) {}
	Transform2D(const Transform2D& B) : position(B.position), scale(B.scale), rotation(B.rotation) {}
	~Transform2D() {}

	Transform2D operator*(const Transform2D& B)
	{
		recalculate();
		Transform2D toRet;
		
		Vector3 Bx(B.row1.x, B.row2.x, 0);
		Vector3 By(B.row1.y, B.row2.y, 0);
		Vector3 Bz(B.row1.z, B.row2.z, 1);

		toRet.row1.x = row1.dot(Bx);
		toRet.row1.y = row1.dot(By);
		toRet.row1.z = row1.dot(Bz);

		toRet.row2.x = row2.dot(Bx);
		toRet.row2.y = row2.dot(By);
		toRet.row2.z = row2.dot(Bz);

		return toRet;
	}

	Transform2D& operator*=(const Transform2D& B)
	{
		recalculate();
		Vector3 Bx(B.row1.x, B.row2.x, 0);
		Vector3 By(B.row1.y, B.row2.y, 0);
		Vector3 Bz(B.row1.z, B.row2.z, 1);

		row1 = Vector3(row1.dot(Bx), row1.dot(By), row1.dot(Bz));
		row2 = Vector3(row2.dot(Bx), row2.dot(By), row2.dot(Bz));

		return *this;
	}

	Vector2 operator*(const Vector2& vec2)
	{
		recalculate();
		Vector3 vec3(vec2, 1);
		Vector2 toRet;

		toRet.x = row1.dot(vec3);
		toRet.y = row2.dot(vec3);

		return toRet;
	}
};

#endif //SIMDTRUE

#endif // !CEngineMATH_H
