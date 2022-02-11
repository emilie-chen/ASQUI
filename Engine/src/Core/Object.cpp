#include "Object.h"

namespace AsquiEngine
{
String Object::ToString() const
{
    return fmt::format("Object@{0:#x}", reinterpret_cast<const size_t>(this));
}
}
