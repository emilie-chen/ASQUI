#include "Behavior.h"
#include "GameObject.h"
#include "Engine.h"

namespace AsquiEngine
{
WeakRef<Transform> Behavior::GetTransform()
{
    using_weak_ref(gameObject)
    {
        return engine->GetComponent<Transform>(_gameObject);
    }
}
}
