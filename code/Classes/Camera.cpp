#include "Camera.h"

Camera::Camera(const Camera& camera) :
    position(camera.position),
    scale(camera.scale),
    size(camera.size)
{
}

Camera::Camera(Vec2F position, float size, float scale) :
    position(position),
    scale(scale),
    size(size)
{
}

void Camera::Move(Vec2F move_vcetor)
{
    position += move_vcetor;
}

Camera::~Camera()
{
}
















