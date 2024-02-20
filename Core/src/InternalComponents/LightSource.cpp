#include "LightSource.h"
#include "MeshRenderer.h"
#include "GameObject.h"
#include "GUI.h"

void LightSource::Awake()
{
	auto gameObject = GetGameObject();
	if (!gameObject->TryGetComponent<MeshRenderer>(meshRenderer))
	{
		meshRenderer = gameObject->AddComponent<MeshRenderer>();
	}
}

void LightSource::BeforeRender()
{
	auto transform = GetTransform();

	if (!defaultShader)
	{
		defaultShader = MeshRenderer::GetDefaultShader();
	}

	defaultShader->Use();
	defaultShader->SendVector(UniformKey::LightMaterial_Color, meshRenderer->material.color);
	defaultShader->SendVector(UniformKey::LightMaterial_Position, transform->position);
	defaultShader->SendLightMaterial(lightMaterial);
}

void LightSource::OnGUI()
{
	ImGui::Text("Light Properties");

	ImGui::SliderFloat("Ambient", &lightMaterial.ambient, 0.0f, 1.0f);
	ImGui::SliderFloat("Diffuse", &lightMaterial.diffuse, 0.0f, 1.0f);
	ImGui::SliderFloat("Specular", &lightMaterial.specular, 0.0f, 1.0f);
}
