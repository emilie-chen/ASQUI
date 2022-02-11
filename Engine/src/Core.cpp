#include "Core.h"

namespace AsquiEngine
{
template <>
String GetString<float2>(const float2& vec)
{
    return fmt::format("{{x = {}, y = {}}}", vec.x, vec.y);
}

template <>
String GetString<float3>(const float3& vec)
{
    return fmt::format("{{x = {}, y = {}, z = {}}}", vec.x, vec.y, vec.z);
}

template <>
String GetString<float4>(const float4& vec)
{
    return fmt::format("{{x = {}, y = {}, z = {}, w = {}}}", vec.x, vec.y, vec.z, vec.w);
}

template <>
String GetString<Quaternion>(const Quaternion& quat)
{
    return fmt::format("{{x = {}, y = {}, z = {}, w = {}}}", quat.x, quat.y, quat.z, quat.w);
}

}
