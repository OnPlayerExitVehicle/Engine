#include "Vehicle.h"
#include "Scene.h"
#include "Exceptions.h"
#include "Rigidbody.h"
#include <GLM/glm/gtc/type_ptr.hpp>
#include <GLM/glm/gtx/matrix_decompose.hpp>

void Vehicle::Awake()
{
    btDynamicsWorld* dynamicsWorld = Scene::Instance->GetDynamicsWorld();
    btVehicleRaycaster* raycaster = new btDefaultVehicleRaycaster(dynamicsWorld);
	btRaycastVehicle::btVehicleTuning tuning;

	std::shared_ptr<Rigidbody> rigidbody;
	if(!GetGameObject()->TryGetComponent(rigidbody))
		throw new RigidbodyNotFoundException("Rigidbody not found!");

	vehicle = new btRaycastVehicle(tuning, rigidbody->GetRigidbody(), raycaster);
	vehicle->setCoordinateSystem(0, 1, 2);
    dynamicsWorld->addAction(vehicle);

    assert(GetTransform()->childList.size() > 0);
    auto& childList = GetTransform()->childList[0]->childList;
	for(unsigned int i = 0U; i < childList.size(); i++)
	{
		const std::string& name = childList[i]->gameObject->name;
        // std::cout << name << std::endl;
        childList[i]->CalculateTransformMatrix();
		if(name == "FL")
		{
            wheelInfos[static_cast<int>(VehicleWheel::FrontLeft)] = {&vehicle->addWheel(childList[i]->GetWorldPosition(), {0, 1, 0}, {-1, 0, 0}, 0.6f, 0.1f, tuning, true), childList[i]};
		}
		else if(name == "FR")
		{
            wheelInfos[static_cast<int>(VehicleWheel::FrontRight)] = {&vehicle->addWheel(childList[i]->GetWorldPosition(), {0, 1, 0}, {-1, 0, 0}, 0.6f, 0.1f, tuning, true), childList[i]};
		}
		else if(name == "RL")
		{
            wheelInfos[static_cast<int>(VehicleWheel::RearLeft)] = {&vehicle->addWheel(childList[i]->GetWorldPosition(), {0, -1, 0}, {1, 0, 0}, 0.6f, 0.1f, tuning, false), childList[i]};
		}
		else if(name == "RR")
		{
            wheelInfos[static_cast<int>(VehicleWheel::RearRight)] = {&vehicle->addWheel(childList[i]->GetWorldPosition(), {0, -1, 0}, {1, 0, 0}, 0.6f, 0.1f, tuning, false), childList[i]};
		}
	}

    assert(vehicle->getNumWheels() == 4);

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
    GetTransform()->parent->CalculateTransformMatrix();
    for(unsigned int i = 0U; i < static_cast<int>(VehicleWheel::SIZE); i++)
    {
        glm::mat4 parentInverse = glm::inverse(GetTransform()->parent->transformMatrix);
        float mtx[16];
        wheelInfos[i].wheelInfo->m_worldTransform.getOpenGLMatrix(mtx);
        glm::mat4 newMatrix = glm::make_mat4(mtx);
        newMatrix = newMatrix * parentInverse;

        glm::vec3 pos;
        glm::quat rot;
        glm::vec3 scale;
        glm::vec3 skew;
        glm::vec4 perspective;
        if(glm::decompose(newMatrix, scale, rot, pos, skew, perspective))
        {
            wheelInfos[i].transform->position = pos;
            wheelInfos[i].transform->rotation = rot;
            wheelInfos[i].transform->scale = scale;
        }
        else
        {
            assert(false);
        }
    }
}

void Vehicle::OnGUI()
{
    for(unsigned int i = 0U; i < static_cast<int>(VehicleWheel::SIZE); i++)
    {
        ImGui::SeparatorText(std::to_string(i).c_str());
        ImGui::PushID(i);
        ImGui::InputFloat("Radius", &wheelInfos[i].wheelInfo->m_wheelsRadius);
        ImGui::PopID();
    }
}

const btRaycastVehicle* Vehicle::GetNativeVehiclePtr() const noexcept
{
	return vehicle;
}
