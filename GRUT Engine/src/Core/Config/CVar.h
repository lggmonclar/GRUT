#pragma once

#include <sstream>
#include <string>
#include "ICVar.h"

namespace GRUT {
  class CVarInt : public ICVar {
  private:
    int m_value;
  public:
    CVarInt(const std::string& p_name, const int& p_defaultValue) : ICVar(p_name), m_value(p_defaultValue) {}
    explicit CVarInt(const std::string_view p_name) : ICVar(p_name), m_value(0) {}
    inline void SetVal(const std::string_view p_strVal) override {
      std::istringstream iss(p_strVal.data());
      iss >> m_value;
    }
    inline int GetVal() const {
      return m_value; 
    }
  };

  class CVarFloat : public ICVar {
  private:
    float m_value;
  public:
    CVarFloat(const std::string& p_name, const float& p_defaultValue) : ICVar(p_name), m_value(p_defaultValue) {}
    explicit CVarFloat(const std::string_view p_name) : ICVar(p_name), m_value(0.0f) {}
    inline void SetVal(const std::string_view p_strVal) override {
      std::istringstream iss(p_strVal.data());
      iss >> m_value;
    }
    inline float GetVal() const {
      return m_value; 
    }
  };

  class CVarString : public ICVar {
    friend class CVarRegistry;
  private:
    std::string m_value;
  public:
    CVarString(const std::string& p_name, const std::string_view p_defaultValue) : ICVar(p_name), m_value(p_defaultValue) {}
    explicit CVarString(const std::string_view p_name) : ICVar(p_name) {}
    inline void SetVal(const std::string_view p_strVal) override { 
      m_value = p_strVal; 
    }
    inline std::string GetVal() const {
      return m_value;
    }
  };
}
