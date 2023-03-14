#pragma once
#include <GLM/glm/vec3.hpp>
#include "bullet3-3.24/src/btBulletDynamicsCommon.h"
#include <ostream>
#include <format>

class Vector3 : public glm::vec3
{
protected:
	constexpr inline	   glm::vec3& GetBase()			   { return *this; }
	constexpr inline const glm::vec3& GetConstBase() const { return *this; }

public:
	static const Vector3 Up;
	static const Vector3 Right;
	static const Vector3 Forward;

	Vector3();
	Vector3(float _s);
	Vector3(float _x, float _y, float _z);
	Vector3(const btVector3& v);
	Vector3(const glm::vec3& v);

	operator btVector3() const;
	Vector3 operator*(float s);
	constexpr inline void operator+=(const Vector3& other) { (glm::vec3&)*this += (const glm::vec3&)other; }
	constexpr inline void operator-=(const Vector3& other) { (glm::vec3&)*this -= (const glm::vec3&)other; }

	friend std::ostream& operator<<(std::ostream& left, const Vector3& right);
};