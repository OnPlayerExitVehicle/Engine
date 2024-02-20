#include "GUI.h"
#include "Scene.h"
#include <iostream>
#include "Rigidbody.h"
#include "MeshRenderer.h"
#include "TestComponent.h"
#include "PlaneCollider.h"
#include "Camera.h"
#include "Input.h"
#include "MyComponent.h"

std::string GUI::newObjectName;
std::string GUI::address = "127.0.0.1";
std::string GUI::port = "60000";

void GUI::Init(GLFWwindow* window)
{
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();
}

void GUI::Draw()
{
    Input::ResetInputThisFrame();
    FrameStart();

    DrawHierarchy();
    if(lastSelected)
        DrawSelectedObjectProps();

    DrawObjectCreator();
    DrawConnectDialog();

    FrameEnd();
 
}

void GUI::DrawHierarchy()
{
    Scene* scene = Scene::Instance;

    ImGui::Begin("Object Hierarchy");

    for (auto object : scene->objectList)
    {
        if (object->transform->parent == nullptr)
            DrawObject(object);
    }

    ImGui::End();
}

void GUI::DrawSelectedObjectProps()
{
    ImGui::Begin("Object Properties");
    
    const char* name = lastSelected->name.c_str();
    char buf[256];
    std::strcpy(buf, name);

    if (ImGui::InputText("Name", buf, 256))
    {
        Input::SetInputThisFrame();
        lastSelected->name = buf;
    }
    
    //ImGui::Text(std::format("Name = {}", lastSelected->name).c_str());
    if (ImGui::SliderFloat3("Position", (float*)&lastSelected->transform->position, -10.0f, 10.0f))
    {
        std::shared_ptr<Rigidbody> ptr;
        if (lastSelected->TryGetComponent<Rigidbody>(ptr))
        {
            ptr->ActivatePhysics();
        }
    }
    ImGui::SliderFloat4("Rotation", (float*)&lastSelected->transform->rotation, -1.0f, 1.0f);
    ImGui::SliderFloat3("Scale", (float*)&lastSelected->transform->scale, 0.0f, 10.0f);

    for (auto ptr : lastSelected->m_componentList)
    {
        std::string name = ptr->GetName().substr(6);
        ImGui::BeginTabBar(name.c_str());
        ImGui::BeginTabItem(name.c_str());
        ptr->OnGUI();
        ImGui::EndTabItem();
        ImGui::EndTabBar();
    }

    if(ImGui::Button("Add MyComponent"))
    {
	    lastSelected->AddComponent<MyComponent>();
    }

    if (ImGui::Button("Add MeshRenderer"))
    {
        lastSelected->AddComponent<MeshRenderer>();
    }

    if (ImGui::Button("Add BoxCollider"))
    {
        lastSelected->AddComponent<BoxCollider>();
    }

    if (ImGui::Button("Add PlaneCollider"))
    {
        lastSelected->AddComponent<PlaneCollider>();
    }

    if (ImGui::Button("Add Dynamic Rigidbody"))
    {
        if (!lastSelected->HasComponent<Collider>())
            lastSelected->AddComponent<BoxCollider>();
        lastSelected->AddComponent<Rigidbody>(10.0f);
    }

    if (ImGui::Button("Add Static Rigidbody"))
    {
        if (!lastSelected->HasComponent<Collider>())
            lastSelected->AddComponent<PlaneCollider>();
        lastSelected->AddComponent<Rigidbody>();
    }

    if (ImGui::Button("Add Camera"))
    {
        lastSelected->AddComponent<Camera>();
    }

    if (ImGui::Button("Add TestComponent"))
    {
        lastSelected->AddComponent<TestComponent>();
    }

    ImGui::End();
}
void GUI::DrawObjectCreator()
{
    ImGui::Begin("Object Creator");

    Scene* scene = Scene::Instance;

    const char* name = newObjectName.c_str();
    char buf[256];
    std::strcpy(buf, name);
    if (ImGui::InputText("Name", buf, 256))
    {
        newObjectName = buf;
    }
    if (ImGui::Button("Create New Object"))
    {
        if (!newObjectName.empty())
        {
            scene->CreateObject(newObjectName);
            newObjectName = "";
        }
        else
            scene->CreateObject("New Object");
    }

    if(ImGui::Button("Create Generic Cube"))
    {
	    if(!newObjectName.empty())
	    {
		    auto go = scene->CreateObject(newObjectName);
            go->AddComponent<MeshRenderer>(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
            go->AddComponent<BoxCollider>();
            go->AddComponent<Rigidbody>(10.0f);

            newObjectName = "";
	    }
        else
        {
	        auto go = scene->CreateObject("New Cube");
            go->AddComponent<MeshRenderer>(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
            go->AddComponent<BoxCollider>();
            go->AddComponent<Rigidbody>(10.0f);
        }
    }

    ImGui::End();
}

void GUI::DrawConnectDialog()
{
    ImGui::Begin("Network");

    Scene* scene = Scene::Instance;
	if(!scene->IsConnected())
    {
	    const char* addr = address.c_str();
        const char* prt = port.c_str();
        char buff1[32];
        char buff2[32];
        std::strcpy(buff1, addr);
        std::strcpy(buff2, prt);

		if (ImGui::InputText("Address", buff1, 32))
		{
			address = buff1;
		}

        if (ImGui::InputText("Port", buff2, 32))
		{
			port = buff2;
		}

        if(ImGui::Button("Connect"))
        {
	        if(!address.empty() && !port.empty())
	        {
		        scene->ConnectToServer(address, atoi(port.c_str()));
	        }
        }

        
    }
    else
    {
	    if(ImGui::Button("Spawn"))
	    {
	        Scene::Instance->networkClient.SpawnLocalNetworkObject();
	    }
    }

    ImGui::End();
}

void GUI::DrawObject(std::shared_ptr<GameObject> object)
{
    if (!object->transform->childList.empty())
    {
        if (ImGui::TreeNodeEx(object->name.c_str()))
        {
            if (!object->lastlySelected)
            {
                object->lastlySelected = true;
                lastSelected = object;
            }

            for (auto transform : object->transform->childList)
            {
                DrawObject(transform->gameObject);
            }
            ImGui::TreePop();
            //ImGui::TreePush();
        }
        else
        {
            object->lastlySelected = false;
        }
        
    }
    else
    {
        if (ImGui::TreeNode(object->name.c_str()))
        {
            if (!object->lastlySelected)
            {
                object->lastlySelected = true;
                lastSelected = object;
            }

            ImGui::TreePop();
        }
        else
        {
            object->lastlySelected = false;
        }
    }
}

void GUI::FrameStart()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::FrameEnd()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}