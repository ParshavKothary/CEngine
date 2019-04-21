#include "Cube.h"

Cube::Cube(Vector2 center, Vector2 scale, float rotation)
{
	VertexArray mArray;
	mArray.positions = new VertexPos[4];
	mArray.colors = new VertexCol[4];
	
	Vector2 topLeft = center + (Vector2(-0.5f, 0.5f) * scale);
	Vector2 topRight = center + (Vector2(0.5f, 0.5f) * scale);
	Vector2 botLeft = center + (Vector2(-0.5f, -0.5f) * scale);
	Vector2 botRight = center + (Vector2(0.5f, -0.5f) * scale);

#ifdef SIMD_TRUE

	mArray.positions[0] = VertexPos(topLeft.getX(), topLeft.getY());
	mArray.positions[1] = VertexPos(topRight.getX(), topRight.getY());
	mArray.positions[2] = VertexPos(botLeft.getX(), botLeft.getY());
	mArray.positions[3] = VertexPos(botRight.getX(), botRight.getY());

#else

	mArray.positions[0] = VertexPos(topLeft.x, topLeft.y);
	mArray.positions[1] = VertexPos(topRight.x, topRight.y);
	mArray.positions[2] = VertexPos(botLeft.x, botLeft.y);
	mArray.positions[3] = VertexPos(botRight.x, botRight.y);

#endif
	mArray.colors[0] = VertexCol(1, 0, 0);
	mArray.colors[1] = VertexCol(0, 1, 0);
	mArray.colors[2] = VertexCol(0, 0, 1);
	mArray.colors[3] = VertexCol(0, 1, 1);

	InitVAO(4, mArray);
}

void Cube::Draw()
{
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, _vertexCount);
	glBindVertexArray(0);
}