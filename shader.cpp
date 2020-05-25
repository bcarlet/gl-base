#include "shader.hpp"

#include <stdexcept>
#include <iostream>
#include <memory>

using namespace gl;

shader::shader(shader&& other) noexcept :
	m_handle(std::exchange(other.m_handle, (GLuint)0))
{
}

shader::shader(GLenum shader_type) :
	m_handle(glCreateShader(shader_type))
{
	if (m_handle == 0)
		throw std::runtime_error("Failed to create shader.");
}

shader::shader(const GLchar* source, GLint source_length, GLenum shader_type) :
	shader(shader_type)
{
	try
	{
		compile(source, source_length);
	}
	catch (...)
	{
		glDeleteShader(m_handle);
		throw;
	}
}

shader& shader::operator=(shader&& other) noexcept
{
	std::swap(m_handle, other.m_handle);

	return *this;
}

shader::~shader()
{
	glDeleteShader(m_handle);
}

void shader::compile(const GLchar* source, GLint source_length)
{
	glShaderSource(m_handle, 1, &source, &source_length);
	glCompileShader(m_handle);

	GLint status;
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint buffer_size;
		glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &buffer_size);

		auto info_log = std::make_unique<GLchar[]>(buffer_size);
		glGetShaderInfoLog(m_handle, buffer_size, nullptr, info_log.get());

		std::cerr << info_log.get() << '\n';

		throw std::runtime_error("Failed to compile shader.");
	}
}
