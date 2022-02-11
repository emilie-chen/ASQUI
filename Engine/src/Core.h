#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <type_traits>
#include <typeindex>
#include <spdlog/spdlog.h>
#include <fmt/core.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include "glm/ext.hpp"

using namespace glm;

namespace AsquiEngine
{

template <typename T>
using List = std::vector<T>;

using String = std::string;

template <typename T, typename U>
using Map = std::unordered_map<T, U>;

template <typename T>
using Set = std::unordered_set<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using UniqueRef = std::unique_ptr<T>;

template <typename T>
using WeakRef = std::weak_ptr<T>;

template <typename T>
using Queue = std::queue<T>;

#define TYPEDEF_FLOAT(count) using float##count = vec##count;

TYPEDEF_FLOAT(2)
TYPEDEF_FLOAT(3)
TYPEDEF_FLOAT(4)

using float4x4 = mat4;
using float4x3 = mat4x3;
using float3x3 = mat3;

using Quaternion = fquat;

using EntityId = uint64_t;

class Id final
{
public:
    Id() = delete;
    
    static const EntityId NIL = 0;
    
    static EntityId New()
    {
        static std::atomic<EntityId> counter { 0 };
        return ++counter;
    }
    
};

template <typename T>
class RuntimeError : public std::runtime_error
{
public:
    RuntimeError(const String& msg = "") :
        std::runtime_error(fmt::format("Message: {}", msg))
    {}
};

class NullPointerError : public RuntimeError<NullPointerError>
{
public:
    NullPointerError(const String& pointer, const String& file, int lineNum)
        : RuntimeError(fmt::format("{} is null in file {} on line {}", pointer, file, lineNum))
    {}
};

class PanicError : public RuntimeError<PanicError>
{
public:
    PanicError(const String& msg = "") : RuntimeError(msg) {}
};

#define nonnull(ptr) if (!ptr) { throw AsquiEngine::NullPointerError(#ptr, __FILE__, __LINE__); }
#define panic_with(msg) throw AsquiEngine::PanicError(msg)
#define panic() panic_with("")

template <typename ... T>
void info(T&& ... args)
{
    spdlog::info(args...);
}

template <typename ... T>
void print(T&& ... args)
{
    info(args...);
}

template <typename ... T>
void warn(T&& ... args)
{
    spdlog::warn(args...);
}

template <typename ... T>
void error(T&& ... args)
{
    spdlog::error(args...);
}

template <typename ... T>
void fatal(T&& ... args)
{
    spdlog::critical(args...);
    panic();
}

template <typename T>
String GetString(const T& t)
{
    return t->ToString();
}

template <>
String GetString<float2>(const float2& vec);
template <>
String GetString<float3>(const float3& vec);
template <>
String GetString<float4>(const float4& vec);
template <>
String GetString<Quaternion>(const Quaternion& quat);

}

#define using_weak_ref(weak_ref) if (auto _##weak_ref = weak_ref.lock())
