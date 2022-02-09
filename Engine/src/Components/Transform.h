#pragma once

#include "../Core/Component.h"

namespace AsquiEngine
{

class Transform : public Component
{
public:
    Transform()
    {
        
    }
    
    float3 GetPosition() const
    {
        return m_Position;
    }
    
    float3 GetScale() const
    {
        return m_Scale;
    }
    
    Quaternion GetRotation() const
    {
        return m_Rotation;
    }
    
    void SetPosition(const float3& position)
    {
        m_Position = position;
    }
    
    void SetScale(const float3& scale)
    {
        m_Scale = scale;
    }
    
    void SetRotation(const Quaternion& rotation)
    {
        m_Rotation = rotation;
    }
    
    float4x4 GetTransformationMatrix() const;
    
private:
    float3 m_Position;
    float3 m_Scale;
    Quaternion m_Rotation;
};

}
