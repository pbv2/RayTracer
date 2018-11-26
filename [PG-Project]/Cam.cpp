#include "Cam.h"

Camera::Camera(Vector position, double fov, double near) : position(position), fov(fov), near(near) {}

Ray Camera::GetRay(double x, double y, int width, int height) {}