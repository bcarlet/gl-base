#ifndef GL_PROGRAM_HPP
#define GL_PROGRAM_HPP

#include <GL/glew.h>
#include <initializer_list>

namespace gl
{

class program
{
public:
	program();
	program(const program&) = delete;
	program(program&& other) noexcept;

	program(std::initializer_list<GLuint> shaders);

	program& operator=(const program&) = delete;
	program& operator=(program&& other) noexcept;

	~program();

	void link(std::initializer_list<GLuint> shaders);

	void use() const;

	GLint uniform_location(const GLchar* name) const;

	GLuint handle() const;

private:
	GLuint m_handle;
};

inline GLuint program::handle() const
{
	return m_handle;
}

}	// namespace gl

#endif
