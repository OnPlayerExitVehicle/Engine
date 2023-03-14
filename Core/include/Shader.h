#pragma once
#include <string>
#include <GLM/glm/mat4x4.hpp>
#include "Globals.h"
#include <map>

enum class UniformKey : int
{
	TransformMatrix,
	ViewMatrix,
	ProjectionMatrix,
	Color,
	IsTextured,
	SIZE
};

class Shader
{
private:
	unsigned int id;

	static std::map<UniformKey, std::string> uniformNameMap;
	unsigned int uniformIds[(int)UniformKey::SIZE];

public:
	Shader();
	void AttachShader(_STRING_CR_ address, unsigned int type);

	void Use();
	void Link();
	void SendMatrix(UniformKey key, const glm::mat4& matrix) const;
	void SendMatrix(UniformKey key, const glm::mat3& matrix) const;
	void SendVector(UniformKey key, const glm::vec4& vector) const;
	void SendVector(UniformKey key, const glm::vec3& vector) const;
	void SendVector(UniformKey key, const glm::vec2& vector) const;
	void SendBool(UniformKey key, bool b) const;
};