#pragma once

constexpr int WINDOW_WIDTH  = 1920;
constexpr int WINDOW_HEIGHT = 1080;

#define _STD_ std::
#define _STRING_R_ _STD_ string
#define _STRING_CR_ const _STD_ string&
#define DEBUG_LOG(str) _STD_ cout << str << _STD_ endl