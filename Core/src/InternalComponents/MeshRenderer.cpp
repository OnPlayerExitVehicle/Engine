#include "MeshRenderer.h"
#include "MeshFactory.h"
#include <glad/glad.h>
#include "Transform.h"
#include "GUI.h"
#include "TextureLoader.h"
#include "Material.h"

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

MeshRenderer::MeshRenderer(const bool defaultMesh, const bool unTextured) : 
	shader(GetDefaultShader()), 
	textured(!unTextured)
{
	if(defaultMesh)
	{
		meshes.push_back(MeshFactory::GetMesh(MeshType::Cube));
	}
}

MeshRenderer::MeshRenderer(const glm::vec3& color, bool isLight) :
	textured(false),
	isLight(isLight),
	material{ color }
{ 
	meshes.push_back(MeshFactory::GetMesh(MeshType::Cube));

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
	shader(GetDefaultShader()),
	textured(true)
{
	meshes.push_back(MeshFactory::GetMesh(MeshType::Cube));
	textures.push_back(std::move(texture));
}

MeshRenderer::MeshRenderer(const glm::vec3& color, std::shared_ptr<Shader> shader) :
	shader(std::move(shader)),
	textured(false),
	material{ color }
{
	meshes.push_back(MeshFactory::GetMesh(MeshType::Cube));
}

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, const glm::vec3& color) :
	shader(GetDefaultShader()),
	textured(false),
	material{ color }
{
	meshes.push_back(std::move(mesh));
}

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture) noexcept :
	shader(GetDefaultShader()),
	textured(true)
{
	meshes.push_back(std::move(mesh));
	textures.push_back(std::move(texture));
}

void MeshRenderer::SetColor(const Vector3& color)
{
	this->material.color = color;
}

void MeshRenderer::AddMesh(std::shared_ptr<Mesh> mesh, std::shared_ptr<Texture> texture)
{
	meshes.push_back(std::move(mesh));
	textures.push_back(std::move(texture));
}

Material& MeshRenderer::GetMaterial() { return material; }

void MeshRenderer::Render()
{
	std::shared_ptr<Transform> transform = GetTransform();
	transform->CalculateTransformMatrix();
	const glm::mat4& transformMatrix = transform->GetTransformMatrix();

	shader->Use();
	shader->SendBool(UniformKey::IsTextured, textured);
	shader->SendMatrix(UniformKey::TransformMatrix, transformMatrix);
	shader->SendMaterial(material);

	for(unsigned int i = 0U; i < meshes.size(); i++)
	{
		if (textured && i < textures.size())
		{
			textures[i]->Bind();
		}

		meshes[i]->Draw();
	}
	

	
}

void MeshRenderer::OnGUI()
{
	if(ImGui::Checkbox("Textured", &textured) && textured && textures.size() == 0U)
	{
		switch (rand() % 2)
		{
		case 0:
			textures.push_back(TextureLoader::LoadTexture(TEXTURES_DIRECTORY"brick.jpg"));
			break;
		case 1:
			textextures.push_back(TextureLoader::LoadTexture(TEXTURES_DIRECTORY"container.jpg"));
			break;
		default:
			textured = false;
			break;
		}
	}

	if (!textured)
	{
		ImGui::ColorEdit3("Color", (float*) & material.color);
	}

	if(!isLight)
	{
		ImGui::Text("Material Properties");

		ImGui::SliderFloat("Ambient", &material.ambient, .0f, 1.0f);
		ImGui::SliderFloat("Diffuse", &material.diffuse, .0f, 1.0f);
		ImGui::SliderFloat("Specular", &material.specular, .0f, 1.0f);
		ImGui::SliderInt("Shininess", &material.shininess, 2, 50);
	}
}