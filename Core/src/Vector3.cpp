#include "Vector3.h"

const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);

Vector3::Vector3() : glm::vec3(0.0f, 0.0f, 0.0f) { }

Vector3::Vector3(float _s) : glm::vec3(_s) { }

Vector3::Vector3(float _x, float _y, float _z) : glm::vec3(_x, _y, _z) { }

Vector3::Vector3(const btVector3& v) : glm::vec3(v.x(), v.y(), v.z()) { }

Vector3::Vector3(const glm::vec3& v) : glm::vec3(v) { }

Vector3::operator btVector3() const { return btVector3(x, y, z); }

Vector3 Vector3::operator*(float s)
{
	glm::vec3& base = *this;
	return base * s;
}

std::ostream& operator<<(std::ostream& left, const Vector3& right)
{
	left << std::format("{}, {}, {}", right.x, right.y, right.z);
	return left;
}