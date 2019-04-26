#pragma once
#include <sid/sid.h>

namespace GRUT {
  class ICVar {
  protected:
    explicit ICVar(std::string_view name);
    virtual ~ICVar() {}
  public:
    const std::string name;
    const StringId nameID;
    virtual void SetVal(const std::string_view strVal) = 0;
  };
}