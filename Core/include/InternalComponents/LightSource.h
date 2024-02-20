#pragma once
#include "Component.h"
#include "Shader.h"
#include "Material.h"

class MeshRenderer;

class LightSource : public Component
{
private:
	std::shared_ptr<MeshRenderer> meshRenderer;
	std::shared_ptr<Shader> defaultShader;
	LightMaterial lightMaterial;

protected:
	void Awake() override;
	void BeforeRender() override;
	void OnGUI() override;

public:
	std::string GetName() override { return typeid(*this).name(); }
};