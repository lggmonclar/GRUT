#pragma once
#include <GRUT.h>

using namespace GRUT;
using namespace GRUT::Math;

class ColliderTest : public GRUT::Component {
  float totalDelta = 0.0f;
  void Update(float p_deltaTime) override {
    if (Input::GetKeyDown(Keys::KEY_M)) {
      totalDelta += p_deltaTime;
      gameObject->transform->Translate(Vector<3>(-cos(totalDelta) * 0.15f, 0.0f, 0.0f));
    }
  }
};