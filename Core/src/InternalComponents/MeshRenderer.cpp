#include "MeshRenderer.h"
#include "MeshFactory.h"
#include <GLAD/glad.h>
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

MeshRenderer::MeshRenderer() : 
	mesh(MeshFactory::GetMesh(MeshType::Cube)), 
	shader(GetDefaultShader()), 
	textured(false)
{ }

MeshRenderer::MeshRenderer(const glm::vec3& color, bool isLight) :
	mesh(MeshFactory::GetMesh(MeshType::Cube)),
	textured(false),
	isLight(isLight),
	material{ color }
{ 
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
	mesh(MeshFactory::GetMesh(MeshType::Cube)),
	texture(std::move(texture)),
	shader(GetDefaultShader()),
	textured(true)
{ }

MeshRenderer::MeshRenderer(const glm::vec3& color, std::shared_ptr<Shader> shader) :
	mesh(MeshFactory::GetMesh(MeshType::Cube)),
	shader(std::move(shader)),
	textured(false),
	material{ color }
{ }

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, const glm::vec3& color) :
	mesh(std::move(mesh)),
	shader(GetDefaultShader()),
	textured(false),
	material{ color }
{ }

void MeshRenderer::SetColor(const Vector3& color)
{
	this->material.color = color;
}

Material& MeshRenderer::GetMaterial() { return material; }

void MeshRenderer::Render()
{
	std::shared_ptr<Transform> transform = GetTransform();
	transform->CalculateTransformMatrix();
	const glm::mat4& transformMatrix = transform->GetTransformMatrix();

	shader->Use();

	if (textured)
	{
		texture->Bind();
	}

	shader->SendBool(UniformKey::IsTextured, textured);
	shader->SendMatrix(UniformKey::TransformMatrix, transformMatrix);
	shader->SendMaterial(material);

	mesh->Draw();
}

void MeshRenderer::OnGUI()
{
	if(ImGui::Checkbox("Textured", &textured) && textured && texture == nullptr)
	{
		switch (rand() % 2)
		{
		case 0:
			texture = TextureLoader::LoadTexture(TEXTURES_DIRECTORY"brick.jpg");
			break;
		case 1:
			texture = TextureLoader::LoadTexture(TEXTURES_DIRECTORY"container.jpg");
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