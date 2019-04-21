#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glew.h>

class GameObject;

struct VertexPos
{
	VertexPos() { x = 0; y = 0; z = 0; }
	VertexPos(float inX, float inY, float inZ) { x = inX; y = inY; z = inZ; }
	VertexPos(float inX, float inY) { x = inX, y = inY, z = 0; }
	float x;
	float y;
	float z;
};

struct VertexCol
{
	VertexCol() { r = 0; g = 0; b = 0; }
	VertexCol(float inR, float inG, float inB) { r = inR; g = inG; b = inB; }
	float r;
	float g;
	float b;
};

struct VertexArray
{
	VertexPos * positions;
	VertexCol * colors;
};

enum VertexAttribs
{
	POS,
	COL,
	NUM_ATTRIBS
};

class Shape
{
public:
	virtual ~Shape();
	virtual void Draw() = 0;
	void DoTransform();

protected:
	Shape() {}
	void InitVAO(int vertCount, VertexArray verts);

	GLuint _VAO;
	int _vertexCount;

private:
	Shape(const Shape& other) {} // disable copy constructor for now
	void operator=(const Shape& other) {} // disable assignment for now

	void UpdateBuffers();

	VertexArray _vertices;
	GLuint _VBOs[VertexAttribs::NUM_ATTRIBS];

};

#endif // !SHAPE_H
