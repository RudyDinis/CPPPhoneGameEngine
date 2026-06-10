#include "CameraClass.hpp"

Camera::Camera(/* args */)
{
}

float *Camera::getOffset_y()
{
	return (&this->offset_y);
}

float *Camera::getOffset_x()
{
	return (&this->offset_x);
}

Camera::~Camera()
{
}