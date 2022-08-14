#include "kwee/graphics/Mesh.h"

float rectVerts[] =
{
	 0.5,  0.5,
	 0.5, -0.5,
	-0.5, -0.5,
	-0.5,  0.5
};

int rectInds[] =
{
	0, 1, 2,
	0, 2, 3
};

kwee::Mesh::Mesh()
{
	for (int i = 0; i < 8; i++)
	{
		vertices_.push_back(rectVerts[i]);
	}

	for (int i = 0; i < 6; i++)
	{
		indices_.push_back(rectInds[i]);
	}

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(int), indices_.data(), GL_STATIC_DRAW);

}

std::vector<float> kwee::Mesh::getVertices()
{
	return vertices_;
}

std::vector<int> kwee::Mesh::getIndices()
{
	return indices_;
}

void kwee::Mesh::draw()
{
	glBindVertexArray(vao_);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
}

void kwee::Mesh::free()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
	glDeleteBuffers(1, &ebo_);
}