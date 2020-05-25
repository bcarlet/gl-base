#include "vertex_array.hpp"

#include <utility>

using namespace gl;

vertex_array::vertex_array()
{
	glGenVertexArrays(1, &m_handle);
}

vertex_array::vertex_array(vertex_array&& other) noexcept :
	m_handle(std::exchange(other.m_handle, (GLuint)0))
{
}

vertex_array& vertex_array::operator=(vertex_array&& other) noexcept
{
	std::swap(m_handle, other.m_handle);

	return *this;
}

vertex_array::~vertex_array()
{
	glDeleteVertexArrays(1, &m_handle);
}

void vertex_array::bind() const
{
	glBindVertexArray(m_handle);
}
