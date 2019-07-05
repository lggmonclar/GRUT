#pragma once
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <sid/sid.h>
#include "CVar.h"

namespace GRUT {
  class CVarRegistry {
  private:
    GRUT_API static std::unordered_map<StringId, ICVar*> s_registry;
    GRUT_API static std::vector<std::string_view> s_keys;
  public:
    GRUT_API static inline void RegisterVariable(ICVar* cvar) {
      s_registry.erase(cvar->nameID);
      s_registry.emplace(cvar->nameID, cvar);
      s_keys.push_back(cvar->name);
    }
    GRUT_API static inline bool UnregisterVariable(const std::string p_name) {
      s_keys.erase(std::remove(s_keys.begin(), s_keys.end(), p_name), s_keys.end());
      return s_registry.erase(SID(p_name.c_str()));
    }
    GRUT_API static inline ICVar* Find(const StringId sid) {
      auto it = s_registry.find(sid);
      if (it == s_registry.end()) {
        return nullptr;
      }
      return it->second;
    }

    GRUT_API static inline void Destroy() {
      for (auto &i : s_registry) {
        delete i.second;
      }
      s_registry.clear();
      s_keys.clear();
    }

    GRUT_API static inline std::vector<std::string_view> GetKeys() { return s_keys; }

    template<class T>
    static inline T* GetCVar(StringId sid) {
      auto cvar = GRUT::Config::Instance().registry.Find(sid);
      T* t_cvar = dynamic_cast<T*>(cvar);
      if (t_cvar == nullptr) {
        CVarString* s_cvar = dynamic_cast<CVarString*>(cvar);
        t_cvar = dynamic_cast<T*>(ConvertCVar<T*>(s_cvar));
        delete s_cvar;
      }
      return t_cvar;
    }

    template <class T> static inline ICVar* ConvertCVar(CVarString* p_cvar) {
      LOG_ERROR("Attempted to convert CVar to an unsupported type");
      return p_cvar;
    }
    template <> static inline ICVar* ConvertCVar<CVarString*>(CVarString* p_cvar) {
      return p_cvar;
    }
    template <> static inline ICVar* ConvertCVar<CVarInt*>(CVarString* p_cvar) {
      CVarInt* cvar = new CVarInt(p_cvar->name, atoi(p_cvar->m_value.c_str()));
      return cvar;
    }
    template <> static inline ICVar* ConvertCVar<CVarFloat*>(CVarString* p_cvar) {
      CVarFloat* cvar = new CVarFloat(p_cvar->name, strtof(p_cvar->m_value.c_str(), nullptr));
      return cvar;
    }
  };
}
