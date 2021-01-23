#ifndef GLBASE_VERTEX_BUFFER_HPP
#define GLBASE_VERTEX_BUFFER_HPP

#include <utility>

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

inline vertex_buffer::vertex_buffer(vertex_buffer&& other) noexcept :
	buffer(std::move(other)),
	m_usage(other.m_usage)
{
}

inline vertex_buffer::vertex_buffer(GLenum usage) :
	m_usage(usage)
{
}

inline vertex_buffer::vertex_buffer(GLsizeiptr size, const void* data, GLenum usage) :
	vertex_buffer(usage)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

inline vertex_buffer& vertex_buffer::operator=(vertex_buffer&& other) noexcept
{
	buffer::operator=(std::move(other));
	m_usage = other.m_usage;

	return *this;
}

inline void vertex_buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, handle());
}

inline void vertex_buffer::update(GLsizeiptr size, const void* data)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, m_usage);	// orphan buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

}	// namespace gl

#endif
