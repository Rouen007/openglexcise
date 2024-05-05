#include "Shader.h"
#include "renderer.h"
#include <fstream>
#include <sstream>
#include <GL/glew.h>

Shader::Shader(const std::string& filepath)
	: m_FilePath(filepath)
	, m_RendererID(0)
{
	ShaderProgramSource source = parseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4)
{
	unsigned location = GetUniformLocation(name);
	GLCall(glUniform4f(location, f1, f2, f3, f4));
}


void Shader::SetUniform1f(const std::string& name, float f1)
{
	unsigned location = GetUniformLocation(name);
	GLCall(glUniform1f(location, f1));
}

void Shader::SetUniform1i(const std::string& name, int i1)
{
	unsigned location = GetUniformLocation(name);
	GLCall(glUniform1i(location, i1));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_LocataionCache.find(name) != m_LocataionCache.end())
	{
		return m_LocataionCache[name];
	}
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform " << name << " doesn't exist\n";
	
	m_LocataionCache[name] = location;
	return location;
}

ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
	std::fstream stream(filepath);
	std::string line;
	std::stringstream ss[2];
	enum class ShaderType {
		NONE = -1,
		VERTEX,
		FRAGMENT
	};
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}

	}
	return { ss[0].str(), ss[1].str() };
}



unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& pixelShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, pixelShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}
