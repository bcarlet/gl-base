#ifndef GLBASE_PROGRAM_HPP
#define GLBASE_PROGRAM_HPP

#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>

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

	GLuint handle() const;

private:
	GLuint m_handle;
};

inline program::program() :
	m_handle(glCreateProgram())
{
	if (m_handle == 0)
		throw std::runtime_error("Failed to create shader program.");
}

inline program::program(program&& other) noexcept :
	m_handle(std::exchange(other.m_handle, (GLuint)0))
{
}

inline program::program(std::initializer_list<GLuint> shaders) :
	program()
{
	link(shaders);
}

inline program& program::operator=(program&& other) noexcept
{
	std::swap(m_handle, other.m_handle);

	return *this;
}

inline program::~program()
{
	glDeleteProgram(m_handle);
}

inline void program::link(std::initializer_list<GLuint> shaders)
{
	for (GLuint shader : shaders)
	{
		glAttachShader(m_handle, shader);
	}

	glLinkProgram(m_handle);

	for (GLuint shader : shaders)
	{
		glDetachShader(m_handle, shader);
	}

	GLint status;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint buffer_size;
		glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &buffer_size);

		auto info_log = std::make_unique<GLchar[]>(buffer_size);
		glGetProgramInfoLog(m_handle, buffer_size, nullptr, info_log.get());

		std::cerr << info_log.get() << '\n';

		throw std::runtime_error("Failed to link shader program.");
	}
}

inline void program::use() const
{
	glUseProgram(m_handle);
}

inline GLuint program::handle() const
{
	return m_handle;
}

}	// namespace gl

#endif
