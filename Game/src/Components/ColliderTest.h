#pragma once
#include <GRUT.h>

using namespace GRUT;
using namespace GRUT::Math;

class ColliderTest : public GRUT::Component {
  float totalDelta = 0.0f;
  Vector<3> startPos;
public:
  
  void Initialize() {
    startPos = gameObject->transform->GetPosition();
  }

  void Update(float p_deltaTime) override {
    if (Input::GetKeyDown(Keys::KEY_M)) {
      totalDelta += p_deltaTime;
      gameObject->transform->SetPosition(startPos + Vector<3>(sin(totalDelta) * 5.0f, 0.0f, 0.0f));
    }
  }
};