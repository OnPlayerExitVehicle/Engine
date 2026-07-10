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
	std::vector<std::shared_ptr<Mesh>>		meshes;
	std::vector<std::shared_ptr<Texture>>	textures;
    std::vector<Material>                   materials;
	std::shared_ptr<Shader>					shader;

	static std::shared_ptr<Shader> defaultShader;
    static std::shared_ptr<Shader> lightShader;
	bool isLight = false;

	friend class LightSource;
protected:
	void Render() override;

public:

	static std::shared_ptr<Shader> GetDefaultShader();
	static std::shared_ptr<Shader> GetLightShader();
    MeshRenderer(const bool defaultMesh = true);
	explicit MeshRenderer(const glm::vec3& color, bool isLight = false); // Obsolete
	explicit MeshRenderer(std::shared_ptr<Texture> texture); // Obsolete
	explicit MeshRenderer(const glm::vec3& color, std::shared_ptr<Shader> shader);
	explicit MeshRenderer(std::shared_ptr<Mesh> mesh, const glm::vec3& color = glm::vec3(1.0f));
	explicit MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture) noexcept;
    // void SetColor(const Vector3& color);
	void AddMesh(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture);
    void AddMesh(std::shared_ptr<Mesh> mesh, const glm::vec3& color = glm::vec3(1.0f));

    Material& GetFirstMaterial();

	void OnGUI() override;

	std::string GetName() override { return typeid(*this).name(); }
};
