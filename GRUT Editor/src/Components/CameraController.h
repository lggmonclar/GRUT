#pragma once
#include <GRUT.h>

using namespace GRUT;
using namespace GRUT::Math;

class CameraController : public GRUT::Component {
    private:
        float movementSpeed = 5.0f;
        float mouseSensitivity = 0.1f;
        float lastMouseX = 0.0f;
        float lastMouseY = 0.0f;
        float currPitch = 0.0f;
        float currYaw = 0.0f;

    public:
        void Update(float p_deltaTime) override {
            if (Input::GetKeyDown(Keys::KEY_LEFT_SHIFT)) {
                movementSpeed = 20.0f;
            }
            else {
                movementSpeed = 5.0f;
            }
            float velocity = movementSpeed * p_deltaTime;

            if (Input::GetKeyDown(Keys::KEY_W)) {
                gameObject->transform->Translate(gameObject->transform->GetFrontVector() * velocity);
            }
            if (Input::GetKeyDown(Keys::KEY_A)) {
                gameObject->transform->Translate(-gameObject->transform->GetRightVector() * velocity);
            }
            if (Input::GetKeyDown(Keys::KEY_S)) {
                gameObject->transform->Translate(-gameObject->transform->GetFrontVector() * velocity);
            }
            if (Input::GetKeyDown(Keys::KEY_D)) {
                gameObject->transform->Translate(gameObject->transform->GetRightVector() * velocity);
            }


            float deltaYaw = static_cast<float>(deg2rad((lastMouseY - Input::mouseY) * mouseSensitivity));
            float deltaPitch = static_cast<float>(deg2rad((Input::mouseX - lastMouseX) * mouseSensitivity));

            currYaw += deltaYaw;
            currPitch += deltaPitch;

            if (currPitch > 89.0f)
                currPitch = 89.0f;
            if (currPitch < -89.0f)
                currPitch = -89.0f;

            gameObject->transform->SetRotation(Vector3(currYaw, currPitch, 0.0f));

            lastMouseX = static_cast<float>(Input::mouseX);
            lastMouseY = static_cast<float>(Input::mouseY);

            auto transform = gameObject->transform;
        }
};