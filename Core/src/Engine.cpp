//#include "Engine.h"
//
//std::unique_ptr<Engine> Engine::instance;
//
//Engine::Engine() : currentScene(std::make_unique<Scene>()) { }
//
//std::shared_ptr<Engine> Engine::QuerryEngine()
//{
//	if (instance == nullptr)
//	{
//		instance = std::make_unique<Engine>();
//	}
//
//	return std::move(instance);
//}