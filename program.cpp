#include "program.hpp"

#include <stdexcept>
#include <iostream>
#include <memory>

using namespace gl;

program::program() :
	m_handle(glCreateProgram())
{
	if (m_handle == 0)
		throw std::runtime_error("Failed to create shader program.");
}

program::program(program&& other) noexcept :
	m_handle(std::exchange(other.m_handle, (GLuint)0))
{
}

program::program(std::initializer_list<GLuint> shaders) :
	program()
{
	try
	{
		link(shaders);
	}
	catch (...)
	{
		glDeleteProgram(m_handle);
		throw;
	}
}

program& program::operator=(program&& other) noexcept
{
	std::swap(m_handle, other.m_handle);

	return *this;
}

program::~program()
{
	glDeleteProgram(m_handle);
}

void program::link(std::initializer_list<GLuint> shaders)
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

void program::use() const
{
	glUseProgram(m_handle);
}

GLint program::uniform_location(const GLchar* name) const
{
	return glGetUniformLocation(m_handle, name);
}
