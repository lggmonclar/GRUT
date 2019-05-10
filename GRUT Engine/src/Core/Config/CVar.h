#pragma once

#include <sstream>
#include <string>
#include <GRUTMath.h>
#include "ICVar.h"

namespace GRUT {
  class CVarInt : public ICVar {
  private:
    int m_value;
  public:
    GRUT_API CVarInt(const std::string& p_name, const int& p_defaultValue) : ICVar(p_name), m_value(p_defaultValue) {}
    GRUT_API explicit CVarInt(const std::string_view p_name) : ICVar(p_name), m_value(0) {}
    GRUT_API inline void SetVal(const std::string_view p_strVal) override {
      std::istringstream iss(p_strVal.data());
      iss >> m_value;
    }
    GRUT_API inline int GetVal() const {
      return m_value; 
    }
  };

  class CVarFloat : public ICVar {
  private:
    float m_value;
  public:
    GRUT_API CVarFloat(const std::string& p_name, const float& p_defaultValue) : ICVar(p_name), m_value(p_defaultValue) {}
    GRUT_API explicit CVarFloat(const std::string_view p_name) : ICVar(p_name), m_value(0.0f) {}
    GRUT_API inline void SetVal(const std::string_view p_strVal) override {
      std::istringstream iss(p_strVal.data());
      iss >> m_value;
    }
    GRUT_API inline float GetVal() const {
      return m_value; 
    }
  };

  class CVarString : public ICVar {
    friend class CVarRegistry;
  private:
    std::string m_value;
  public:
    GRUT_API CVarString(const std::string& p_name, const std::string_view p_defaultValue) : ICVar(p_name), m_value(p_defaultValue) {}
    GRUT_API explicit CVarString(const std::string_view p_name) : ICVar(p_name) {}
    GRUT_API inline void SetVal(const std::string_view p_strVal) override { 
      m_value = p_strVal; 
    }
    GRUT_API inline std::string GetVal() const {
      return m_value;
    }
  };
}
