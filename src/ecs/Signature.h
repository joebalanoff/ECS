#pragma once

#include <bitset>
#include <cstddef>

const std::size_t MAX_ENTITIES = 5000;
const std::size_t MAX_COMPONENTS = 32;

using Entity = std::size_t;
using ComponentType = std::size_t;
using Signature = std::bitset<MAX_COMPONENTS>;
