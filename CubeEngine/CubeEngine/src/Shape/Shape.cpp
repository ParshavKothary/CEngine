#include "Shape.h"

void Shape::InitVAO(int vertCount, VertexArray verts)
{
	_vertices = verts;
	_vertexCount = vertCount;

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(VertexAttribs::NUM_ATTRIBS, _VBOs);

	glBindBuffer(GL_ARRAY_BUFFER, _VBOs[VertexAttribs::POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPos) * _vertexCount, _vertices.positions, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(VertexAttribs::POS);
	glVertexAttribPointer(VertexAttribs::POS, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _VBOs[VertexAttribs::COL]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexCol) * _vertexCount, _vertices.colors, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(VertexAttribs::COL);
	glVertexAttribPointer(VertexAttribs::COL, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindVertexArray(0);
}

Shape::~Shape()
{
	glDeleteBuffers(VertexAttribs::NUM_ATTRIBS, _VBOs);
	glDeleteVertexArrays(1, &_VAO);
	delete[] _vertices.positions;
	delete[] _vertices.colors;
}

void Shape::DoTransform()
{
	UpdateBuffers();
}

void Shape::UpdateBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, _VBOs[VertexAttribs::POS]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexPos) * _vertexCount, _vertices.positions);
}
