#pragma once
#include <sstream>
#include <string>
#include "Core/GRUTAlias.h"
#include "CVarRegistry.h"
#include <sid/sid.h>
#include "Root.h"

namespace GRUT {
  #define GET_CVAR(type, key) CVarRegistry::GetCVar<type>(SID(key))->GetVal()
  #define SET_CVAR(key, val) CVarRegistry::Find(SID(key))->SetVal(val)

  class Config {
  private:
    Config() = default;

    bool IsOnlyWhitespace(const std::string_view& p_line) const;
    bool IsValidLine(const std::string_view& p_line) const;
    void ProcessContents(const std::string& p_contentBuffer);
    void RemoveComments(std::string* p_line) const;
    void ExtractKey(std::string* p_key, const Size& p_sepPos, const std::string_view p_line);
    void ExtractValue(std::string* p_value, const Size& p_sepPos, const std::string_view p_line);
  public:
    class CVarRegistry registry;
    static Config& Instance() {
      static Config instance;
      return instance;
    }

    void Read(const char* p_filePath);
    void SetVal(const std::string& p_key, const std::string_view& valuep_);
  };
}