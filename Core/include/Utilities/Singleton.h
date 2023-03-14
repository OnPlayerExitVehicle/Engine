#pragma once
#include <memory>

template <class T>
class Singleton
{
protected:
	static std::unique_ptr<T> instance;
public:
	static std::shared_ptr<T> QuerryInstance()
	{
		if (!instance)
		{
			instance = std::make_unique<T>();
		}

		return std::move(instance);
	}
};