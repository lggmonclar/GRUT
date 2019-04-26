#include "grutpch.h"
#include "ICVar.h"
#include "CVarRegistry.h"

namespace GRUT {
  ICVar::ICVar(std::string_view name) : name(name), nameID(SID(name.data())) {
      CVarRegistry::RegisterVariable(this);
  }
}
