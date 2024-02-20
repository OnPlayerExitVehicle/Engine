#include "Shader.h"
#include "GLAD/glad.h"
#include "FileReader.h"
#include <iostream>
#include "Material.h"

std::map<UniformKey, std::string> Shader::uniformNameMap = {
	{UniformKey::TransformMatrix, "MTX_Transform"},
	{UniformKey::ViewMatrix, "MTX_View"},
	{UniformKey::ProjectionMatrix, "MTX_Projection"},
	{UniformKey::IsTextured, "B_IsTextured"},
	{UniformKey::ViewPosition, "VEC_ViewPosition"},
	{UniformKey::Material_Color, "material.color"},
	{UniformKey::Material_Ambient, "material.ambient"},
	{UniformKey::Material_Diffuse, "material.diffuse"},
	{UniformKey::Material_Specular, "material.specular"},
	{UniformKey::Material_Shininess, "material.shininess"},
	{UniformKey::LightMaterial_Color, "light.color"},
	{UniformKey::LightMaterial_Position, "light.position"},
	{UniformKey::LightMaterial_Ambient, "light.ambient"},
	{UniformKey::LightMaterial_Diffuse, "light.diffuse"},
	{UniformKey::LightMaterial_Specular, "light.specular"}

};

Shader::Shader() : id(glCreateProgram()) { }

void Shader::AttachShader(const std::string& address, unsigned int type)
{
	std::string strShader = FileReader::ReadFile(address);
	const char* cStrShader = &strShader[0];

	const unsigned int shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &cStrShader, 0);
	glCompileShader(shader_id);
	int compileStatus;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus)
	{
		char error[1024];
		int log_length;
		DEBUG_LOG("[Error] Cannot compile shader: " + address);
		glGetShaderInfoLog(shader_id, 1024, &log_length, error);
		DEBUG_LOG(error);
	}
	glAttachShader(id, shader_id);

	shaderDirectoryMap[shader_id] = address;
}

void Shader::Recompile()
{
	unsigned int new_id = glCreateProgram();

	int count;
	unsigned int shaders[16];
	glGetAttachedShaders(id, 16, &count, shaders);


	for(int i = 0; i < count; i++)
	{
		if(shaderDirectoryMap.contains(shaders[i]))
		{
			const unsigned int shader_id = shaders[i];
			int shader_type;
			glGetShaderiv(shader_id, GL_SHADER_TYPE, &shader_type);
			const unsigned int new_shader_id = glCreateShader(shader_type);

			std::string address = shaderDirectoryMap[shaders[i]];
			//std::cout << "Shader address = " << address << std::endl;
			std::string strShader = FileReader::ReadFile(address);
			const char* cStrShader = strShader.data();

			glShaderSource(new_shader_id, 1, &cStrShader, 0);
			glCompileShader(new_shader_id);
			int compileStatus;
			glGetShaderiv(new_shader_id, GL_COMPILE_STATUS, &compileStatus);
			if (!compileStatus)
			{
				char error[1024];
				int log_length;
				DEBUG_LOG("[Error] Cannot compile shader: " + address);
				glGetShaderInfoLog(new_shader_id, 1024, &log_length, error);
				DEBUG_LOG(error);
			}
			glAttachShader(new_id, new_shader_id);

			shaderDirectoryMap[new_shader_id] = address;
			shaderDirectoryMap.erase(shader_id);
		}
	}

	glDeleteProgram(id);
	id = new_id;

	Link();
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

void Shader::SendFloat(UniformKey key, float value) const
{
	glUniform1f(uniformIds[(int)key], value);
}

void Shader::SendInteger(UniformKey key, int value) const
{
	glUniform1i(uniformIds[(int)key], value);
}

void Shader::SendMaterial(const Material& material) const
{
	glUniform3fv(uniformIds[(int)UniformKey::Material_Color], 1, (float*)&material.color);
	glUniform1f(uniformIds[(int)UniformKey::Material_Ambient], material.ambient);
	glUniform1f(uniformIds[(int)UniformKey::Material_Diffuse], material.diffuse);
	glUniform1f(uniformIds[(int)UniformKey::Material_Specular], material.specular);
	glUniform1i(uniformIds[(int)UniformKey::Material_Shininess], material.shininess);
}

void Shader::SendLightMaterial(const LightMaterial& material) const
{
	glUniform1f(uniformIds[(int)UniformKey::LightMaterial_Ambient], material.ambient);
	glUniform1f(uniformIds[(int)UniformKey::LightMaterial_Diffuse], material.diffuse);
	glUniform1f(uniformIds[(int)UniformKey::LightMaterial_Specular], material.specular);
}