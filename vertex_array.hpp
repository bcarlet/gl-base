#ifndef GL_VERTEX_ARRAY_HPP
#define GL_VERTEX_ARRAY_HPP

#include <GL/glew.h>

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

inline GLuint vertex_array::handle() const
{
	return m_handle;
}

}	// namespace gl

#endif
