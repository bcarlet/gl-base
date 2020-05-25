#ifndef GL_BUFFER_HPP
#define GL_BUFFER_HPP

#include <GL/glew.h>

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

inline GLuint buffer::handle() const
{
	return m_handle;
}

}	// namespace gl

#endif
