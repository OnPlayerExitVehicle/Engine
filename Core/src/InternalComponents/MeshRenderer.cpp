#include "MeshRenderer.h"
#include "MeshFactory.h"
#include <glad/glad.h>
#include "Transform.h"
#include "GUI.h"
#include "TextureLoader.h"

std::shared_ptr<Shader> MeshRenderer::defaultShader;

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

MeshRenderer::MeshRenderer() : 
	mesh(MeshFactory::GetMesh(MeshType::Cube)), 
	shader(GetDefaultShader()), 
	color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
	textured(false)
{ }

MeshRenderer::MeshRenderer(const glm::vec4& color) : 
	mesh(MeshFactory::GetMesh(MeshType::Cube)),
	shader(GetDefaultShader()),
	color(color),
	textured(false)
{ }

MeshRenderer::MeshRenderer(std::shared_ptr<Texture> texture) :
	mesh(MeshFactory::GetMesh(MeshType::Cube)),
	texture(std::move(texture)),
	shader(GetDefaultShader()),
	color(glm::vec4(0.0f)),
	textured(true)
{ }

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
	else
	{
		shader->SendVector(UniformKey::Color, color);
	}
	shader->SendBool(UniformKey::IsTextured, textured);
	shader->SendMatrix(UniformKey::TransformMatrix, transformMatrix);
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
		ImGui::ColorEdit4("Color", &color[0]);
	}
}