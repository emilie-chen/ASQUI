#include "Transform.h"

namespace AsquiEngine
{

float4x4 Transform::GetTransformationMatrix() const
{
    return translate(toMat4(m_Rotation) * (float4x4(1.0f) * diagonal4x4(float4(m_Scale, 1.0f))), m_Position);
}

String Transform::ToString() const
{
    return fmt::format("{{m_Position = {}, m_Scale = {}, m_Rotation = {}}}", GetString(m_Position), GetString(m_Scale), GetString(m_Rotation));
}

}
