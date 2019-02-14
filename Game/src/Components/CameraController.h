#pragma once
#include <GRUT.h>

using namespace GRUT;
using namespace GRUT::Math;

class CameraController : public GRUT::Component {
private:
  float movementSpeed = 5.0f;
  float mouseSensitivity = 0.2f;
  float lastMouseX = 0.0f;
  float lastMouseY = 0.0f;
  float currPitch = 0.0f;
  float currYaw = 0.0f;
public:
  void Update(float p_deltaTime) override {
    auto camera = gameObject->GetComponent<Camera>();
    float velocity = movementSpeed * p_deltaTime;
    if (Input::GetKeyDown(Keys::KEY_W)) {
      gameObject->transform->Translate(camera->front * velocity);
    }
    if (Input::GetKeyDown(Keys::KEY_A)) {
      gameObject->transform->Translate(-camera->right * velocity);
    }
    if (Input::GetKeyDown(Keys::KEY_S)) {
      gameObject->transform->Translate(-camera->front * velocity);
    }
    if (Input::GetKeyDown(Keys::KEY_D)) {
      gameObject->transform->Translate(camera->right * velocity);
    }

    currYaw += (Input::mouseX - lastMouseX) * mouseSensitivity;
    currPitch += (lastMouseY - Input::mouseY) * mouseSensitivity;

    if (currPitch > 89.0f)
      currPitch = 89.0f;
    if (currPitch < -89.0f)
      currPitch = -89.0f;

    lastMouseX = Input::mouseX;
    lastMouseY = Input::mouseY;

    camera->SetPitch(currPitch);
    camera->SetYaw(currYaw);
  }
};