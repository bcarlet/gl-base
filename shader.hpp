#ifndef GL_SHADER_HPP
#define GL_SHADER_HPP

#include <GL/glew.h>

namespace gl
{

class shader
{
public:
	shader(const shader&) = delete;
	shader(shader&& other) noexcept;

	explicit shader(GLenum shader_type);

	// Compile a shader from source. If source_length is less than 0 then source
	// is assumed to be null-terminated.
	shader(const GLchar* source, GLint source_length, GLenum shader_type);

	shader& operator=(const shader&) = delete;
	shader& operator=(shader&& other) noexcept;

	~shader();

	// Compile a shader from source. If source_length is less than 0 then source
	// is assumed to be null-terminated.
	void compile(const GLchar* source, GLint source_length);

	GLuint handle() const;

private:
	GLuint m_handle;
};

inline GLuint shader::handle() const
{
	return m_handle;
}

}	// namespace gl

#endif
