#include "grutpch.h"
#include "CVarRegistry.h"

namespace GRUT {
  GRUT_API std::unordered_map<StringId, ICVar*> CVarRegistry::s_registry;
  GRUT_API std::vector<std::string_view> CVarRegistry::s_keys;
}