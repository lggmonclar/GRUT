#pragma once
#include <unordered_map>
#include <vector>
#include <sid/sid.h>
#include "ICVar.h"

namespace GRUT {
  class CVarRegistry {
  private:
    static std::unordered_map<StringId, ICVar*> m_registry;
    static std::vector<std::string_view> m_keys;
  public:
    static inline void RegisterVariable(ICVar* cvar) {
      m_registry.emplace(cvar->nameID, cvar);
      m_keys.push_back(cvar->name);
    }
    static inline bool UnregisterVariable(const StringId sid) {
      return m_registry.erase(sid);
    }
    inline ICVar* Find(const StringId sid) {
      auto it = m_registry.find(sid);
      if (it == m_registry.end()) {
        return nullptr;
      }
      return it->second;
    }

    inline std::vector<std::string_view> GetKeys() const { return m_keys; }
  };
}
