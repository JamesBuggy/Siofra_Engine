#include "testSceneController.hpp"

void TestSceneController::init(siofraEngine::core::Scene * scene)
{
	SE_LOG_INFO("TestSceneController::init");
	cameraEntity = scene->getEntities<siofraEngine::core::Camera>()[0];
	camerTransform = scene->getComponent<siofraEngine::core::Transform>(cameraEntity);
	camerCamera = scene->getComponent<siofraEngine::core::Camera>(cameraEntity);
}

void TestSceneController::update(siofraEngine::core::IInputState const * inputState, siofraEngine::core::Scene * scene, float deltaTime)
{
	auto turnSpeed = 0.5f;
	auto movementSpeed = 5.0f;
	auto minPitch = -89.0f;
	auto maxPitch = 89.0f;
	auto invertY = true;

	auto xChange = inputState->getMouseXChange() * turnSpeed;
	auto yChange = inputState->getMouseYChange() * turnSpeed;
	yChange = invertY
		? yChange * -1
		: yChange;

	camerCamera->yaw += xChange;

	camerCamera->pitch += yChange;
	camerCamera->pitch = std::min(camerCamera->pitch, maxPitch);
	camerCamera->pitch = std::max(camerCamera->pitch, minPitch);

	camerCamera->front.x = cos(glm::radians(camerCamera->yaw)) * cos(glm::radians(camerCamera->pitch));
	camerCamera->front.y = sin(glm::radians(camerCamera->pitch));
	camerCamera->front.z = sin(glm::radians(camerCamera->yaw)) * cos(glm::radians(camerCamera->pitch));
	camerCamera->front = glm::normalize(camerCamera->front);

	camerCamera->right = glm::normalize(glm::cross(camerCamera->front, camerCamera->worldUp));

	camerCamera->up = glm::normalize(glm::cross(camerCamera->right, camerCamera->front));

	if (inputState->isDown(siofraEngine::core::KeyCode::KEY_W))
	{
		camerTransform->position += camerCamera->front * movementSpeed * deltaTime;
	}

	if (inputState->isDown(siofraEngine::core::KeyCode::KEY_A))
	{
		camerTransform->position -= camerCamera->right * movementSpeed * deltaTime;
	}

	if (inputState->isDown(siofraEngine::core::KeyCode::KEY_D))
	{
		camerTransform->position += camerCamera->right * movementSpeed * deltaTime;
	}

	if (inputState->isDown(siofraEngine::core::KeyCode::KEY_S))
	{
		camerTransform->position -= camerCamera->front * movementSpeed * deltaTime;
	}
}