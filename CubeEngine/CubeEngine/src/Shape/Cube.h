#pragma once

#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"
#include <Math/CEMath.h>

class Cube : public Shape
{
public:
	Cube(Vector2 center, Vector2 scale, float rotation);
	~Cube() {};
	
	void Draw();
protected:
};

#endif // !CUBE_H
