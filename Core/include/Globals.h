#pragma once

constexpr inline int DEFAULT_WINDOW_WIDTH = 960;
constexpr inline int DEFAULT_WINDOW_HEIGHT = 540;

inline int WINDOW_WIDTH  = DEFAULT_WINDOW_WIDTH;
inline int WINDOW_HEIGHT = DEFAULT_WINDOW_HEIGHT;

#define _STD_ std::
#define _STRING_R_ _STD_ string
#define _STRING_CR_ const _STD_ string&
#define DEBUG_LOG(str) _STD_ cout << str << _STD_ endl
#define DEBUG_FORMAT(str, ...) _STD_ cout << _STD_ format(str, __VA_ARGS__) << _STD_ endl

#if WIN32
	#define CORE_DIRECTORY "../Core"
#else
	#define CORE_DIRECTORY "../Core"
#endif

///
#define TEXTURES_DIRECTORY CORE_DIRECTORY"/textures/"
#define SHADERS_DIRECTORY CORE_DIRECTORY"/shaders/"
#define OBJECTS_DIRECTORY CORE_DIRECTORY"/objects/"