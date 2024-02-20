#include "Mesh.h"
#include "glad/glad.h"
#include <iostream>

Mesh::Mesh(const std::vector<MeshFactory::TexturedVertex>& vertexVector, const std::vector<unsigned int>& indexVector)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vertexBuffer, indexBuffer;

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexVector.size() * sizeof(MeshFactory::TexturedVertex), vertexVector.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexVector.size() * sizeof(unsigned int), indexVector.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(MeshFactory::TexturedVertex), nullptr);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(MeshFactory::TexturedVertex), reinterpret_cast<const void*>(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(MeshFactory::TexturedVertex), reinterpret_cast<const void*>(sizeof(float) * 5));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	indexCount = indexVector.size();
}

void Mesh::Draw() const
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}