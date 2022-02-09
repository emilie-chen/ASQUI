#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>

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
using Unique = std::unique_ptr<T>;

template <typename T>
using Weak = std::weak_ptr<T>;

}
