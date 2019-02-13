#pragma once
#include <GRUT.h>

using namespace GRUT::Math;

class Test : public GRUT::Component {
  float totalDelta = 0.0f;
  void Update(float p_deltaTime) override {
    if (GRUT::Input::GetKeyDown(GRUT::Keys::KEY_R)) {
      totalDelta += p_deltaTime;
      gameObject->transform->Translate(Vector<3>(sin(totalDelta), cos(totalDelta), 0.0f));
    }
  }
};