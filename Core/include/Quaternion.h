#pragma once
#include "GLM/glm/gtc/quaternion.hpp"
#include "GLM/glm/gtx/quaternion.hpp"
#include "bullet3-3.24/src/btBulletDynamicsCommon.h"
#include <format>
#include <ostream>

class Quaternion : public glm::quat
{
public:
	Quaternion();
	Quaternion(float _x, float _y, float _z);
	Quaternion(float _x, float _y, float _z, float _w);
	Quaternion(const btQuaternion& q);

	operator btQuaternion() const;
	friend std::ostream& operator<<(std::ostream& left, const Quaternion& right);
};