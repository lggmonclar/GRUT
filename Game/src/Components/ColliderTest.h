#pragma once
#include <GRUT.h>

using namespace GRUT::Math;

class ColliderTest : public GRUT::Component {
  float totalDelta = 0.0f;
  void Update(float p_deltaTime) override {
    totalDelta += p_deltaTime;
    gameObject->transform->Translate(Vector<3>(-cos(totalDelta) * 0.09f, 0.0f, 0.0f));
  }
};