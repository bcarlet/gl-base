#ifndef GLBASE_SHADER_HPP
#define GLBASE_SHADER_HPP

#include <iostream>
#include <memory>
#include <stdexcept>

namespace gl
{

class shader
{
public:
	shader(const shader&) = delete;
	shader(shader&& other) noexcept;

	explicit shader(GLenum shader_type);

	// Compile a shader from source. If source_length is less than 0, then
	// source is assumed to be null-terminated.
	shader(const GLchar* source, GLint source_length, GLenum shader_type);

	shader& operator=(const shader&) = delete;
	shader& operator=(shader&& other) noexcept;

	~shader();

	// Compile a shader from source. If source_length is less than 0, then
	// source is assumed to be null-terminated.
	void compile(const GLchar* source, GLint source_length);

	GLuint handle() const;

private:
	GLuint m_handle;
};

inline shader::shader(shader&& other) noexcept :
	m_handle(std::exchange(other.m_handle, (GLuint)0))
{
}

inline shader::shader(GLenum shader_type) :
	m_handle(glCreateShader(shader_type))
{
	if (m_handle == 0)
		throw std::runtime_error("Failed to create shader.");
}

inline shader::shader(const GLchar* source, GLint source_length, GLenum shader_type) :
	shader(shader_type)
{
	compile(source, source_length);
}

inline shader& shader::operator=(shader&& other) noexcept
{
	std::swap(m_handle, other.m_handle);

	return *this;
}

inline shader::~shader()
{
	glDeleteShader(m_handle);
}

inline void shader::compile(const GLchar* source, GLint source_length)
{
	glShaderSource(m_handle, 1, &source, &source_length);
	glCompileShader(m_handle);

	GLint status;
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
#ifndef NDEBUG
		GLint buffer_size;
		glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &buffer_size);

		auto info_log = std::make_unique<GLchar[]>(buffer_size);
		glGetShaderInfoLog(m_handle, buffer_size, nullptr, info_log.get());

		std::cerr << info_log.get() << '\n';
#endif

		throw std::runtime_error("Failed to compile shader.");
	}
}

inline GLuint shader::handle() const
{
	return m_handle;
}

}	// namespace gl

#endif
