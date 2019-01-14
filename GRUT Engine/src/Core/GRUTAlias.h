#pragma once
#include <cstdint>

namespace GRUT {
  using Byte = uint8_t;
  using Size = size_t;

  using U8 = uint8_t;
  using U16 = uint16_t;
  using U32 = uint32_t;
  using U64 = uint64_t;

  inline auto operator""_KB(Size const x) { return 1024 * x; }
  inline auto operator""_MB(Size const x) { return 1024 * 1024 * x; }
  inline auto operator""_GB(Size const x) { return 1024 * 1024 * 1024 * x; }
}