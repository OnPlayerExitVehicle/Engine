#include "Vehicle.h"
#include "Scene.h"
#include "Exceptions.h"
#include "Rigidbody.h"

void Vehicle::Awake()
{
	btVehicleRaycaster* raycaster = new btDefaultVehicleRaycaster(Scene::Instance->GetDynamicsWorld());
	btRaycastVehicle::btVehicleTuning tuning;

	std::shared_ptr<Rigidbody> rigidbody;
	if(!GetGameObject()->TryGetComponent(rigidbody))
		throw new RigidbodyNotFoundException("Rigidbody not found!");

	vehicle = new btRaycastVehicle(tuning, rigidbody->GetRigidbody(), raycaster);
	vehicle->setCoordinateSystem(0, 1, 2);

	const auto& childList = GetTransform()->childList;
	for(unsigned int i = 0U; i < childList.size(); i++)
	{
		const std::string& name = childList[i]->gameObject->name;
		//std::cout << name << std::endl;
		if(name == "FL")
		{
			vehicle->addWheel(childList[i]->position, {0, 1, 0}, {-1, 0, 0}, 0.6f, 0.1f, tuning, true);
		}
		else if(name == "FR")
		{
			vehicle->addWheel(childList[i]->position, {0, 1, 0}, {-1, 0, 0}, 0.6f, 0.1f, tuning, true);
		}
		else if(name == "RL")
		{
			vehicle->addWheel(childList[i]->position, {0, -1, 0}, {1, 0, 0}, 0.6f, 0.1f, tuning, false);
		}
		else if(name == "RR")
		{
			vehicle->addWheel(childList[i]->position, {0, -1, 0}, {1, 0, 0}, 0.6f, 0.1f, tuning, false);
		}
	}

	//assert(vehicle->getNumWheels() == 4);

	//btVector3 wheelDirection(0, -1, 0);
	//btVector3 wheelAxle(-1, 0, 0);
	/*vehicle->addWheel(btVector3(-1, 1, 1.5f), {0, 1, 0}, {-1, 0, 0}, 0.6f, 0.1f, tuning, true);
	vehicle->addWheel(btVector3(1, 0, 1.5f), {0, 1, 0}, {-1, 0, 0}, 0.6f, 0.1f, tuning, true);

	vehicle->addWheel(btVector3(-1, 0, -1.5f), {0, -1, 0}, {1, 0, 0}, 0.6f, 0.1f, tuning, false);
	vehicle->addWheel(btVector3(1, 0, -1.5f), {0, -1, 0}, {1, 0, 0}, 0.6f, 0.1f, tuning, false);*/
	vehicle->resetSuspension();
}

void Vehicle::BeforeFixedUpdate()
{
	
}

void Vehicle::FixedUpdate(float fixedDeltaTime)
{
	//vehicle->updateVehicle(fixedDeltaTime);
}

void Vehicle::OnGUI()
{
}

const btRaycastVehicle* Vehicle::GetNativeVehiclePtr() const noexcept
{
	return vehicle;
}
