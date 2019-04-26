#include "grutpch.h"
#include "CVar.h"

namespace GRUT {
  std::unordered_map<StringId, ICVar*> CVarRegistry::m_registry;
  std::vector<std::string_view> CVarRegistry::m_keys;
}