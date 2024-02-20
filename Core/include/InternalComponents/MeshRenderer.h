#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Globals.h"
#include <iostream>
#include "LightSource.h"

class MeshRenderer : public Component
{
private:
	std::shared_ptr<Mesh>	 mesh;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Shader>  shader;

	static std::shared_ptr<Shader> defaultShader;
	static std::shared_ptr<Shader> lightShader;
	bool textured;
	bool isLight = false;
	Material material;

	friend class LightSource;
protected:
	void Render() override;

public:

	static std::shared_ptr<Shader> GetDefaultShader();
	static std::shared_ptr<Shader> GetLightShader();
	MeshRenderer();
	explicit MeshRenderer(const glm::vec3& color, bool isLight = false);
	explicit MeshRenderer(std::shared_ptr<Texture> texture);
	explicit MeshRenderer(const glm::vec3& color, std::shared_ptr<Shader> shader);
	explicit MeshRenderer(std::shared_ptr<Mesh> mesh, const glm::vec3& color = glm::vec3(1.0f));
	void SetColor(const Vector3& color);

	Material& GetMaterial();

	void OnGUI() override;

	std::string GetName() override { return typeid(*this).name(); }
};