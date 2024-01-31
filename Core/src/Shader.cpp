#include "Shader.h"
#include "glad/glad.h"
#include "FileReader.h"
#include <iostream>

std::map<UniformKey, std::string> Shader::uniformNameMap = {
	{UniformKey::TransformMatrix, "MTX_Transform"},
	{UniformKey::ViewMatrix, "MTX_View"},
	{UniformKey::ProjectionMatrix, "MTX_Projection"},
	{UniformKey::Color, "VEC_Color"},
	{UniformKey::IsTextured, "B_IsTextured"}
};

Shader::Shader() : id(glCreateProgram()) { }

void Shader::AttachShader(const std::string& address, unsigned int type)
{
	std::string strShader = FileReader::ReadFile(address);
	const char* cStrShader = &strShader[0];

	int shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &cStrShader, 0);
	glCompileShader(shader_id);
	int compileStatus;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus)
	{
		char error[1024];
		int log_length;
		DEBUG_LOG("[Error] Cannot compile shader: " + address);
		glGetShaderInfoLog(id, 1024, &log_length, error);
		DEBUG_LOG(error);
	}
	glAttachShader(id, shader_id);
}

void Shader::Use()
{
	glUseProgram(id);
}

void Shader::Link()
{
	glLinkProgram(id);

	int size = (int)UniformKey::SIZE;
	for (int i = 0; i < size; i++)
	{
		uniformIds[i] = glGetUniformLocation(id, uniformNameMap[(UniformKey)i].c_str());
	}
}

void Shader::SendMatrix(UniformKey key, const glm::mat4& matrix) const
{
	glUniformMatrix4fv(uniformIds[(int)key], 1, false, &matrix[0][0]);
}

void Shader::SendMatrix(UniformKey key, const glm::mat3& matrix) const
{
	glUniformMatrix3fv(uniformIds[(int)key], 1, false, &matrix[0][0]);
}

void Shader::SendVector(UniformKey key, const glm::vec4& vector) const
{
	glUniform4fv(uniformIds[(int)key], 1, &vector[0]);
}

void Shader::SendVector(UniformKey key, const glm::vec3& vector) const
{
	glUniform3fv(uniformIds[(int)key], 1, &vector[0]);
}

void Shader::SendVector(UniformKey key, const glm::vec2& vector) const
{
	glUniform2fv(uniformIds[(int)key], 1, &vector[0]);
}

void Shader::SendBool(UniformKey key, bool b) const
{
	glUniform1i(uniformIds[(int)key], b);
}