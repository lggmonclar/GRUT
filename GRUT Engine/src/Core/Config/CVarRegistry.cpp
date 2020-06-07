#include "grutpch.h"
#include "CVarRegistry.h"

namespace GRUT {
    std::unordered_map<StringId, ICVar*> CVarRegistry::s_registry;
    std::vector<std::string_view> CVarRegistry::s_keys;
}