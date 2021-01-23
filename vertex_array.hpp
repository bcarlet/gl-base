#ifndef GLBASE_VERTEX_ARRAY_HPP
#define GLBASE_VERTEX_ARRAY_HPP

#include <utility>

namespace gl
{

class vertex_array
{
public:
	vertex_array();
	vertex_array(const vertex_array&) = delete;
	vertex_array(vertex_array&& other) noexcept;

	vertex_array& operator=(const vertex_array&) = delete;
	vertex_array& operator=(vertex_array&& other) noexcept;

	~vertex_array();

	void bind() const;

	GLuint handle() const;

private:
	GLuint m_handle;
};

inline vertex_array::vertex_array()
{
	glGenVertexArrays(1, &m_handle);
}

inline vertex_array::vertex_array(vertex_array&& other) noexcept :
	m_handle(std::exchange(other.m_handle, (GLuint)0))
{
}

inline vertex_array& vertex_array::operator=(vertex_array&& other) noexcept
{
	std::swap(m_handle, other.m_handle);

	return *this;
}

inline vertex_array::~vertex_array()
{
	glDeleteVertexArrays(1, &m_handle);
}

inline void vertex_array::bind() const
{
	glBindVertexArray(m_handle);
}

inline GLuint vertex_array::handle() const
{
	return m_handle;
}

}	// namespace gl

#endif
