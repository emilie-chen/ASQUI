#include "GameObject.h"

namespace AsquiEngine
{
Ref<GameObject> GameObject::New()
{
    return Ref<GameObject>(new GameObject);
}
}
