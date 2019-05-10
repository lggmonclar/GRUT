#pragma once
#include <sid/sid.h>

namespace GRUT {
  class ICVar {
  protected:
    GRUT_API explicit ICVar(std::string_view name);
  public:
    const std::string name;
    const StringId nameID;
    GRUT_API virtual void SetVal(const std::string_view strVal) = 0;
    GRUT_API virtual ~ICVar() {}
  };
}