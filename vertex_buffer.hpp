#ifndef GL_VERTEX_BUFFER_HPP
#define GL_VERTEX_BUFFER_HPP

#include <GL/glew.h>

#include "buffer.hpp"

namespace gl
{

class vertex_buffer: public buffer
{
public:
	vertex_buffer(const vertex_buffer&) = delete;
	vertex_buffer(vertex_buffer&& other) noexcept;

	explicit vertex_buffer(GLenum usage = GL_STATIC_DRAW);

	// Create a new buffer with the given size and usage hint. If data is not
	// NULL then it will be copied into the buffer's data store.
	vertex_buffer(GLsizeiptr size, const void* data, GLenum usage);

	vertex_buffer& operator=(const vertex_buffer&) = delete;
	vertex_buffer& operator=(vertex_buffer&& other) noexcept;

	void bind() const;

	// Recreate the buffer's data store. The old store will be orphaned.
	void update(GLsizeiptr size, const void* data);

private:
	GLenum m_usage;
};

}	// namespace gl

#endif
