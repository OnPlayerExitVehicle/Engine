#include "Transform.h"
#include <GLM/glm/gtc/matrix_transform.hpp>
#include <iostream>

const glm::mat4& Transform::GetTransformMatrix() const
{
	return transformMatrix;
}

void Transform::SetParent(std::shared_ptr<Transform> parent)
{
    this->parent = parent;
    parent->childList.push_back(shared_from_this());
}

void Transform::CalculateTransformMatrix()
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1), position);
    glm::mat4 scalingMatrix = glm::scale(glm::mat4(1), scale);

    glm::mat4 rotationMatrix = glm::toMat4(rotation);

    transformMatrix = translationMatrix * rotationMatrix * scalingMatrix;

    auto parent_shared = GetParent();
    if (parent_shared != nullptr)
    {
        if (!parent_shared->calculatedThisFrame)
            parent_shared->CalculateTransformMatrix();
        transformMatrix *= parent_shared->transformMatrix;
    }
    calculatedThisFrame = true;
}

std::shared_ptr<Transform> Transform::GetParent() const
{
    return parent;
}

void Transform::ResetCalculated()
{
    calculatedThisFrame = false;
    drawByGuiThisFrame = false;
}