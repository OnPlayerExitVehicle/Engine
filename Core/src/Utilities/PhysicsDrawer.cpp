#include "PhysicsDrawer.h"
#include "Globals.h"
#include <iostream>
#include <glad/glad.h>

PhysicsDrawer::PhysicsDrawer() noexcept : debugMode(0), shader()
{
	shader.AttachShader(SHADERS_DIRECTORY"physdbgvertex.glsl", GL_VERTEX_SHADER);
	shader.AttachShader(SHADERS_DIRECTORY"physdbgfragment.glsl", GL_FRAGMENT_SHADER);
	shader.Link();
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexBuffer);
}

void PhysicsDrawer::Render() noexcept
{
	if(debugMode && !debugDrawDatas.empty())
	{
		glDisable(GL_DEPTH_TEST);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, debugDrawDatas.size() * sizeof(DebugVertexData), debugDrawDatas.data(), GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(DebugVertexData), nullptr);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(DebugVertexData), reinterpret_cast<const void*>(sizeof(float) * 3));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		shader.Use();
		glDrawArrays(GL_LINES, 0, debugDrawDatas.size());

		glBindVertexArray(0);
		sealed = true;

		glEnable(GL_DEPTH_TEST);
	}
	
}

void PhysicsDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) noexcept
{
	if(sealed)
	{
		debugDrawDatas.clear();
		sealed = false;
	}
	debugDrawDatas.push_back({from, color});
	debugDrawDatas.push_back({to, color});
}

void PhysicsDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) noexcept
{
	if(sealed)
	{
		debugDrawDatas.clear();
		sealed = false;
	}

	const Vector3 startPoint = PointOnB;
	const Vector3 endPoint = startPoint - (normalOnB);
	debugDrawDatas.push_back({startPoint, color});
	debugDrawDatas.push_back({endPoint, color});
}

void PhysicsDrawer::reportErrorWarning(const char* warningString) noexcept
{
	DEBUG_LOG(warningString);
}

void PhysicsDrawer::draw3dText(const btVector3& location, const char* textString) noexcept
{

}

void PhysicsDrawer::setDebugMode(int debugMode) noexcept
{
	this->debugMode = debugMode;
}

int PhysicsDrawer::getDebugMode() const noexcept
{
	return debugMode;
}
