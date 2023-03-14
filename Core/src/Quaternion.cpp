#include "Quaternion.h"

Quaternion::Quaternion() : glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)) { }
Quaternion::Quaternion(float _x, float _y, float _z) : glm::quat(glm::vec3((_x), (_y), (_z))) { }
Quaternion::Quaternion(float _x, float _y, float _z, float _w) : glm::quat(_w, _x, _y, _z) { }
Quaternion::Quaternion(const btQuaternion& q) : glm::quat(q.w(), q.x(), q.y(), q.z()) { }

Quaternion::operator btQuaternion() const { return btQuaternion(x, y, z, w); }

std::ostream& operator<<(std::ostream& left, const Quaternion& right)
{
	left << std::format("{}, {}, {}, {}", right.x, right.y, right.z, right.w);
	return left;
}