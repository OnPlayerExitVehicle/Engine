#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Globals.h"
#include <iostream>

class MeshRenderer final : public Component
{
private:
	std::shared_ptr<Mesh>	 mesh;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Shader>  shader;
	glm::vec4 color;

	static std::shared_ptr<Shader> defaultShader;
	bool textured;

protected:
	void Render() override;

public:
	static std::shared_ptr<Shader> GetDefaultShader();
	MeshRenderer();
	explicit MeshRenderer(const glm::vec4& color);
	explicit MeshRenderer(std::shared_ptr<Texture> texture);

	void OnGUI() override;

	std::string GetName() override { return typeid(*this).name(); }
};