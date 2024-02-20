#pragma once
#include <exception>
#include <string>

class ColliderNotFoundException : std::exception
{
public:
	ColliderNotFoundException() { }
	ColliderNotFoundException(const std::string& message) : std::exception() { } // FIXED FOR NATIVE GCC (LINUX)
};