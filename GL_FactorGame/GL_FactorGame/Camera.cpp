#include "Camera.h"


Camera::Camera(void)
{
	Position = vec3(0, 0.5f, 3);
	center = vec3(0,0,-4);
	Up = vec3(0, 1, 0);
	Yaw = 0;
	Pitch = 0;
}


Camera::~Camera(void)
{

}

void Camera::MouseMove(int x, int y)
{
	float xOffset = x - LastX;
	float yOffset = y - LastY;  //System is Reversed

	if(firstMouse) // this bool variable is initially set to true
	{
		LastX = x;
		LastY = y;
		firstMouse = false;
	}

	LastX = x;
	LastY = y;

	float Sensibility = 0.25;
	xOffset *= Sensibility;
	yOffset *= Sensibility;

	Yaw += xOffset;
	Pitch += -yOffset;

	if(Pitch >  89.0f) Pitch =  89.0f;
	if(Pitch < -89.0f) Pitch = -89.0f;

	/*center[0] = cos(radians(Yaw) * cos(radians(Pitch)));
	center[1] = sin(radians(Pitch));
	center[2] = sin(radians(Yaw) * cos(radians(Pitch)));*/
	center[0] = cos(radians(Yaw) * cos(radians(Pitch)));
	center[1] = sin(radians(Pitch));
	center[2] = sin(radians(Yaw) * cos(radians(Pitch)));
	center = normalize(center);
}

void Camera::Update()
{
	lookAtMatrix_matrix = lookAt(Position,Position + center, Up);
}

mat4 Camera::lookAt(vec3 eye, vec3 center, vec3 up)
{
	vec3 forward = normalize(center - eye); //forward vector
	vec3 upNormal = normalize(up); 
	vec3 sideway = cross(forward, upNormal);
	vec3 up_Vector = cross(sideway, forward);

	mat4 M = mat4(
		vec4(sideway[0], up_Vector[0], -forward[0], 0),
		vec4(sideway[1], up_Vector[1], -forward[1], 0),
		vec4(sideway[2], up_Vector[2], -forward[2], 0),
		vec4(0, 0, 0, 1)
		);

	return M * translate(-eye);
}
