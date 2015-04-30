#include "Camera.h"


Camera::Camera(void)
{
	Position = vec3(15.0f, -15.0f, 21.0f);
	center = vec3(0,0,-4);
	Up = vec3(0, 1, 0);
	Yaw = 0;
	Pitch = 0;
	CameraSpeed = 0.01f;
	SetBasePosition(vec3(0.0f,0.0f,6.0f));
}


Camera::~Camera(void)
{

}

void Camera::SetBasePosition(vec3 Position)
{
	BaseOffset = Position;
}

void Camera::Keyboard_Update(Keyboard keyboard)
{
	//Camera Position X
	//if(keyboard.IsHold('W')) Position += CameraSpeed * center;
	//if(keyboard.IsHold('S')) Position -= CameraSpeed * center;
	//if(keyboard.IsHold('A')) Position -= normalize(cross(center, Up)) * CameraSpeed * 2;
	//if(keyboard.IsHold('D')) Position += normalize(cross(center, Up)) * CameraSpeed * 2; 

	//Camera Position Z
	if(keyboard.IsHold('Q')) Position[1] += CameraSpeed;
	else if(keyboard.IsHold('E')) Position[1] -= CameraSpeed;

	//Camera Rotation
	if(keyboard.IsHold('J')) center[0] += CameraSpeed;
	else if(keyboard.IsHold('L')) center[0] -= CameraSpeed;

	if(keyboard.IsHold('I')) center[1] += CameraSpeed;
	else if(keyboard.IsHold('K')) center[1] -= CameraSpeed;

	if(keyboard.IsHold('U')) center[2] += CameraSpeed;
	else if(keyboard.IsHold('O')) center[2] -= CameraSpeed;
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

void Camera::Update(vec3 PlayerPosition)
{
	Position[2] = abs(PlayerPosition[2]) + BaseOffset[2];
	Position[1] = PlayerPosition[1];
	Position[0] = PlayerPosition[0];
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
