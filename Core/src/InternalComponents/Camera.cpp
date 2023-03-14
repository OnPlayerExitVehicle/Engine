#include "Camera.h"
#include "GLM/glm/mat4x4.hpp"
#include "GLM/glm/gtc/matrix_transform.hpp"
#include "Globals.h"
#include "Transform.h"

void Camera::BeforeRender()
{
	if (!defaultShader)
	{
		defaultShader = MeshRenderer::GetDefaultShader();
	}

	auto transform = GetTransform();
	/*std::cout << 
		transform->position.x << ", " << 
		transform->position.y << ", " <<
		transform->position.z << std::endl;*/

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1), transform->position);
	
	/*
	glm::vec3& rotation = transform->rotation;

	glm::mat4 rotationMatrix_X = glm::rotate(glm::mat4(1), glm::radians(rotation.x), Vector3::Right);
	glm::mat4 rotationMatrix_Y = glm::rotate(glm::mat4(1), glm::radians(rotation.y), Vector3::Up);
	glm::mat4 rotationMatrix_Z = glm::rotate(glm::mat4(1), glm::radians(rotation.z), Vector3::Forward);

	glm::mat4 rotationMatrix = rotationMatrix_Z * rotationMatrix_Y * rotationMatrix_X;
	*/

	glm::mat4 rotationMatrix = glm::toMat4(transform->rotation);

	transformMatrix = translationMatrix * rotationMatrix;
	viewMatrix = glm::inverse(rotationMatrix) * translationMatrix;
	projectionMatrix = glm::perspective(glm::radians(verticalFOV), ((float)WINDOW_WIDTH / WINDOW_HEIGHT), nearClip, farClip);

	defaultShader->Use();
	defaultShader->SendMatrix(UniformKey::ViewMatrix, viewMatrix);
	defaultShader->SendMatrix(UniformKey::ProjectionMatrix, projectionMatrix);
}