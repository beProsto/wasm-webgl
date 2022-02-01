#pragma once

#include "utils/include/utils.hpp"

static uint32_t g_BoundVertexBuffer;

struct Vertex;

class VertexBuffer {
public:
	VertexBuffer() {
		// create a vertex array (vertex descriptor)
		m_VAID = glCreateVertexArray();
		// create an array buffer (the actual vertex buffer)
		m_VBID = glCreateBuffer();

		// we bind it all (initialise the vertex buffer)
		bind();
	}
	VertexBuffer(const Vertex* _mesh) {
		// create a vertex array (vertex descriptor)
		m_VAID = glCreateVertexArray();
		// create an array buffer (the actual vertex buffer)
		m_VBID = glCreateBuffer();

		// feed the mesh to the gpu
		data(_mesh);
	}
	~VertexBuffer() {
		glDeleteVertexArray(m_VAID);
		glDeleteBuffer(m_VBID);
	}

	void data(const Vertex* _mesh) const {
		// make sure it's all bound
		bind();

		// Vertex description - how the vertex is structured
		// 3 floats for position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
		// 2 floats for texture coordinates 
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 3 * sizeof(float));
		// 3 floats for normals
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 5 * sizeof(float));

		// pass data to the buffer
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), (void*)_mesh, GL_STATIC_DRAW);
	}

	void bind() const {
		if(g_BoundVertexBuffer != m_VBID) {
			g_BoundVertexBuffer = m_VBID;

			glBindVertexArray(m_VAID);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBID);
		}
	}

private:
	uint32_t m_VBID, m_VAID;
};


struct Vec3 {
	float x, y, z;
};

struct Vertex {
	Vec3 pos;
	Vec3 col;
};