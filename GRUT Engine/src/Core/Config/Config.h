#pragma once
#include <sstream>
#include <string>
#include "Core/GRUTAlias.h"
#include "CVarRegistry.h"
#include <sid/sid.h>

namespace GRUT {
  #define GET_CONFIG_VAL(expr) GRUT::Config::Instance().expr.GetVal()
  #define GET_CONFIG_M_VAL(mod, expr) GRUT::Config::Instance().mod.expr.GetVal()

  class Config {
  private:
    class CVarRegistry m_registry;

    Config() = default;

    bool IsOnlyWhitespace(const std::string_view& p_line) const;
    bool IsValidLine(const std::string_view& p_line) const;
    void ProcessContents(const std::string& p_contentBuffer);
    void RemoveComments(std::string* p_line) const;
    void ExtractKey(std::string* p_key, const Size& p_sepPos, const std::string_view p_line);
    void ExtractValue(std::string* p_value, const Size& p_sepPos, const std::string_view p_line);
  public:
    static Config& Instance() {
      static Config instance;
      return instance;
    }

    void Read(const char* p_filePath);
    void SetVal(const std::string& p_key, const std::string_view& valuep_);
  };
}