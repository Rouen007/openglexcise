#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"


struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_LocataionCache;
	//cache
public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;
	void Unbind() const;

	// set uniform
	void SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4);
	void SetUniform1f(const std::string& name, float f1);
	void SetUniform1i(const std::string& name, int i1);
	void SetUniformMat4f(const std::string& name, glm::mat4& matrix);
private:
	int GetUniformLocation(const std::string& name);

	ShaderProgramSource parseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& pixelShader);
};