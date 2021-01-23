#ifndef GLBASE_BUFFER_HPP
#define GLBASE_BUFFER_HPP

#include <utility>

namespace gl
{

class buffer
{
public:
	buffer();
	buffer(const buffer&) = delete;
	buffer(buffer&& other) noexcept;

	buffer& operator=(const buffer&) = delete;
	buffer& operator=(buffer&& other) noexcept;

	~buffer();

	GLuint handle() const;

private:
	GLuint m_handle;
};

inline buffer::buffer()
{
	glGenBuffers(1, &m_handle);
}

inline buffer::buffer(buffer&& other) noexcept :
	m_handle(std::exchange(other.m_handle, (GLuint)0))
{
}

inline buffer& buffer::operator=(buffer&& other) noexcept
{
	std::swap(m_handle, other.m_handle);

	return *this;
}

inline buffer::~buffer()
{
	glDeleteBuffers(1, &m_handle);
}

inline GLuint buffer::handle() const
{
	return m_handle;
}

}	// namespace gl

#endif
