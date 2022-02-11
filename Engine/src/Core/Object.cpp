#include "Object.h"
#include "GameObject.h"
#include "Engine.h"

namespace AsquiEngine
{
String Object::ToString() const
{
    return fmt::format("Object@{0:#x}", reinterpret_cast<const size_t>(this));
}

int64_t Object::GetInstanceID() const
{
    return reinterpret_cast<const int64_t>(this);
}

void Object::Destroy(Ref<GameObject> object)
{
    engine->DestroyGameObject(object);
}

}
