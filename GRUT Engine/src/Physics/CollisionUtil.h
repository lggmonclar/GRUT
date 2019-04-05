#pragma once
#include <unordered_set>
#include "Core/Memory/ObjectHandle.h"

namespace GRUT {
  class Collider;

  using CollisionPair = std::pair<ObjectHandle<Collider>, ObjectHandle<Collider>>;
  struct UnorderedPairHash {
    std::size_t operator()(const CollisionPair& p) const {
      auto a = std::hash<Collider*>()(&p.first);
      auto b = std::hash<Collider*>()(&p.second);
      return a ^ b;
    }
    bool operator()(const CollisionPair& a, const CollisionPair& b) const {
      if (a.first == b.first && a.second == b.second) return true;
      if (a.first == b.second && a.second == b.first) return true;
      return false;
    }
  };

  using ColliderPairSet = std::unordered_set<CollisionPair, UnorderedPairHash, UnorderedPairHash>;
}