#include "pch.h"
#include "core.h"
#include "camera.h"
#include "hero.h"

CameraState Camera::getCameraState()
{
	return Core::tryReadMemory<CameraState>(0x27EBC8, true);
}

void Camera::setCameraState(CameraState state)
{
	Core::tryWriteMemory<CameraState>(0x27EBC8, true, state);
	Core::tryWriteMemory<CameraState>(0x27EBD0, true, state);
}

Vector3f Camera::getCameraPosition()
{
	return Core::tryReadMemory<Vector3f>(0x27EB78, true);

}

void Camera::setCameraPosition(Vector3f position)
{
	Core::tryWriteMemory<Vector3f>(0x27EB78, true, position);
}

Vector3f Camera::getCameraRotation()
{
	return Core::tryReadMemory<Vector3f>(0x27F2B4, true);
}

void Camera::setCameraRotation(Vector3f rotation)
{
	Core::tryWriteMemory<Vector3f>(0x27F2B4, true, rotation);
}

float Camera::getFreeCamSpeed()
{
	return Core::tryReadMemory<float>(0x254B08, true);
}

void Camera::setFreeCamSpeed(float speed = 0.6f)
{
	Core::tryWriteMemory<float>(0x254B08, true, speed);
}

float Camera::getCameraDistance()
{
	return Core::tryReadMemory<float>(0x27EC00, true);
}

void Camera::setCameraDistance(float distance)
{
	Core::tryWriteMemory<float>(0x27EC00, true, distance);
}

void Camera::setCameraDistanceValue(CameraDistanceLevel level, float distance) {
	Core::tryWriteMemory<float>(0x27E7E8 + 0x8 * (int)level, true, distance);
}

void Camera::setCameraGoof(float value = 1.0) {
	Core::tryWriteMemory<float>(0x240488, true, value);
}
