#include "MeshRenderer.h"
#include "MeshFactory.h"
#include <GLAD/glad.h>
#include "Transform.h"
#include "GUI.h"
#include "TextureLoader.h"

std::shared_ptr<Shader> MeshRenderer::defaultShader;

std::shared_ptr<Shader> MeshRenderer::GetDefaultShader()
{
	if (!defaultShader)
	{
		defaultShader = std::make_shared<Shader>();
		defaultShader->AttachShader("../../../../Core/shaders/vertex.glsl", GL_VERTEX_SHADER);
		defaultShader->AttachShader("../../../../Core/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
		defaultShader->Link();
	}

	return defaultShader;
}

MeshRenderer::MeshRenderer() : 
	shader(GetDefaultShader()), 
	mesh(MeshFactory::GetMesh(MeshType::Cube)), 
	color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
	textured(false)
{ }

MeshRenderer::MeshRenderer(const glm::vec4& color) : 
	shader(GetDefaultShader()),
	mesh(MeshFactory::GetMesh(MeshType::Cube)),
	color(color),
	textured(false)
{ }

MeshRenderer::MeshRenderer(std::shared_ptr<Texture> texture) :
	shader(GetDefaultShader()),
	mesh(MeshFactory::GetMesh(MeshType::Cube)),
	color(glm::vec4(0.0f)),
	texture(texture),
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
		int result = rand() % 2;
		switch (result)
		{
		case 0:
			texture = TextureLoader::LoadTexture("../../../../Core/textures/brick.jpg");
			break;
		case 1:
			texture = TextureLoader::LoadTexture("../../../../Core/textures/container.jpg");
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