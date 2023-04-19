#include "HTime.h"
#include <iostream>
#include "Scene.h"

std::chrono::system_clock::time_point Time::frameStart;

float Time::fixedDtCounter;
int Time::fixedFrameCount;

float Time::networkDtCounter;
int Time::networkFrameCount;

int Time::frameCount;
float Time::secondCounter;

float Time::Dt;
const float Time::FixedDt = .02f;
const float Time::NetworkDt = .005f;

void Time::FrameStart()
{
	std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
	float difference = std::chrono::duration<float, std::milli>(currentTime - frameStart).count();
	Dt = difference / 1000.0f;
	fixedDtCounter += Dt;
	secondCounter += Dt;
	networkDtCounter += Dt;

	if (fixedDtCounter >= FixedDt)
	{
		fixedDtCounter = std::fmod(fixedDtCounter, FixedDt);
		
		fixedFrameCount++;
		// Call fixed updates
		Scene::Instance->ProcessFixedUpdate();
	}

	if(networkDtCounter >= NetworkDt)
	{
		networkDtCounter = std::fmod(networkDtCounter, NetworkDt);

		networkFrameCount++;
		Scene::Instance->ProcessNetworkUpdate();
	}

	frameCount++;

	if (secondCounter >= 1.0f)
	{
		secondCounter = std::fmod(secondCounter, 1.0f);
		std::cout << frameCount << " Frames Per Second, " << fixedFrameCount << " Fixed Frames Per Second" << std::endl;
		frameCount = 0;
		fixedFrameCount = 0;
	}

	frameStart = currentTime;
}