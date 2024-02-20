#pragma once

constexpr int WINDOW_WIDTH  = 1280;
constexpr int WINDOW_HEIGHT = 960;

#define _STD_ std::
#define _STRING_R_ _STD_ string
#define _STRING_CR_ const _STD_ string&
#define DEBUG_LOG(str) _STD_ cout << str << _STD_ endl
#if WIN32
    #define CORE_DIRECTORY "../../Core"
#else
    #define CORE_DIRECTORY "../Core"
#endif

///
#define TEXTURES_DIRECTORY CORE_DIRECTORY"/textures/"
#define SHADERS_DIRECTORY CORE_DIRECTORY"/shaders/"