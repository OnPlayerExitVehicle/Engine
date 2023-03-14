#pragma once
#include <memory>

template <class T>
class Singleton
{
protected:
	static std::unique_ptr<T> _instance;

public:
	static std::shared_ptr<T> QuerryInstance()
	{
		if (!_instance)
		{
			_instance = std::make_unique<T>();
		}

		return std::move(_instance);
	}
};