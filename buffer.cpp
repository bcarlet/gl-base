#include "buffer.hpp"

#include <utility>

using namespace gl;

buffer::buffer()
{
	glGenBuffers(1, &m_handle);
}

buffer::buffer(buffer&& other) noexcept :
	m_handle(std::exchange(other.m_handle, (GLuint)0))
{
}

buffer& buffer::operator=(buffer&& other) noexcept
{
	std::swap(m_handle, other.m_handle);

	return *this;
}

buffer::~buffer()
{
	glDeleteBuffers(1, &m_handle);
}
