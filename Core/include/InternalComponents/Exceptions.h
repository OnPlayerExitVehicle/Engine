#pragma once
#include <exception>
#include <string>

class ColliderNotFoundException : std::exception
{
public:
	ColliderNotFoundException() { }
	ColliderNotFoundException(const std::string& message) : std::exception(message.c_str()) { }
};