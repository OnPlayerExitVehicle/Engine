#pragma once
#include <string>
#include <GLM/glm/mat4x4.hpp>
#include "Globals.h"
#include <map>

struct Material;
struct LightMaterial;

enum class UniformKey : int
{
	TransformMatrix,
	ViewMatrix,
	ProjectionMatrix,
	IsTextured,
	ViewPosition,
	Material_Color,
	Material_Ambient,
	Material_Diffuse,
	Material_Specular,
	Material_Shininess,
	LightMaterial_Color,
	LightMaterial_Position,
	LightMaterial_Ambient,
	LightMaterial_Diffuse,
	LightMaterial_Specular,
	SIZE
};

class Shader
{
private:
	unsigned int id;

	static std::map<UniformKey, std::string> uniformNameMap;
	int uniformIds[(int)UniformKey::SIZE];

	std::map<unsigned int, std::string> shaderDirectoryMap;

public:
	Shader();
	void AttachShader(_STRING_CR_ address, unsigned int type);
	void Recompile();

	void Use();
	void Link();
	void SendMatrix(UniformKey key, const glm::mat4& matrix) const;
	void SendMatrix(UniformKey key, const glm::mat3& matrix) const;
	void SendVector(UniformKey key, const glm::vec4& vector) const;
	void SendVector(UniformKey key, const glm::vec3& vector) const;
	void SendVector(UniformKey key, const glm::vec2& vector) const;
	void SendBool(UniformKey key, bool b) const;
	void SendFloat(UniformKey key, float value) const;
	void SendInteger(UniformKey key, int value) const;
	void SendMaterial(const Material& material) const;
	void SendLightMaterial(const LightMaterial& material) const;
};