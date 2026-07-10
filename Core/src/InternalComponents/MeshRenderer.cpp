#include "MeshRenderer.h"
#include "MeshFactory.h"
#include <glad/glad.h>
#include "Transform.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "Material.h"
#include "GameObject.h"

std::shared_ptr<Shader> MeshRenderer::defaultShader;
std::shared_ptr<Shader> MeshRenderer::lightShader;

std::shared_ptr<Shader> MeshRenderer::GetDefaultShader()
{
	if (!defaultShader)
	{
		defaultShader = std::make_shared<Shader>();
		defaultShader->AttachShader(SHADERS_DIRECTORY"vertex.glsl", GL_VERTEX_SHADER);
		defaultShader->AttachShader(SHADERS_DIRECTORY"fragment.glsl", GL_FRAGMENT_SHADER);
		defaultShader->Link();
	}

	return defaultShader;
}

std::shared_ptr<Shader> MeshRenderer::GetLightShader()
{
	if (!lightShader)
	{
		lightShader = std::make_shared<Shader>();
		lightShader->AttachShader(SHADERS_DIRECTORY"vertexLight.glsl", GL_VERTEX_SHADER);
		lightShader->AttachShader(SHADERS_DIRECTORY"fragmentLight.glsl", GL_FRAGMENT_SHADER);
		lightShader->Link();
	}

	return lightShader;
}

MeshRenderer::MeshRenderer(const bool defaultMesh) :
    shader(GetDefaultShader())
{
	if(defaultMesh)
	{
		meshes.push_back(MeshFactory::GetMesh(MeshType::Cube));
        textures.push_back(nullptr);
        materials.push_back({});
	}
}

MeshRenderer::MeshRenderer(const glm::vec3& color, bool isLight) :
    isLight(isLight)
{ 
	meshes.push_back(MeshFactory::GetMesh(MeshType::Cube));
    textures.push_back(nullptr);
    materials.push_back({color});

	if (isLight)
	{
		shader = GetLightShader();
	}
	else
	{
		shader = GetDefaultShader();
	}
}

MeshRenderer::MeshRenderer(std::shared_ptr<Texture> texture) :
    shader(GetDefaultShader())
{
	meshes.push_back(MeshFactory::GetMesh(MeshType::Cube));
	textures.push_back(std::move(texture));
    materials.push_back({});
}

MeshRenderer::MeshRenderer(const glm::vec3& color, std::shared_ptr<Shader> shader) :
    shader(std::move(shader))
{
	meshes.push_back(MeshFactory::GetMesh(MeshType::Cube));
    textures.push_back(nullptr);
    materials.push_back({});
}

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, const glm::vec3& color) :
    shader(GetDefaultShader())
{
	meshes.push_back(std::move(mesh));
    textures.push_back(nullptr);
    materials.push_back({color});
}

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture) noexcept :
    shader(GetDefaultShader())
{
	meshes.push_back(std::move(mesh));
	textures.push_back(std::move(texture));
    materials.push_back({});
}

void MeshRenderer::AddMesh(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture)
{
	meshes.push_back(std::move(mesh));
    textures.push_back(texture);
    materials.push_back({});
}

void MeshRenderer::AddMesh(std::shared_ptr<Mesh> mesh, const glm::vec3 &color)
{
    meshes.push_back(std::move(mesh));
    textures.push_back(nullptr);
    materials.push_back({color});
}

Material& MeshRenderer::GetFirstMaterial() { return *materials.begin(); }

void MeshRenderer::Render()
{
	std::shared_ptr<Transform> transform = GetTransform();
	transform->CalculateTransformMatrix();
	const glm::mat4& transformMatrix = transform->GetTransformMatrix();

	shader->Use();
	shader->SendMatrix(UniformKey::TransformMatrix, transformMatrix);

	for(unsigned int i = 0U; i < meshes.size(); i++)
	{
        shader->SendMaterial(materials[i]);
        if (textures[i])
		{
			textures[i]->Bind();
            shader->SendBool(UniformKey::IsTextured, true);
		}
        else
        {
            shader->SendBool(UniformKey::IsTextured, false);
        }

		meshes[i]->Draw();
	}	
}

void MeshRenderer::OnGUI()
{
    
}
