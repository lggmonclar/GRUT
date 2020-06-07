#pragma once
#include <GRUT.h>

using namespace GRUT;
using namespace GRUT::Math;

class ColliderTest : public GRUT::Component {
    float totalDelta = 0.0f;
    Vector3 startPos;

    public:

        void Initialize() {
            startPos = gameObject->transform->GetPosition();
        }

        void Update(float p_deltaTime) override {
            if (Input::GetKeyDown(Keys::KEY_M)) {
                totalDelta += p_deltaTime;
                gameObject->transform->SetPosition(startPos + Vector3(sin(totalDelta) * 5.0f, 0.0f, 0.0f));
            }
            if (Input::GetKeyDown(Keys::KEY_P)) {
                gameObject->ScheduleDestruction();
            }
        }
};