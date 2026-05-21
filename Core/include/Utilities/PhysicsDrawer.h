#pragma once
#include "Bullet/src/LinearMath/btIDebugDraw.h"
#include <vector>
#include "Vector3.h"
#include "Shader.h"

class PhysicsDrawer : public btIDebugDraw
{
public:
    PhysicsDrawer() noexcept;
    void Render() noexcept;
    Shader* GetPhysicsDrawShader() noexcept;

	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) noexcept override;
    virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) noexcept override;
    virtual void reportErrorWarning(const char* warningString) noexcept override;
    virtual void draw3dText(const btVector3& location, const char* textString) noexcept override;

    virtual void setDebugMode(int debugMode) noexcept override;
    virtual int getDebugMode() const noexcept override;

private:
    struct DebugVertexData
    {
        Vector3 point;
        Vector3 color;
    };

    int debugMode = 0;
    std::vector<DebugVertexData> debugDrawDatas;
    Shader shader;
    unsigned int vao, vertexBuffer;
    bool sealed = false;
};