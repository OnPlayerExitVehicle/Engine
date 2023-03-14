#pragma once
#include <chrono>

class Time
{
public: // private:
	static std::chrono::system_clock::time_point frameStart;

	static float fixedDtCounter;
	static int fixedFrameCount;

	static int frameCount;

	static float secondCounter;

	static void FrameStart();

public:
	static float Dt;
	const static float FixedDt;
};