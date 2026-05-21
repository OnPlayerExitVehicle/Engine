#include "Quaternion.h"

Quaternion::Quaternion() : glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)) { }
Quaternion::Quaternion(float _x, float _y, float _z) : glm::quat(glm::vec3((_x), (_y), (_z))) { }
Quaternion::Quaternion(float _x, float _y, float _z, float _w) : glm::quat(_w, _x, _y, _z) { }
Quaternion::Quaternion(const btQuaternion& q) : glm::quat(q.w(), q.x(), q.y(), q.z()) { }
Quaternion::Quaternion(const glm::quat& q) noexcept : glm::quat(q) { }

Quaternion::operator btQuaternion() const { return btQuaternion(x, y, z, w); }

glm::vec3 Quaternion::euler() const noexcept
{
	return glm::degrees(glm::eulerAngles(*this));
}

void Quaternion::fromEuler(const glm::vec3& euler) noexcept
{
	glm::vec3 eulerRadians = glm::radians(euler);
	*this = Quaternion(eulerRadians.x, eulerRadians.y, eulerRadians.z);
}

std::ostream& operator<<(std::ostream& left, const Quaternion& right)
{
	left << std::format("{}, {}, {}, {}", right.x, right.y, right.z, right.w);
	return left;
}