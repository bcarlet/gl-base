#include "vertex_buffer.hpp"

#include <utility>

using namespace gl;

vertex_buffer::vertex_buffer(vertex_buffer&& other) noexcept :
	buffer(std::move(other)),
	m_usage(other.m_usage)
{
}

vertex_buffer::vertex_buffer(GLenum usage) :
	m_usage(usage)
{
}

vertex_buffer::vertex_buffer(GLsizeiptr size, const void* data, GLenum usage) :
	vertex_buffer(usage)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

vertex_buffer& vertex_buffer::operator=(vertex_buffer&& other) noexcept
{
	buffer::operator=(std::move(other));
	m_usage = other.m_usage;

	return *this;
}

void vertex_buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, handle());
}

void vertex_buffer::update(GLsizeiptr size, const void* data)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, m_usage);	// orphan buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
