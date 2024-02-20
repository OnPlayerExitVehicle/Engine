#pragma once
#include <vector>
#include <functional>

template <class _Fty>
class Event
{
private:
	std::vector<std::function<_Fty>> _fns;

	constexpr static inline void* getFunctionAddress(const std::function<_Fty>& f) noexcept
	{
		return static_cast<void*>(*(f.template target<_Fty*>()));
	}

public:
	template <typename... _Cty>
	constexpr inline void Invoke(_Cty... args)
	{
		for (int i = 0; i < _fns.size(); i++)
		{
			_fns[i](args...);
		}
	}

	constexpr inline void AddListener(const std::function<_Fty>& other)
	{
		_fns.push_back(std::move(other));
	}

	constexpr inline void RemoveListener(const std::function<_Fty>& other)
	{
		void* ptr = getFunctionAddress(other);
		for (auto i = _fns.begin(); i != _fns.end(); i++)
		{
			if (ptr == (getFunctionAddress(*i)))
			{
				_fns.erase(i);
				return;
			}
		}
	}

	void operator +=(const std::function<_Fty>& other)
	{
		AddListener(std::move(other));
	}

	void operator -=(const std::function<_Fty>& other)
	{
		RemoveListener(std::move(other));
	}
};