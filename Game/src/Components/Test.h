#pragma once
#include <GRUT.h>

using namespace GRUT::Math;

class Test : public GRUT::Component {
public:
  float totalDelta = 0.0f;

  void Initialize() override {
    //DEBUG_DRAW_LINE(gameObject->transform->GetPosition(), gameObject->transform->GetPosition() + Vector<3>(2.0f, 0.0f, 0.0f), Vector<3>(0.0f, 1.0f, 0.0f));
  }

  void Update(float p_deltaTime) override {
    totalDelta += p_deltaTime;
    //DEBUG_DRAW_LINE(gameObject->transform->GetPosition(), gameObject->transform->GetPosition() + Vector<3>(1.0f, 1.0f, 0.0f), Vector<3>(1.0f, 1.0f, 0.0f));
    DEBUG_DRAW_BOX(gameObject->transform->GetPosition(), Vector<3>(1.0f, 1.0f, 1.0f), Vector<3>(0.0f, 0.0f, 0.0f), Vector<3>(0.0f, 0.95f, 0.2f));
  }
};